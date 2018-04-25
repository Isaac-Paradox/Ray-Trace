#include "stdafx.h"

using namespace std;
using namespace chrono;
using namespace RayTraceRenderer;

int main(int argc, char **argv)
{
	string outPutPath = "output.ppm";
	double width = 4;
	double height = 3;
	int pixelHeight = 600;
	PPMWriter writer(int(pixelHeight * width / height), pixelHeight);
	RayTraceCamera camera(width, height);

	system_clock::time_point startTime = system_clock::now();

	camera.DrawToBuffer(writer.GetFrameBuffer(), pixelHeight);

	double drawTime = double(duration_cast<microseconds>(system_clock::now() - startTime).count()) * microseconds::period::num / microseconds::period::den;

	if (writer.WritePPMFile(outPutPath))
	{
		cout << "输出图片" << outPutPath << "成功，耗时" << drawTime << "毫秒";
	}
	else
	{
		cout << "输出图片" << outPutPath << "失败";
	}
	cin.get();
    return 0;
}

