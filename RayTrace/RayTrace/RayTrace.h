#pragma once
#include"CommonDefine.h"

namespace RayTraceRenderer
{
	class RayTraceCamera
	{
		//改成挂个transform或者写成unity的component形式来控制位置
		private:
		//vector3缓存，用于加快运算速度,之后考虑看看能不能从矩阵中取出
		//static Vector3 s_vOrigin;
		//static Vector3 s_vHorizontal;
		//static Vector3 s_vVertical;
		//static Vector3 s_vLowLeftCorner;

		protected:
		double m_fWidth = 0;
		double m_fHeight = 0;
		double m_fAspect = 1;

		public:
		RayTraceCamera(double width, double height) : 
			m_fWidth(width), m_fHeight(height), m_fAspect(width / height) { }

		~RayTraceCamera() {}

		void DrawToBuffer(Color** frameBuffer, unsigned int pixelHeight);

		protected:
		Color _RayCatchColor(const Ray& ray);

		private:

	};
}