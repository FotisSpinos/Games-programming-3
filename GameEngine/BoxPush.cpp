#include "BoxPush.h"
#include "Physics.h"
#include "BoxShape.h"
#include "Input.h"

void BoxPush::OnAttach()
{
	std::shared_ptr<RigidBody> rb = m_entity->GetComponent<RigidBody>();

	if (rb.use_count() == 0)
	{
		rb = m_entity->AddComponent<RigidBody>();
		rb->Init(new BoxShape(glm::vec3(0.1f, 0.1f, 0.1f)));
	}

	m_rigidBody = rb;
}

void BoxPush::OnUpdate(float deltaTime)
{
	if (INPUT->GetKey(SDLK_UP))
	{		
		this->m_rigidBody->ApplyForce(glm::vec3(0.0f, 0.0f, m_motionForce));
	}
	
	if (INPUT->GetKey(SDLK_DOWN))
	{
		this->m_rigidBody->ApplyForce(glm::vec3(0.0f, 0.0f, -m_motionForce));
	}

	if (INPUT->GetKey(SDLK_RIGHT))
	{
		this->m_rigidBody->ApplyTorque(glm::vec3(0.0f, m_rotationForce, 0.0f));
	}

	if (INPUT->GetKey(SDLK_LEFT))
	{
		this->m_rigidBody->ApplyTorque(glm::vec3(0.0f, -m_rotationForce, 0.0f));
	}
}

void BoxPush::OnRender()
{
}

BoxPush::BoxPush() : 
m_rotationForce(10.0f), m_motionForce(10.0f)
{
}

BoxPush::BoxPush(float rotationForce, float motionForce) :
	m_rotationForce(rotationForce), m_motionForce(motionForce)
{
}
