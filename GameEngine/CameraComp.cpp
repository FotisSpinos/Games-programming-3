#include "pch.h"
#include "CameraComp.h"
#include "Camera.h"
#include "Input.h"


void CameraComp::OnUpdate(float deltaTime)
{
}

void CameraComp::OnRender()
{
}

void CameraComp::OnAttach()
{
	m_camera = std::make_shared<Camera>(m_entity->GetTransform());
	if (Application::GetInstance()->GetCamera() == nullptr)
	{
		Application::GetInstance()->SetCamera(m_camera);
	}
}
