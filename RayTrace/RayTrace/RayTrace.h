#pragma once
#include"CommonDefine.h"

namespace RayTraceRenderer
{
	class RayTrace
	{
	public:
		RayTrace(){}
		~RayTrace(){}

		void DrawToBuffer(Color** frameBuffer, unsigned int width, unsigned int height);

	private:

	};
}