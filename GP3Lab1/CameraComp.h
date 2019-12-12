#pragma once
#include "Component.h"
#include "Camera.h"
class CameraComp : public Component
{
protected:
	std::shared_ptr<Camera> m_camera;
	// Inherited via Component
public:
	CameraComp() {}
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
	virtual void OnAttach() override;
};