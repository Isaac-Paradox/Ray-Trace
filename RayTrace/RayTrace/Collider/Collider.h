#pragma once
#include<vector>
#include"../CoreDefine/CommonDefine.h"

#define _ISINVIEWFRUSTUM(v, max, min) (v < max && v > min)

class IMaterial;

struct RayCastHitRecord {
	float t;
	Vector3 rayCastHitPoint;
	Vector3 hitPointNormal;
	IMaterial* mat = nullptr;
};

class ICollider{
	public:
	//�����ع���������������Rendererͳ������
	IMaterial* m_pMaterial = nullptr;

	public:
	ICollider(IMaterial* mat) : m_pMaterial(mat){}

	virtual bool Hit(const Ray& ray, float t_min, float t_max, RayCastHitRecord& record) const = 0;
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