#include"RayTrace.h"

void RayTraceRenderer::RayTrace::DrawToBuffer(Color ** frameBuffer, unsigned int width, unsigned int height)
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			float t = (double)i / height;
			float r = (1.0 - t) + t * 0.5;
			float g = (1.0 - t) + t * 0.7;
			float b = (1.0 - t) + t;
			frameBuffer[i][j].r = unsigned int(255.99 * r);
			frameBuffer[i][j].g = unsigned int(255.99 * g);
			frameBuffer[i][j].b = unsigned int(255.99 * b);
		}
	}
}
