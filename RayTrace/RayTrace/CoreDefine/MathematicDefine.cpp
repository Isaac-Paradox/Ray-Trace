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

extern inline Vector3 operator-(const Vector3 & value)
{
	return Vector3(-value.x, -value.y, -value.z);
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

extern inline float Dot(const Vector3 & lhs, const Vector3 & rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

extern inline Vector3 Cross(const Vector3 & lhs, const Vector3 & rhs) {
	return Vector3(lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x);
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
	unsigned int x = unsigned int(seed >> 16);
	return  ((double)x / 0x100000000LL);
}

extern inline float Clamp(float value, float max, float min)
{
	return assert(max > min), (value < min) ? min : ((max < value) ? max : value);
}

inline void Quaternion::Normalize() {
	float norm = 1 / sqrtf(x * x + y * y + z * z + w * w);
	x *= norm;
	y *= norm;
	z *= norm;
	w *= norm;
}

void Quaternion::AngleAxis(float angle, const Vector3& axis) {
	float halfAngle = angle * 0.5f,
		_sin = sinf(halfAngle);

	x = axis.x * _sin;
	y = axis.y * _sin;
	z = axis.z * _sin;
	w = cosf(halfAngle);
}

void Quaternion::FromEulerAngle(const Vector3& euler) {
	float k = DEGREES_TO_RADIANS * 0.5f, temp = 0.0f;
	temp = euler.x * k;
	float cr_0 = cosf(temp), sr_0 = sinf(temp);
	temp = euler.y * k;
	float cr_1 = cosf(temp), sr_1 = sinf(temp);
	temp = euler.z * k;
	float cr_2 = cosf(temp), sr_2 = sinf(temp);

	x = sr_0 * cr_1 * cr_2 + cr_0 * sr_1 * sr_2;
	y = cr_0 * sr_1 * cr_2 - sr_0 * cr_1 * sr_2;
	z = cr_0 * cr_1 * sr_2 - sr_0 * sr_1 * cr_2;
	w = cr_0 * cr_1 * cr_2 + sr_0 * sr_1 * sr_2;
}

Vector3 Quaternion::ToEulerAngle() const {
	float pitchFactor = w * x - y * z;

	if (FloatEqual(fabsf(pitchFactor) - 0.5, 0)) {
		return Vector3();
	} else {
		return Vector3(asinf(2.0f * pitchFactor) * RADIANS_TO_DEGREES,
			atan2f(2.0f * (z * x + w * y), 1.0f - 2.0f * (y * y + x * x)) * RADIANS_TO_DEGREES,
			atan2f(2.0f * (y * x + w * z), 1.0f - 2.0f * (z * z + x * x)) * RADIANS_TO_DEGREES);
	}
}

Matrix4x4 Matrix4x4::ToTRS(const Vector3 & pos, const Quaternion & q, const Vector3 & s) {
	Matrix4x4 _out;
	float qX = q.x;
	float qY = q.y;
	float qZ = q.z;
	float qW = q.w;

	_out.m00 = (s.x * (1 - 2 * (qY * qY + qZ * qZ)));
	_out.m01 = (s.y * (2 * (qX * qY - qZ * qW)));
	_out.m02 = (s.z * (2 * (qX * qZ + qY * qW)));
	_out.m03 = pos.x;
	_out.m10 = (s.x * (2 * (qX * qY + qZ * qW)));
	_out.m11 = (s.y * (1 - 2 * (qX * qX + qZ * qZ)));
	_out.m12 = (s.z * (2 * (qY * qZ - qX * qW)));
	_out.m13 = pos.y;
	_out.m20 = (s.x * (2 * (qX * qZ - qY * qW)));
	_out.m21 = (s.y * (2 * (qY * qZ + qX * qW)));
	_out.m22 = (s.z * (1 - 2 * (qX * qX + qY * qY)));
	_out.m23 = pos.z;
	_out.m30 = 0;
	_out.m31 = 0;
	_out.m32 = 0;
	_out.m33 = 1;
	return _out;
}

Vector4 Matrix4x4::GetColumn(int index) {
	switch (index) {
	case 0:
		return Vector4(m00, m10, m20, m30);
	case 1:
		return Vector4(m01, m11, m21, m31);
	case 2:
		return Vector4(m02, m12, m22, m32);
	case 3:
		return Vector4(m03, m13, m23, m33);
	}
	return Vector4();
}

Vector4 Matrix4x4::GetRow(int index) {
	switch (index) {
	case 0:
		return Vector4(m00, m01, m02, m03);
	case 1:
		return Vector4(m10, m11, m12, m13);
	case 2:
		return Vector4(m20, m21, m22, m23);
	case 3:
		return Vector4(m30, m31, m32, m33);
	}
	return Vector4();
}
