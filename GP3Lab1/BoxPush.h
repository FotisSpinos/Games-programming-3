#pragma once
#include "pch.h"
#include "Component.h"
#include "RigidBody.h"
#include "Entity.h"

class BoxPush : public Component
{
public:
	virtual void OnAttach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	BoxPush();
	BoxPush(float rotationForce, float motionForce);

protected:
	std::shared_ptr<RigidBody> m_rigidBody;

	float m_rotationForce;
	float m_motionForce;
};