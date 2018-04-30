#include"MathematicDefine.h"

extern inline bool FloatEqual(float lhs, float rhs) {
	float s = lhs - rhs;
	return s < fEpsilon &&  s > -fEpsilon;
}

extern inline bool FloatEqual(double lhs, double rhs) {
	return FloatEqual((float)lhs, (float)rhs);
}

extern inline Vector3 operator+(const Vector3 & value, float v)
{
	return Vector3(value.x + v, value.y + v, value.z + v);
}

extern inline Vector3 operator + (const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

extern inline Vector3 operator - (const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

extern inline Vector3 operator * (const Vector3& value, float k)
{
	return Vector3(value.x * k, value.y * k, value.z * k);
}

extern inline Vector3 operator * (float k, const Vector3& value)
{
	return Vector3(value.x * k, value.y * k, value.z * k);
}

extern inline Vector3 operator / (const Vector3& value, float k)
{
	k = 1 / k;
	return Vector3(value.x * k, value.y * k, value.z * k);
}

extern inline float dot(const Vector3 & lhs, const Vector3 & rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

extern inline bool operator != (const Vector3& lhs, const Vector3& rhs)
{
	return !FloatEqual(lhs.x, rhs.x) || !FloatEqual(lhs.y, rhs.y) || !FloatEqual(lhs.z, rhs.z);
}

extern inline bool operator == (const Vector3& lhs, const Vector3& rhs)
{
	return !(lhs != rhs);
}

extern double Random()
{
	static unsigned long long seed = 1;

	seed = (0x5DEECE66DLL * seed + 0xB16) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return  ((double)x / 0x100000000LL);
}
