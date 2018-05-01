#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <chrono>  

#include "RayTrace.h"
#include "PPMWriter.h"
#include "Collider/Sphere.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"

using namespace std;
using namespace chrono;
using namespace RayTraceRenderer;

int main(int argc, char **argv)
{
	string outPutPath = "output.ppm";
	float width = 4;
	float height = 3;
	int pixelHeight = 600;
	PPMWriter writer(int(pixelHeight * width / height), pixelHeight);
	RayTraceCamera camera(width, height);

	ColliderList worldObjectList;

	Lambertian ballMat(Vector3(0.8f, 0.3f, 0.3f));
	Lambertian groundMat(Vector3(0.8f, 0.8f, 0.0f));

	Metal metal1(Vector3(0.8f, 0.6f, 0.2f), 1.0f);
	Metal metal2(Vector3(0.8f, 0.8f, 0.8f), 0.3f);

	Dielectric diele(1.5f);

	Sphere ball(Vector3(0.0f, 0.0f, -1.0f), 0.5f, &ballMat);
	Sphere ground(Vector3(0.0f, -100.5f, -1.0f), 100.0f, &groundMat);

	Sphere ball1(Vector3(1.0f, 0.0f, -1.0f), 0.5f, &metal1);
	Sphere ball2(Vector3(-1.0f, 0.0f, -1.0f), 0.5f, &diele);
	
	worldObjectList.AddCollider(&ball);
	worldObjectList.AddCollider(&ground);
	worldObjectList.AddCollider(&ball1);
	worldObjectList.AddCollider(&ball2);

	cout << "初始化完成，开始输出" << endl;

	system_clock::time_point startTime = system_clock::now();
	
	camera.DrawToBuffer(writer.GetFrameBuffer(), worldObjectList, pixelHeight);

	system_clock::time_point drawCompleteTime = system_clock::now();

	cout << "光线追踪完成，耗时" << double(duration_cast<microseconds>(drawCompleteTime - startTime).count()) * microseconds::period::num / microseconds::period::den << "秒" << endl;

	if (writer.WritePPMFile(outPutPath))
	{
		cout << "输出图片" << outPutPath << "成功，输出耗时" << double(duration_cast<microseconds>(system_clock::now() - drawCompleteTime).count()) * microseconds::period::num / microseconds::period::den << "秒";
	}
	else
	{
		cout << "输出图片" << outPutPath << "失败";
	}
	cin.get();
    return 0;
}

