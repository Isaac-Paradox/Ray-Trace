#pragma once
#include"Collider.h"
class Sphere : public ICollider
{
	protected:
	Vector3 m_vCenter;
	float radius;

	public:
	Sphere();
	~Sphere();

	private:

};

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}