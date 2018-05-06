#include"RayTrace.h"
void RayTraceRenderer::RayTraceCamera::Draw(const ColliderList& colliderObjects) {
	if (m_bPerspectiveDataDirty) {
		_UpdateRayScanData();
	}

	unsigned int pixelWidth = m_rTarget.Width();
	unsigned int pixelHeight = m_rTarget.Height();

	Ray ray;
	Color sampledColor;
	Color color;
	Color** frameBuffer = m_rTarget.GetFrameBuffer();
	for (size_t i = 0; i < pixelHeight; ++i) {
		for (size_t j = 0; j < pixelWidth; ++j) {
			color.SetTo(0, 0, 0);
			for (size_t s = 0; s < c_nSample; ++s) {
				_GetRay(ray, float(j + Random()) / pixelWidth, float(i + Random()) / pixelHeight);
				_RayCatchColor(ray, colliderObjects, sampledColor);
				color += sampledColor;
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

void RayTraceRenderer::RayTraceCamera::_RayCatchColor(Ray & ray, const ColliderList& colliderObjects, Color & col, int step) {
	if (step > c_nMaxStep) {
		col.SetTo(0.0f, 0.0f, 0.0f);
		return;
	}
	RayCastHitRecord record;
	Color attenuation;
	if (colliderObjects.Hit(ray, step == 0 ? m_fNear : fEpsilon, m_fFar, record)) {
		if (record.mat->Scatter(ray, record, attenuation)) {
			_RayCatchColor(ray, colliderObjects, col, step + 1);
			col *= attenuation;
			return;
		} else {
			col.SetTo(0.0f, 0.0f, 0.0f);
			return;
		}
	} else {
		float t = 0.5f * (ray.Direction().Normalized().y + 1);
		col = (1.0f - t) * c_cSkyBoyLow + t * c_cSkyBoyTop;
	}
}

//用于矫正颜色
void RayTraceRenderer::RayTraceCamera::_WriteColor(Color & target, const Color & value) {
	//target.x = sqrtf(value.x);
	//target.y = sqrtf(value.y);
	//target.z = sqrtf(value.z);
	target = value;
}

void RayTraceRenderer::RayTraceCamera::_UpdateRayScanData() {
	float height = std::tanf(m_fFov * fPi / 360);//可以考虑手算1 / 360 然后直接填字面值
	float widht = Aspect() * height;

	//之后考虑看看能不能从矩阵中取出
	m_vOrigin.SetTo(0, 0, 0);
	m_vHorizontal.SetTo(1, 0, 0);
	m_vVertical.SetTo(0, 1, 0);
	Vector3 forward = Vector3::Forward();//这个的长度和height使用同一个一个单位长度

	m_vHorizontal *= widht;
	m_vVertical *= height;
	m_vLowLeftCorner = -(m_vHorizontal + m_vVertical) * 0.5f + forward;

	m_bPerspectiveDataDirty = false;
}
