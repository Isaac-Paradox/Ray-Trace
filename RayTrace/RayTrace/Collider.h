#pragma once
#include<vector>
#include"CommonDefine.h"

struct RayCastHitRecord {
	float t;
	Vector3 rayCastHitPoint;
	Vector3 hitPointNormal;
};

class ICollider{
	public:
	virtual bool Hit(const Ray& ray, RayCastHitRecord& record) const = 0;
};

class ColliderList
{
	protected:
	std::vector<const ICollider*> m_vColliders;
	std::vector<unsigned int> m_vColliderHandles;
	unsigned int m_nNewHandle = 0;

	public:
	unsigned int AddCollider(const ICollider* collider);

	bool Hit(const Ray& ray, float near, float far, RayCastHitRecord& record) const;

	private:

};