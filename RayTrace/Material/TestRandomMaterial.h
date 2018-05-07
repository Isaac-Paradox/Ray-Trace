#pragma once
#include "Material.h"
class TestMaterial : public IReflectObjectMaterial
{
	public:
	bool Scatter(Ray& ray, const RayCastHitRecord& record, Color& attenuation) const override {
		Vector3	target = record.rayCastHitPoint + record.hitPointNormal + RandomSphere();
		ray.ResetRay(record.rayCastHitPoint, target - record.rayCastHitPoint);
		attenuation.SetTo(0.5f, 0.5f, 0.5f);
		return true;
	}
};
