#pragma once
#include "Camera.h"
#include "Component.h"
#include "Input.h"
#include "CameraComp.h"

class FirstPersonCamera : public CameraComp
{
private:
	//std::shared_ptr<Camera> m_camera;
	float m_motionSpeed;
	float m_rotationSpeed;

public:
	FirstPersonCamera(float motionSpeed, float rotationSpeed);

	virtual void OnRender() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnAttach() override;
};