#include "Material.h"

Vector3 IReflectObjectMaterial::RandomSphere(float radius) const
{
	float angleTheta = float(2.0 * PI * Random());
	float anglePhi = float(2.0 * PI * Random());
	float _radius = radius * (float)Random();
	float cosPhi = std::cos(anglePhi);
	return Vector3(_radius * cosPhi * std::cos(angleTheta), _radius * std::sin(anglePhi), _radius * cosPhi * std::sin(angleTheta));
}

Vector3 IReflectObjectMaterial::_Reflect(const Vector3 & v, const Vector3 & n) const
{
	Vector3 uv = v.Normalized();
	return uv - 2.0f * Dot(uv, n) * n;
}

bool IReflectObjectMaterial::_Refract(const Vector3 & v, const Vector3 & n, float ior, Vector3 & refracted) const
{
	Vector3 uv = v.Normalized();
	float _dot = Dot(uv, n);
	float delta = 1.0f - ior * ior * (1 - _dot * _dot);
	if (delta > 0)
	{
		refracted = ior * (uv - n * _dot) - n * sqrtf(delta);
		return true;
	}
	else
	{
		return false;
	}
}
