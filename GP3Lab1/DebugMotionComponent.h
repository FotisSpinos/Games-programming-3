#pragma once
#include "Component.h"

class DebugMotionComponent : public Component
{
public:
	DebugMotionComponent(float motionSpeed, float rotationSpeed);

	virtual void OnAttach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

private:
	float m_motionSpeed;
	float m_rotationSpeed;

	float m_motionProgress;
};