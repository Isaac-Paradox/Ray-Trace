#pragma once
#include<cassert>
#include<math.h>

const float fEpsilon = 1E-05F;

const float PI = 3.1415926f;

const float RADIANS_TO_DEGREES = 180.0f / PI;
const float DEGREES_TO_RADIANS = PI / 180.0f;

inline bool FloatEqual(float lhs, float rhs);
inline bool FloatEqual(double lhs, double rhs);

double Random();

inline float Clamp(float value, float max, float min);

struct Vector3;
struct Vector4;
struct Matrix4x4;
struct Quaternion;

struct Vector4 {
	public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	public:
	Vector4(float _x = 0, float _y = 0, float _z = 0, float _w = 0)
		: x(_x), y(_y), z(_z), w(_w) {}
};

struct Vector3 {
	public:
	float x = 0;
	float y = 0;
	float z = 0;

	public:
	Vector3(float _x = 0, float _y = 0, float _z = 0)
		: x(_x), y(_y), z(_z) {}

	Vector3(const Vector3& copy) :
		x(copy.x), y(copy.y), z(copy.z) {}

	Vector3(const Vector4& copy) :
		x(copy.x), y(copy.y), z(copy.z) {}

	inline static Vector3 Zero() { return Vector3(0.0f, 0.0f, 0.0f); }

	inline static Vector3 One() { return Vector3(1.0f, 1.0f, 1.0f); }

	inline static Vector3 Forward() { return Vector3(0.0f, 0.0f, 1.0f); }

	inline static Vector3 Back() { return Vector3(0.0f, 0.0f, -1.0f); }

	inline static Vector3 Left() { return Vector3(-1.0f, 0.0f, 0.0f); }

	inline static Vector3 Right() { return Vector3(1.0f, 0.0f, 0.0f); }

	inline static Vector3 Up() { return Vector3(0.0f, 1.0f, 0.0f); }

	inline static Vector3 Down() { return Vector3(0.0f, -1.0f, 0.0f); }

	void SetTo(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

	inline float Length() const { return sqrtf(x * x + y * y + z * z); }

	inline void Normalize() { (*this) /= Length(); }

	inline Vector3 Normalized() const { Vector3 out(*this); out.Normalize(); return out; }

	inline Vector3& operator += (float value) { x += value; y += value; z += value;  return *this; }

	inline Vector3& operator += (const Vector3& value) { x += value.x; y += value.y; z += value.z;  return *this; }

	inline Vector3& operator -= (const Vector3& value) { x -= value.x; y -= value.y; z -= value.z; return *this; }

	inline Vector3& operator *= (float k) { x *= k; y *= k; z *= k; return *this; }

	inline Vector3& operator /= (float k) { k = 1 / k; x *= k; y *= k; z *= k; return *this; }
};

struct Matrix4x4
{
	public:
	float m00 = 1.0f;
	float m01 = 0.0f;
	float m02 = 0.0f;
	float m03 = 0.0f;
	float m10 = 0.0f;
	float m11 = 1.0f;
	float m12 = 0.0f;
	float m13 = 0.0f;
	float m20 = 0.0f;
	float m21 = 0.0f;
	float m22 = 1.0f;
	float m23 = 0.0f;
	float m30 = 0.0f;
	float m31 = 0.0f;
	float m32 = 0.0f;
	float m33 = 1.0f;

	public:
	inline static Matrix4x4 Zero() { Matrix4x4 _out; _out.m00 = 0.0f; _out.m11 = 0.0f; _out.m22 = 0.0f; _out.m33 = 0.0f; return _out; }
	inline static Matrix4x4 Identity() { return Matrix4x4(); }

	inline static Matrix4x4 TRS(const Vector3& pos, const Quaternion& q, const Vector3& s) { Matrix4x4 _out; _out.ToTRS(pos, q, s); return _out; }

	void ToTRS(const Vector3& pos, const Quaternion& q, const Vector3& s);

	Vector4 GetColumn(int index);

	Vector4 GetRow(int index);

	inline float* operator[](int index) { return &m00 + sizeof(float) * index * 4; }
};

struct Quaternion {
	public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;

	public:
	inline void Normalize();

	void AngleAxis(float angle, const Vector3& axis);

	void FromEulerAngle(const Vector3& euler);

	Vector3 ToEulerAngle() const;
};

inline Vector3 operator + (const Vector3& value, float v);

inline Vector3 operator + (const Vector3& lhs, const Vector3& rhs);

inline Vector3 operator - (const Vector3& lhs, const Vector3& rhs);

inline Vector3 operator - (const Vector3& value);

inline Vector3 operator * (const Vector3& value, float k);

inline Vector3 operator * (float k, const Vector3& value);

inline Vector3 operator / (const Vector3& value, float k);

inline float Dot(const Vector3& lhs, const Vector3& rhs);

inline Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

inline float Distance (const Vector3& lhs, const Vector3& rhs);

inline bool operator != (const Vector3& lhs, const Vector3& rhs);

inline bool operator == (const Vector3& lhs, const Vector3& rhs);