#pragma once
#include<math.h>

const float fEpsilon = 1E-05F;

const float fPi = 3.1415926f;

inline bool FloatEqual(float lhs, float rhs);
inline bool FloatEqual(double lhs, double rhs);

struct Vector3;
struct Matrix4x4;
struct Quaternion;

struct Vector3
{
	public:
	float x = 0;
	float y = 0;
	float z = 0;

	public:
	Vector3(float _x = 0, float _y = 0, float _z = 0)
		: x(_x), y(_y), z(_z)
	{ }

	Vector3(const Vector3& copy) :
		x(copy.x), y(copy.y), z(copy.z)
	{ }

	inline static Vector3 Zero()    { return Vector3( 0.0f,  0.0f,  0.0f); }

	inline static Vector3 One()     { return Vector3( 1.0f,  1.0f,  1.0f); }

	inline static Vector3 Forward() { return Vector3( 0.0f,  0.0f,  1.0f); }

	inline static Vector3 Back()    { return Vector3( 0.0f,  0.0f, -1.0f); }

	inline static Vector3 Left()    { return Vector3(-1.0f,  0.0f,  0.0f); }

	inline static Vector3 Right()   { return Vector3( 1.0f,  0.0f,  0.0f); }

	inline static Vector3 Up()      { return Vector3( 0.0f,  1.0f,  0.0f); }

	inline static Vector3 Down()    { return Vector3( 0.0f, -1.0f,  0.0f); }

	void SetTo(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

	inline float Length() { return sqrtf(x * x + y * y + z * z); }

	inline void Normalize() { (*this) /= Length(); }

	inline Vector3 Normalized() const
	{
		Vector3 out(*this);
		out.Normalize();
		return out;
	}

	inline Vector3& operator += (float value) { x += value; y += value; z += value;  return *this; }

	inline Vector3& operator += (const Vector3& value) { x += value.x; y += value.y; z += value.z;  return *this; }

	inline Vector3& operator -= (const Vector3& value) { x -= value.x; y -= value.y; z -= value.z; return *this; }

	inline Vector3& operator *= (float k) { x *= k; y *= k; z *= k; return *this; }

	inline Vector3& operator /= (float k) { k = 1 / k; x *= k; y *= k; z *= k; return *this; }
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

inline Vector3 operator + (const Vector3& value, float v);

inline Vector3 operator + (const Vector3& lhs, const Vector3& rhs);

inline Vector3 operator - (const Vector3& lhs, const Vector3& rhs);

inline Vector3 operator * (const Vector3& value, float k);

inline Vector3 operator * (float k, const Vector3& value);

inline Vector3 operator / (const Vector3& value, float k);

inline float dot(const Vector3& lhs, const Vector3& rhs);

inline bool operator != (const Vector3& lhs, const Vector3& rhs);

inline bool operator == (const Vector3& lhs, const Vector3& rhs);

double Random();