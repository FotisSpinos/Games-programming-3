#include "FirstPersonCamera.h"
#include "QuaternionHelper.h"

float quaternionY= 0.0f;
float dir = -1.0f;


FirstPersonCamera::FirstPersonCamera(float motionSpeed, float rotationSpeed) :
	m_motionSpeed(motionSpeed), m_rotationSpeed(rotationSpeed)
{

}

void FirstPersonCamera::OnRender()
{

}

void FirstPersonCamera::OnUpdate(float deltaTime)
{
	//Move Camera
	float displacement = m_motionSpeed * deltaTime;

	if (INPUT->GetInstance()->GetKey(SDLK_a))
		this->m_entity->GetTransform()->AddPosition(this->m_entity->GetTransform()->GetRight() * -displacement);

	if(INPUT->GetInstance()->GetKey(SDLK_d))
		this->m_entity->GetTransform()->AddPosition(this->m_entity->GetTransform()->GetRight() * displacement);

	if (INPUT->GetKey(SDL_BUTTON_RIGHT))
	{
		if (INPUT->GetInstance()->GetKey(SDLK_w))
			this->m_entity->GetTransform()->AddPosition(this->m_entity->GetTransform()->GetForward() * displacement);
		if (INPUT->GetInstance()->GetKey(SDLK_s))
			this->m_entity->GetTransform()->AddPosition(this->m_entity->GetTransform()->GetForward() * -displacement);
	}
	else
	{
		if (INPUT->GetInstance()->GetKey(SDLK_w))
			this->m_entity->GetTransform()->AddPosition(this->m_entity->GetTransform()->GetUp() * displacement);
		if (INPUT->GetInstance()->GetKey(SDLK_s))
			this->m_entity->GetTransform()->AddPosition(-this->m_entity->GetTransform()->GetUp() * displacement);
	}

	//Rotate Camera
	glm::vec2 mouseDelta = INPUT->GetMouseDelta();
	float angleX = -mouseDelta.x * deltaTime * m_rotationSpeed;
	float angleY = -mouseDelta.y * deltaTime * m_rotationSpeed;

	glm::quat rotationX = QuaternionHelper::AngleToQuaternion(angleY, this->m_entity->GetTransform()->GetRight());
	glm::quat rotationY = QuaternionHelper::AngleToQuaternion(angleX, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::quat objRot = this->m_entity->GetTransform()->GetRotation();

	// Note: Quaternion multiplication adds rotation angles
	this->m_entity->GetTransform()->SetRotation(rotationY * rotationX * objRot);

	// Reset rotations when "r" is pressed
	if (INPUT->GetInstance()->GetKey(SDLK_r))
		this->m_entity->GetTransform()->SetRotation(QuaternionHelper::AngleToQuaternion(0, this->m_entity->GetTransform()->GetRight()));
}

void FirstPersonCamera::OnAttach()
{
	//Call parent class
	CameraComp::OnAttach();
}