#pragma once
#include "Material.h"
class Metal : public IReflectObjectMaterial
{
	protected:
	Vector3 m_vAlbedo;
	float m_fFuzz;

	public:
	Metal(const Vector3& albedo, float fuzz) : m_vAlbedo(albedo), m_fFuzz(Clamp(fuzz, 1, 0)) {}

	virtual bool Scatter(Ray& ray, const RayCastHitRecord& record, Color& attenuation) const override;
};