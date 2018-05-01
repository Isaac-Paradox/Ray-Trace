#include "Lambertian.h"

bool Lambertian::Scatter(Ray & ray, const RayCastHitRecord & record, Color & attenuation) const
{
	Vector3	target = record.rayCastHitPoint + record.hitPointNormal + RandomSphere();
	ray.ResetRay(record.rayCastHitPoint, target - record.rayCastHitPoint);
	attenuation = m_vAlbedo;
	return true;
}
