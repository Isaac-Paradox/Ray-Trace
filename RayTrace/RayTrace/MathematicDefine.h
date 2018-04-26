#pragma once
#include<math.h>

const float fEpsilon = 1E-05F;

bool FloatEqual(float lhs, float rhs);

struct Vector3;
struct Matrix4x4;
struct Quaternion;

struct Vector3
{
public:
	double x = 0;
	double y = 0;
	double z = 0;

public:
	Vector3(double _x = 0, double _y = 0, double _z = 0):
		x(_x), y(_y), z(_z)
	{ }

	Vector3(const Vector3& copy):
		x(copy.x), y(copy.y), z(copy.z)
	{ }

	void SetTo(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }

	inline double Length() { return sqrt(x * x + y * y + z * z); }

	inline void Normalize() { (*this) /= Length(); }

	inline Vector3 Normalized() const
	{
		Vector3 out(*this);
		out.Normalize();
		return out;
	}

	inline void operator += (const Vector3& value) { x += value.x; y += value.y; z += value.z; }

	inline void operator -= (const Vector3& value) { x -= value.x; y -= value.y; z -= value.z; }

	inline void operator *= (double k){ x *= k; y *= k; z *= k; }

	inline void operator /= (double k) { k = 1 / k; x *= k; y *= k; z *= k; }
};

struct Matrix4x4
{
	public:
	float m00;
	float m33;
	float m23;
	float m13;
	float m03;
	float m32;
	float m22;
	float m02;
	float m12;
	float m21;
	float m11;
	float m01;
	float m30;
	float m20;
	float m10;
	float m31;
};

inline Vector3 operator + (const Vector3& lhs, const Vector3& rhs);

inline Vector3 operator - (const Vector3& lhs, const Vector3& rhs);

inline Vector3 operator * (const Vector3& value, double k);

inline Vector3 operator * (double k, const Vector3& value);

inline Vector3 operator / (const Vector3& value, double k);

inline bool operator != (const Vector3& lhs, const Vector3& rhs);

inline bool operator == (const Vector3& lhs, const Vector3& rhs);
