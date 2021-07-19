#pragma once
#include "Component.h"

class DebugInputControlsComp : public Component
{
public:
	void OnAttach() override;
	void OnUpdate(float deltaTime) override;
	void OnRender() override;

private:
	float motionSpeed;
	float rotationSpeed;


};

