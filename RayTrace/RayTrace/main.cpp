#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <chrono>  

#include "RayTrace.h"
#include "PPMWriter.h"
#include "Collider/Sphere.h"
#include "Material/TestRandomMaterial.h"

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

	TestMaterial testMat;

	Sphere ball(Vector3(0, 0, -1), 0.5, &testMat);
	Sphere ground(Vector3(0, -100.5f, -1), 100, &testMat);
	
	worldObjectList.AddCollider(&ball);
	worldObjectList.AddCollider(&ground);

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

