#pragma once
#include "Material.h"
class Lambertian : public IRandomReflectMaterial
{
	protected:
	Vector3 m_vAlbedo;

	public:
	Lambertian(const Vector3& albedo) : m_vAlbedo(albedo) {}

	virtual bool Scatter(Ray& ray, const RayCastHitRecord& record, Color& attenuation) const override;
};