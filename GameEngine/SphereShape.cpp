#include "SphereShape.h"

SphereShape::SphereShape(float radious)
{
	m_radious = radious;
	m_shape = new btSphereShape(radious);
	m_type = CShapeType::SPHERE;
}
