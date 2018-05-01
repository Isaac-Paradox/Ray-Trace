#include "Lambertian.h"

bool Lambertian::Scatter(Ray & ray, const RayCastHitRecord & record, Color & attenuation) const
{
	float angleTheta = float(2.0 * fPi * Random());
	float anglePhi = float(2.0 * fPi * Random());
	float radius = (float)Random();
	float cosPhi = std::cos(anglePhi);
	Vector3 p(radius * cosPhi * std::cos(angleTheta), radius * std::sin(anglePhi), radius * cosPhi * std::sin(angleTheta));
	Vector3	target = record.rayCastHitPoint + record.hitPointNormal + p;
	ray.ResetRay(record.rayCastHitPoint, target - record.rayCastHitPoint);
	attenuation = m_vAlbedo;
	return true;
}
