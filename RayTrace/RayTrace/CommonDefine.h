#pragma once

#include "MathematicDefine.h"

struct Color
{
	double r = 0;
	double g = 0;
	double b = 0;

	public:
	Color(double _r = 0, double _g = 0, double _b = 0)
		: r(_r), g(_g), b(_b)
	{ }

	//Color(const Color& col):
	//	r(col.r), g(col.g), b(col.b)
	//{ }
	//Color operator = (const Color col)
	//{
	//	r = col.r;
	//	g = col.g;
	//	b = col.b;

	//	return *this;
	//}
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