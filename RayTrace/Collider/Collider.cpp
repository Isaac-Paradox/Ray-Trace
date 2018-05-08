#include"Collider.h"

unsigned int ColliderList::AddCollider(const ICollider * collider)
{
	m_vColliders.push_back(collider);
	m_vColliderHandles.push_back(m_nNewHandle);
	return m_nNewHandle++;
}

bool ColliderList::RemoveCollider(unsigned int handle) {
	auto iter = std::find(m_vColliderHandles.begin(), m_vColliderHandles.end(), handle);
	if (iter == m_vColliderHandles.end()) {
		return false;
	}

	int index = std::distance(m_vColliderHandles.begin(), iter);
	m_vColliderHandles.erase(iter);
	m_vColliders.erase(m_vColliders.begin() + index);
	return true;
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
				record.mat = collider->m_pMaterial;
		}
	}
	return hitAny;
}
