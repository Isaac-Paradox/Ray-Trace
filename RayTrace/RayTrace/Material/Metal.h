#pragma once
#include "Material.h"
class Metal : public IRandomReflectMaterial
{
	protected:
	Vector3 m_vAlbedo;
	float m_fFuzz;

	public:
	Metal(const Vector3& albedo, float fuzz) : m_vAlbedo(albedo), m_fFuzz(Clamp(fuzz, 1, 0)) {}

	virtual bool Scatter(Ray& ray, const RayCastHitRecord& record, Color& attenuation) const override;

	private:
	Vector3 _Reflect(const Vector3& v, const Vector3& n) const;
};