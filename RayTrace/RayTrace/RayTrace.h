#pragma once
#include"CommonDefine.h"

namespace RayTraceRenderer
{
	class RayTraceCamera
	{
		//�ĳɹҸ�transform����д��unity��component��ʽ������λ��
		private:
		//vector3���棬���ڼӿ������ٶ�,֮���ǿ����ܲ��ܴӾ�����ȡ��
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