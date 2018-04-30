#pragma once

#include "MathematicDefine.h"

struct Color : public Vector3
{
	public:
	Color(float _x = 0, float _y = 0, float _z = 0) : Vector3(_x, _y, _z) {};

	Color(Vector3 tran): Vector3(tran){}


	inline float r() { return x; }

	inline float g() { return y; }

	inline float b() { return z; }

	inline unsigned int R() { return unsigned int(255.99 * x); }

	inline unsigned int G() { return unsigned int(255.99 * y); }

	inline unsigned int B() { return unsigned int(255.99 * z); }
};

class Ray
{
	protected:
	Vector3 m_vOrigin;
	Vector3 m_vDirection;

	public:
	Ray() {}
	Ray(const Vector3& ori, const Vector3& dir)
		: m_vOrigin(ori), m_vDirection(dir)
	{}

	void ResetRay(const Vector3& ori, const Vector3& dir) { m_vOrigin = ori; m_vDirection = dir; }

	inline const Vector3& Origin() const { return m_vOrigin; }
	inline const Vector3& Direction() const { return m_vDirection; }
	Vector3 GetPointAt(float t) const { return m_vOrigin + t * m_vDirection; }
};