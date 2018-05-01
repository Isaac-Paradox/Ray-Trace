#pragma once
#include "../CoreDefine/CommonDefine.h"
#include "../Collider/Collider.h"

class IMaterial
{
	public:
	virtual bool Scatter(Ray& ray, const RayCastHitRecord& record, Color& attenuation) const = 0;
};