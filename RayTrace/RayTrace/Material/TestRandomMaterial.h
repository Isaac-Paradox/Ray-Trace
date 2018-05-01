#pragma once
#include "Material.h"
class TestMaterial : public IMaterial
{
	public:
	bool Scatter(Ray& ray, const RayCastHitRecord& record, Color& attenuation) const override {
		float angleTheta = float(2.0 * fPi * Random());
		float anglePhi = float(2.0 * fPi * Random());
		float radius = (float)Random();
		float cosPhi = std::cos(anglePhi);
		Vector3 p(radius * cosPhi * std::cos(angleTheta), radius * std::sin(anglePhi), radius * cosPhi * std::sin(angleTheta));
		Vector3	target = record.rayCastHitPoint + record.hitPointNormal + p;
		ray.ResetRay(record.rayCastHitPoint, target - record.rayCastHitPoint);
		attenuation.SetTo(0.5f, 0.5f, 0.5f);
		return true;
	}
};
