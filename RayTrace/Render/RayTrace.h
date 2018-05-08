#pragma once
#include<math.h>
#include "../Object/GameObject.h"
#include "RenderTarget.h"
#include"../Collider/Collider.h"
#include"../Material/Material.h"

namespace RayTraceRenderer
{
	class RayTraceCamera : public IComponent
	{
		private:
		const unsigned int c_nSample = 16;
		const int c_nMaxStep = 64;
		const Color c_cSkyBoyLow = Color(1.0f, 1.0f, 1.0f);//暂时代替天空盒用
		const Color c_cSkyBoyTop = Color(0.5f, 0.7f, 1.0f);

		//vector3缓存，用于加快运算速度
		Vector3 m_vOrigin;
		Vector3 m_vHorizontal;
		Vector3 m_vVertical;
		Vector3 m_vLowLeftCorner;

		protected:
		RenderTarget & m_rTarget;

		float m_fNear = 0.3f;
		float m_fFar = 1000.0f;

		bool m_bOrthographic = false;//还没实现平行投影

		//Orthographic
		float m_fOrthographicSize = 5.0f;

		//Perspective
		float m_fFov = 60.0f;

		bool m_bOpenDepthOfField = false;
		float m_fLensRadius = 1.0f;
		float m_fFocus = 10.0f;


		bool m_bPerspectiveDataDirty = true;

		public:
		RayTraceCamera(GameObject& gobj, RenderTarget & target) : IComponent(gobj), m_rTarget(target) {}//后面通过factory把构造函数写到protected里面
		~RayTraceCamera() {}

		void Draw(const ColliderList& colliderObjects);

		inline float Aspect() const {
			return (float)m_rTarget.Width() / m_rTarget.Height();
		}

		inline float GetNear() const { return m_fNear; }

		inline void SetNear(float value) { m_fNear = value; m_bPerspectiveDataDirty = true; }

		inline float GetFar() const { return m_fFar; }

		inline void SetFar(float value) { m_fFar = value; m_bPerspectiveDataDirty = true; }

		inline float GetOrthographicSize() const { return m_fOrthographicSize; }

		inline void SetOrthographicSize(float value) { m_fOrthographicSize = value; m_bPerspectiveDataDirty = true; }

		inline float GetFov() const { return m_fFov; }

		inline void SetFov(float value) { m_fFov = value; m_bPerspectiveDataDirty = true; }

		inline bool DepthOfFieldActive() const { return m_bOpenDepthOfField; }

		inline void OpenDepthOfField(float value) { m_fLensRadius = value * 0.5f; m_bOpenDepthOfField = true; m_bPerspectiveDataDirty = true; }

		inline void CloseDepthOfField() { m_bOpenDepthOfField = false; m_bPerspectiveDataDirty = true; }

		inline float GetAperture() const { return m_fLensRadius * 2.0f; }

		inline float GetFocus() const { return m_fFocus; }

		inline void SetFocus(float value) { m_fFocus = value; if(m_bOpenDepthOfField) m_bPerspectiveDataDirty = true; }

		protected:

		inline void _GetRay(Ray& ray, float u, float v) const;

		void _RayCatchColor(Ray& ray, const ColliderList& colliderObjects, Color& col, int step = 0);//ray不用const,复用同一个,减少内存申请释放

		void _WriteColor(Color& target, const Color& value);

		private:
		void _UpdateRayScanData();
	};
}