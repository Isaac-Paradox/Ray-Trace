#pragma once
#include "Material.h"

class Dielectric : public IReflectObjectMaterial
{
	protected:
	float m_fIor;

	public:
	Dielectric(float ior) : m_fIor(ior) {};

	bool Scatter(Ray& ray, const RayCastHitRecord& record, Color& attenuation) const override;
};