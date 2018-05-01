#include"Sphere.h"
Sphere::Sphere(IMaterial* mat) : ICollider(mat)
{ }

Sphere::Sphere(Vector3 center, float r, IMaterial* mat)
	: m_vCenter(center), m_fRadius(r), ICollider(mat)
{ }

Sphere::~Sphere()
{ }

bool Sphere::Hit(const Ray & ray, float t_min, float t_max, RayCastHitRecord & record) const
{
	Vector3 oc = ray.Origin() - m_vCenter;
	float a = dot(ray.Direction(), ray.Direction());
	float b = dot(oc, ray.Direction());
	float c = dot(oc, oc) - m_fRadius * m_fRadius;
	float delta = b * b - a * c;//b^2 - 4ac 4与b^2中的2约去
	if (delta >= 0)
	{
		delta = sqrtf(delta);
		float temp = (-b - delta) / a;
		if (_ISINVIEWFRUSTUM(temp, t_max, t_min))
		{
			record.t = temp;
			record.rayCastHitPoint = ray.GetPointAt(temp);
			record.hitPointNormal = (record.rayCastHitPoint - m_vCenter) / m_fRadius;
			return true;
		}
		temp = (-b + delta) / a;
		if (_ISINVIEWFRUSTUM(temp, t_max, t_min))
		{
			record.t = temp;
			record.rayCastHitPoint = ray.GetPointAt(temp);
			record.hitPointNormal = (record.rayCastHitPoint - m_vCenter) / m_fRadius;
			return true;
		}
	}
	return false;
}
