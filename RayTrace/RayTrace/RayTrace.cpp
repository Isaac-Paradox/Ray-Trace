#include"RayTrace.h"

void RayTraceRenderer::RayTraceCamera::DrawToBuffer(Color ** frameBuffer, unsigned int pixelHeight)
{
	unsigned int pixelWidth = m_fAspect * pixelHeight;

	Vector3 s_vOrigin(0, 0, 0);
	Vector3 s_vHorizontal(m_fWidth, 0, 0);
	Vector3 s_vVertical(0, m_fHeight, 0);
	Vector3 s_vLowLeftCorner(-m_fWidth * 0.5, -m_fHeight * 0.5, -1);//最后这个值以后通过fov算出来

	for (size_t i = 0; i < pixelHeight; i++)
	{
		for (size_t j = 0; j < pixelWidth; j++)
		{
			Ray r(s_vOrigin, s_vLowLeftCorner + ((double)j / pixelWidth) * s_vHorizontal + ((double)i / pixelHeight) * s_vVertical);
			Color color = _RayCatchColor(r);
			frameBuffer[i][j].r = unsigned int(255.99 * color.r);
			frameBuffer[i][j].g = unsigned int(255.99 * color.g);
			frameBuffer[i][j].b = unsigned int(255.99 * color.b);
		}
	}
}

Color RayTraceRenderer::RayTraceCamera::_RayCatchColor(const Ray& ray)
{
	float t = 0.5 * (ray.Direction().Normalized().y + 1);
	float _1st = 1 - t;
	return Color(_1st + t * 0.5, _1st + t * 0.7, _1st + t);
}
