#include"RayTrace.h"

void RayTraceRenderer::RayTraceCamera::DrawToBuffer(Color ** frameBuffer, const ColliderList& colliderObjects, unsigned int pixelHeight)
{
	unsigned int pixelWidth = m_fAspect * pixelHeight;
	
	Ray ray;
	for (size_t i = 0; i < pixelHeight; i++)
	{
		for (size_t j = 0; j < pixelWidth; j++)
		{
			_GetRay(ray, (double)j / pixelWidth, (double)i / pixelHeight);
			_RayCatchColor(ray, colliderObjects, frameBuffer[i][j]);
		}
	}
}

void RayTraceRenderer::RayTraceCamera::_GetRay(Ray & ray, double u, double v)
{
	ray.ResetRay(m_vOrigin, m_vLowLeftCorner + u * m_vHorizontal + v * m_vVertical);
}

void RayTraceRenderer::RayTraceCamera::_RayCatchColor(const Ray & ray, const ColliderList& colliderObjects, Color & col)
{
	RayCastHitRecord record;
	if (colliderObjects.Hit(ray, 0.0, 1000, record))
	{
		Vector3 vec = (record.hitPointNormal + 1) * 0.5;
		col.r = vec.x;
		col.g = vec.y;
		col.b = vec.z;
	}
	else
	{
		float t = 0.5 * (ray.Direction().Normalized().y + 1);
		float _1st = 1 - t;
		col.r = _1st + t * 0.5;
		col.g = _1st + t * 0.7;
		col.b = _1st + t;
	}
}
