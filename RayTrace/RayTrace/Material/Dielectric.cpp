#include "Dielectric.h"

bool Dielectric::Scatter(Ray & ray, const RayCastHitRecord & record, Color & attenuation) const {
	Vector3 _normal;
	Vector3 reflected = _Reflect(ray.Direction(), record.hitPointNormal);
	float _ior;
	attenuation.SetTo(1.0f, 1.0f, 0.0f);
	
	if (dot(ray.Direction(), record.hitPointNormal) > 0) {
		_normal = -record.hitPointNormal;
		_ior = m_fIor;
	} else {
		_normal = record.hitPointNormal;
		_ior = 1.0f / m_fIor;
	}

	Vector3 refracted;
	if (_Refract(ray.Direction(), _normal, _ior, refracted)) {
		ray.ResetRay(record.rayCastHitPoint, refracted);
	} else {
		ray.ResetRay(record.rayCastHitPoint, reflected);
		return false;
	}

	return true;
}
