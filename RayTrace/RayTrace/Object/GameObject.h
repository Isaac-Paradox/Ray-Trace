#pragma once
#include <vector>
#include "../CoreDefine/MathematicDefine.h"

class GameObject;
class Transform;
class IComponent;

class Transform {
	friend class GameObject;
	protected:
	mutable Matrix4x4 m_mMatrix;

	Vector3 m_vPosition;
	Vector3 m_vScale = Vector3::One();
	Quaternion m_qRotation;

	mutable bool m_bMatrixDirty = true;

	public:
	~Transform() {};

	inline const Vector3& GetLocalPosition() const { return m_vPosition; }

	inline void SetLocalPosition(const Vector3& value) { m_vPosition = value; m_bMatrixDirty = true; }

	inline const Vector3& GetLocalScale() const { return m_vScale; }

	inline void SetLocalScale(const Vector3& value) { m_vScale = value; m_bMatrixDirty = true; }

	inline const Quaternion& GetLocalRotation() const { return m_qRotation; }

	inline void SetLocalRotation(const Quaternion& value) { m_qRotation = value; m_bMatrixDirty = true; }

	inline Vector3 GetLocalEulerRotation() const { return m_qRotation.ToEulerAngle(); }

	inline void SetLocalEulerRotation(const Vector3& value) { m_qRotation.FromEulerAngle(value); m_bMatrixDirty = true; }

	inline void LookAt(const Vector3& worldPosition) { LookAt(worldPosition, Vector3::Up()); }

	inline void LookAt(const Vector3& worldPosition, const Vector3& worldUp) { _LookAt(m_vPosition, worldPosition, worldUp); }

	Vector3 Forward() const {Vector3 _out(m_mMatrix.GetColumn(2)); _out.Normalize(); return _out; }

	Vector3 Back() const { Vector3 _out(m_mMatrix.GetColumn(2)); _out.Normalize(); return -_out; }

	Vector3 Right() const { Vector3 _out(m_mMatrix.GetColumn(0)); _out.Normalize(); return _out; }

	Vector3 Left() const { Vector3 _out(m_mMatrix.GetColumn(0)); _out.Normalize(); return -_out; }

	Vector3 Up() const { Vector3 _out(m_mMatrix.GetColumn(1)); _out.Normalize(); return _out; }

	Vector3 Down() const { Vector3 _out(m_mMatrix.GetColumn(1)); _out.Normalize(); return -_out; }

	protected:
	Transform() {};

	void _LookAt(const Vector3& origin, const Vector3& worldPosition, const Vector3& worldUp);

	private:
	void _CheckMatrixUpdate() const;

	void _UpdateMatrix() const;
};

class IComponent {
	friend class GameObject;

	protected:
	GameObject & m_gGameObject;
	Transform& m_tTransform;

	public:
	~IComponent() {};

	protected:
	IComponent() = delete;
	IComponent(GameObject& gobj);

	private:

};

class GameObject {
	protected:
	Transform m_tTransform;

	std::vector<IComponent*> m_vComponents;
	public:
	GameObject() {};
	~GameObject();

	inline Transform& GetTransform() { return m_tTransform; }

	template<typename T, class ...Args>
	T& AddComponent(Args && ...args);

	private:

};