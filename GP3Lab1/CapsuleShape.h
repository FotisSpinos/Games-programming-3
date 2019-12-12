#pragma once

#include "pch.h"
#include "CollisionShape.h"

class CapsuleShape : public CollisionShape
{
private:
	float m_radious;
	float m_height;
public:
	CapsuleShape(float radious, float height);
};
