#include "ConeShape.h"

ConeShape::ConeShape(float height, float radious)
{
	m_radious = radious;
	m_height = height;

	m_shape = new btConeShape(m_radious, m_height);
	m_type = CShapeType::CONE;
}