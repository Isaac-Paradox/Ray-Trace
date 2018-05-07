#include "Dielectric.h"

bool Dielectric::Scatter(Ray & ray, const RayCastHitRecord & record, Color & attenuation) const {
	Vector3 _normal;
	
	float _ior;
	attenuation.SetTo(1.0f, 1.0f, 1.0f);

	float _fDirLengthMulCos = Dot(ray.Direction(), record.hitPointNormal);
	if (_fDirLengthMulCos > 0) {
		_normal = -record.hitPointNormal;
		_ior = m_fIor;
	} else {
		_normal = record.hitPointNormal;
		_ior = 1.0f / m_fIor;
	}

	float reflProbty;
	Vector3 refracted;
	if (_Refract(ray.Direction(), _normal, _ior, refracted)) {
		float cos = _fDirLengthMulCos / ray.Direction().Length();
		if (_fDirLengthMulCos > 0) {
			cos = m_fIor * cos;
		} else {
			cos = -cos;
		}
		reflProbty = _Schlick(cos, m_fIor);
	} else {
		reflProbty = 1.0f;
	}

	if(Random() < reflProbty){
		ray.ResetRay(record.rayCastHitPoint, _Reflect(ray.Direction(), record.hitPointNormal));
	} else {
		ray.ResetRay(record.rayCastHitPoint, refracted);
	}

	return true;
}

inline float Dielectric::_Schlick(float cos, float ior) const {
	float r0 = (1 - ior) / (1 + ior);
	r0 = r0 * r0;
	return r0 + (1 - r0) * std::pow((1 - cos), 5);
}
