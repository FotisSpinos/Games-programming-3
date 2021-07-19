#include "DebugMotionComponent.h"
#include "Entity.h"
#include "pch.h"
#include "QuaternionHelper.h"

DebugMotionComponent::DebugMotionComponent(float motionSpeed, float rotationSpeed) :
	m_motionSpeed(motionSpeed), m_rotationSpeed(rotationSpeed), m_motionProgress(0)
{
}

void DebugMotionComponent::OnAttach()
{
}

void DebugMotionComponent::OnUpdate(float deltaTime)
{
	m_entity->GetTransform()->AddPosition(glm::vec3(sinf(m_motionProgress * m_motionSpeed), 0.0f, 0.0f));
	m_entity->GetTransform()->AddRotation(QuaternionHelper::AngleToQuaternion(m_rotationSpeed * deltaTime, m_entity->GetTransform()->GetUp()));

	m_motionProgress += deltaTime;
}

void DebugMotionComponent::OnRender()
{
}
