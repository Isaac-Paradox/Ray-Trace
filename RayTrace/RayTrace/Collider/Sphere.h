#pragma once
#include"Collider.h"
class Sphere : public ICollider
{
	protected:
	Vector3 m_vCenter;
	float m_fRadius = 1;

	public:
	Sphere(IMaterial* mat);
	Sphere(Vector3 center, float r, IMaterial* mat);

	~Sphere();

	bool Hit(const Ray& ray, float t_min, float t_max, RayCastHitRecord& record) const override;

	private:

};

