#pragma once
#include "pch.h"
#include "CollisionShape.h"

class ConeShape : public CollisionShape
{
private:
	float m_radious;
	float m_height;
public:
	ConeShape(float height, float radious);
};