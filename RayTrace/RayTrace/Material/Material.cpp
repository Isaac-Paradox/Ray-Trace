#include "Material.h"

Vector3 IRandomReflectMaterial::RandomSphere(float radius) const
{
	float angleTheta = float(2.0 * fPi * Random());
	float anglePhi = float(2.0 * fPi * Random());
	float _radius = radius * (float)Random();
	float cosPhi = std::cos(anglePhi);
	return Vector3(_radius * cosPhi * std::cos(angleTheta), _radius * std::sin(anglePhi), _radius * cosPhi * std::sin(angleTheta));
}
