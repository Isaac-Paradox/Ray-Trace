#include "Metal.h"

bool Metal::Scatter(Ray & ray, const RayCastHitRecord & record, Color & attenuation) const
{
	Vector3 refl = _Reflect(ray.Direction(), record.hitPointNormal);
	ray.ResetRay(record.rayCastHitPoint, refl + RandomSphere(m_fFuzz));
	attenuation = m_vAlbedo;
	return Dot(ray.Direction(), record.hitPointNormal) > 0;
}