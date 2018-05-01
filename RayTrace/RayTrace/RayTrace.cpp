#include"RayTrace.h"
void RayTraceRenderer::RayTraceCamera::DrawToBuffer(Color ** frameBuffer, const ColliderList& colliderObjects, unsigned int pixelHeight)
{
	unsigned int pixelWidth = unsigned int(m_fAspect * pixelHeight);
	
	Ray ray;
	Color col;
	Color color;
	for (size_t i = 0; i < pixelHeight; ++i)
	{
		for (size_t j = 0; j < pixelWidth; ++j)
		{
			color.SetTo(0, 0, 0);
			for (size_t s = 0; s < c_nSample; ++s)
			{
				_GetRay(ray, float(j + Random()) / pixelWidth, float(i + Random()) / pixelHeight);
				_RayCatchColor(ray, colliderObjects, col);
				color += col;
			}
			color /= (float)c_nSample;
			_WriteColor(frameBuffer[i][j], color);
		}
	}
}

void RayTraceRenderer::RayTraceCamera::_GetRay(Ray & ray, float u, float v)
{
	ray.ResetRay(m_vOrigin, (m_vLowLeftCorner + u * m_vHorizontal + v * m_vVertical));
}

void RayTraceRenderer::RayTraceCamera::_RayCatchColor(Ray & ray, const ColliderList& colliderObjects, Color & col, int step)
{
	if (step > c_nMaxStep)
	{
		col.SetTo(0.0f, 0.0f, 0.0f);
		return;
	}
	RayCastHitRecord record;
	Color attenuation;
	if (colliderObjects.Hit(ray, fEpsilon, 1000.0f, record))
	{
		if (record.mat->Scatter(ray, record, attenuation))
		{
			_RayCatchColor(ray, colliderObjects, col, step + 1);
			col *= attenuation;
			return;
		}
		else
		{
			col.SetTo(0.0f, 0.0f, 0.0f);
			return;
		}
	}
	else
	{
		float t = 0.5f * (ray.Direction().Normalized().y + 1);
		col = (1.0f - t) * c_cSkyBoyLow + t * c_cSkyBoyTop;
	}
}

//用于矫正颜色
void RayTraceRenderer::RayTraceCamera::_WriteColor(Color & target, const Color & value)
{
	//target.x = sqrtf(value.x);
	//target.y = sqrtf(value.y);
	//target.z = sqrtf(value.z);
	target = value;
}
