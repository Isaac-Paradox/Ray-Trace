#pragma once
#include<math.h>
#include"Collider.h"

namespace RayTraceRenderer
{
	class RayTraceCamera
	{
		//改成挂个transform或者写成unity的component形式来控制位置

		private:
		const unsigned int c_nSample = 32;
		const int c_nMaxStep = 32;
		const Color c_cSkyBoyLow = Color(1.0f, 1.0f, 1.0f);//暂时代替天空盒用
		const Color c_cSkyBoyTop = Color(0.5f, 0.7f, 1.0f);

		//vector3缓存，用于加快运算速度
		Vector3 m_vOrigin;
		Vector3 m_vHorizontal;
		Vector3 m_vVertical;
		Vector3 m_vLowLeftCorner;

		protected:
		float m_fWidth = 0;
		float m_fHeight = 0;
		float m_fAspect = 1;

		//Color ** frameBuffer = nullptr; //后面可以再封装一层


		public:
		RayTraceCamera(float width, float height)
			: m_fWidth(width), m_fHeight(height), m_fAspect(width / height) {
			//之后考虑看看能不能从矩阵中取出
			m_vOrigin.SetTo(0, 0, 0);
			m_vHorizontal.SetTo(m_fWidth, 0, 0);
			m_vVertical.SetTo(0, m_fHeight, 0);
			m_vLowLeftCorner.SetTo(-m_fWidth * 0.5f, -m_fHeight * 0.5f, -1);//最后这个值以后通过fov算出来
		}

		~RayTraceCamera() {}

		void DrawToBuffer(Color** frameBuffer, const ColliderList& colliderObjects, unsigned int pixelHeight);

		protected:
		void _GetRay(Ray& ray, float u, float v);

		void _RayCatchColor(Ray& ray, const ColliderList& colliderObjects, Color& col, int step = 0);//ray先不用const复用同一个，后面有问题了再每次重新生成一个

		void _WriteColor(Color& target, const Color& value);

		private:

	};
}