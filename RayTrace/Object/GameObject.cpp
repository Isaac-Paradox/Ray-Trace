#include "GameObject.h"
GameObject::~GameObject() {
	for (IComponent* ptr : m_vComponents) {
		delete ptr;
	}
	m_vComponents.clear();
}

void Transform::_CheckMatrixUpdate() const {
	if (m_bMatrixDirty) {
		_UpdateMatrix();
	}
}

void Transform::_UpdateMatrix() const {
	m_mMatrix.ToTRS(m_vPosition, m_qRotation, m_vScale);
	m_bMatrixDirty = false;
}

void Transform::_LookAt(const Vector3 & from, const Vector3 & to, const Vector3 & up) {
	Vector3 z = to - from;
	if (z.Length() == 0) {
		z.z = 1;
	}

	z.Normalize();
	Vector3 x = Cross(up, z);

	if (x.Length() == 0) {
		// up and z are parallel

		if (FloatEqual(fabsf(up.z), 1)) {
			z.x -= 0.0001f;
		} else {
			z.z -= 0.0001f;
		}

		z.Normalize();
		x = Cross(up, z);
	}

	x.Normalize();
	Vector3 y = Cross(z, x);

	//m_mMatrix.m00 = m_vScale.x * x.x; m_mMatrix.m10 = m_vScale.y * y.x; m_mMatrix.m20 = m_vScale.z * z.x; m_mMatrix.m30 = 0;
	//m_mMatrix.m01 = m_vScale.x * x.y; m_mMatrix.m11 = m_vScale.y * y.y; m_mMatrix.m21 = m_vScale.z * z.y; m_mMatrix.m31 = 0;
	//m_mMatrix.m02 = m_vScale.x * x.z; m_mMatrix.m12 = m_vScale.y * y.z; m_mMatrix.m22 = m_vScale.z * z.z; m_mMatrix.m32 = 0;
	//m_mMatrix.m03 = from.x;           m_mMatrix.m13 = from.y;           m_mMatrix.m23 = from.z;           m_mMatrix.m33 = 1;

	//上面的直接赋值或许会快一点
	m_bMatrixDirty = true;

	m_qRotation.w = sqrtf(1 + x.x + y.y + z.z) * 0.5f;
	float k = 1 / (4.0f * m_qRotation.w);
	m_qRotation.x = (y.z - z.y) * k;
	m_qRotation.y = (z.x - x.z) * k;
	m_qRotation.z = (x.y - y.x) * k;
}

IComponent::IComponent(GameObject & gobj) : m_gGameObject(gobj), m_tTransform(gobj.GetTransform()) {}
