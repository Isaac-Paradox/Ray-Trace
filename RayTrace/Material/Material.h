#pragma once
#include "../CoreDefine/CommonDefine.h"
#include "../Collider/Collider.h"

class IBaseMaterial
{
	public:
	virtual bool Scatter(Ray& ray, const RayCastHitRecord& record, Color& attenuation) const = 0;
};

class IReflectObjectMaterial : public IBaseMaterial
{
	protected:
	Vector3 RandomSphere(float radius = 1.0f) const;

	Vector3 _Reflect(const Vector3& v, const Vector3& n) const;

	bool _Refract(const Vector3& v, const Vector3& n, float ior, Vector3& refracted) const;
};
