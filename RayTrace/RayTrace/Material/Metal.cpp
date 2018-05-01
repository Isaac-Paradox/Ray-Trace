#include "Metal.h"

bool Metal::Scatter(Ray & ray, const RayCastHitRecord & record, Color & attenuation) const
{
	Vector3 refl = _Reflect(ray.Direction().Normalized(), record.hitPointNormal);
	ray.ResetRay(record.rayCastHitPoint, refl + RandomSphere(m_fFuzz));
	attenuation = m_vAlbedo;
	return dot(ray.Direction(), record.hitPointNormal) > 0;
}

Vector3 Metal::_Reflect(const Vector3 & v, const Vector3 & n) const
{
	return v - 2.0f * dot(v, n) * n;
}
