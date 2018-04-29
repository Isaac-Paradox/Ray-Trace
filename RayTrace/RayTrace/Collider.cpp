#include"Collider.h"

unsigned int ColliderList::AddCollider(const ICollider * collider)
{
	m_vColliders.push_back(collider);
	m_vColliderHandles.push_back(m_nNewHandle);
	return m_nNewHandle++;
}

bool ColliderList::Hit(const Ray & ray, float near, float far, RayCastHitRecord & record) const
{
	RayCastHitRecord tempRec;
	bool hitAny = false;
	float closest = far;
	for (const ICollider* collider : m_vColliders)
	{
		if (collider->Hit(ray, near, closest, tempRec))
		{
				hitAny = true;
				closest = tempRec.t;
				record = tempRec;
		}
	}
	return hitAny;
}
