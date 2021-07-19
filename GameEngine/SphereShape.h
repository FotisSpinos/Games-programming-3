#pragma once

#include "pch.h"
#include "CollisionShape.h"

class SphereShape : public CollisionShape
{
private:
	float m_radious;
public:
	SphereShape(float radious);
};
