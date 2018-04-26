#include"MathematicDefine.h"

extern bool FloatEqual(float lhs, float rhs) {
	float s = lhs - rhs;
	return s < fEpsilon &&  s > -fEpsilon;
}

extern inline Vector3 operator + (const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

extern inline Vector3 operator - (const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

extern inline Vector3 operator * (const Vector3& value, double k)
{
	return Vector3(value.x * k, value.y * k, value.z * k);
}

extern inline Vector3 operator * (double k, const Vector3& value)
{
	return Vector3(value.x * k, value.y * k, value.z * k);
}

extern inline Vector3 operator / (const Vector3& value, double k)
{
	k = 1 / k;
	return Vector3(value.x * k, value.y * k, value.z * k);
}

extern inline bool operator != (const Vector3& lhs, const Vector3& rhs)
{
	return !FloatEqual(lhs.x, rhs.x) || !FloatEqual(lhs.y, rhs.y) || !FloatEqual(lhs.z, rhs.z);
}

extern inline bool operator == (const Vector3& lhs, const Vector3& rhs)
{
	return !(lhs != rhs);
}
