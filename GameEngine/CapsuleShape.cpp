#include "CapsuleShape.h"

CapsuleShape::CapsuleShape(float radious, float height) :
	m_radious(radious), m_height(height)
{
	m_shape = new btCapsuleShape(radious, height);
	m_type = CShapeType::CAPSULE;
}
