#pragma once
#include"Collider.h"

namespace RayTraceRenderer
{
	class RayTraceCamera
	{
		//改成挂个transform或者写成unity的component形式来控制位置
		private:
		//vector3缓存，用于加快运算速度
		Vector3 m_vOrigin;
		Vector3 m_vHorizontal;
		Vector3 m_vVertical;
		Vector3 m_vLowLeftCorner;

		protected:
		double m_fWidth = 0;
		double m_fHeight = 0;
		double m_fAspect = 1;

		//Color ** frameBuffer = nullptr; //后面可以再封装一层


		public:
		RayTraceCamera(double width, double height) :
			m_fWidth(width), m_fHeight(height), m_fAspect(width / height) {
			//之后考虑看看能不能从矩阵中取出
			m_vOrigin.SetTo(0, 0, 0);
			m_vHorizontal.SetTo(m_fWidth, 0, 0);
			m_vVertical.SetTo(0, m_fHeight, 0);
			m_vLowLeftCorner.SetTo(-m_fWidth * 0.5, -m_fHeight * 0.5, -1);//最后这个值以后通过fov算出来
		}

		~RayTraceCamera() {}

		void DrawToBuffer(Color** frameBuffer, const ColliderList& colliderObjects, unsigned int pixelHeight);

		protected:
		void _GetRay(Ray& ray, double u, double v);

		void _RayCatchColor(const Ray& ray, const ColliderList& colliderObjects, Color& col);

		private:

	};
}