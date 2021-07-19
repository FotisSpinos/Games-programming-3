#include "RigidBody.h"
#include "pch.h"
#include "Entity.h"


void RigidBody::ApplyForce(glm::vec3 direction)
{
	m_rigidBody->applyCentralForce(btVector3(direction.x, direction.y, direction.z));
}

void RigidBody::ApplyImpulse(glm::vec3 direction)
{
	m_rigidBody->applyCentralImpulse(btVector3(direction.x, direction.y, direction.z));
}

void RigidBody::ApplyTorque(glm::vec3 direction)
{
	m_rigidBody->applyTorque(btVector3(direction.x, direction.y, direction.z));
}

RigidBody::~RigidBody()
{
	//Remove from physics environment

	//clear memory
	delete m_mState;
	delete m_rigidBody;
	delete m_shape;
}

void RigidBody::OnUpdate(float deltaTime)
{
}

void RigidBody::OnRender()
{
}

void RigidBody::OnCollision(std::shared_ptr<RigidBody> rb)
{
}

void RigidBody::OnCollisionEnter(std::shared_ptr<RigidBody> rb)
{
}

void RigidBody::OnCollisionExit(std::shared_ptr<RigidBody> rb)
{
}

void RigidBody::CollisionOccured(std::shared_ptr<RigidBody> rb)
{
	m_collidedBodies.insert(rb);
}

void RigidBody::Init(CollisionShape* shape, float mass, const glm::vec3 localInertia, const glm::vec3 shapeOffset)
{
	//Apply shape offset
	m_entity->GetTransform()->AddPosition(shapeOffset);

	btTransform bT = Physics::ConvertTransformToBtTransform(*m_entity->GetTransform());
	m_mState = new btDefaultMotionState(bT);
	m_shape = shape;
	btVector3 li = btVector3(localInertia.x, localInertia.y, localInertia.z);
	m_shape->Get()->calculateLocalInertia(mass, li);
	m_rigidBody = new btRigidBody(btScalar(mass), m_mState, m_shape->Get(), li);
	Physics::GetInstance()->AddRigidbody(shared_from_this());
	m_rigidBody->setSleepingThresholds(0, 0);
	m_rigidBody->setFriction(1);
}

void RigidBody::UpdateParent()
{
	glm::vec3 position = glm::vec3(m_rigidBody->getCenterOfMassTransform().getOrigin().getX(), 
		m_rigidBody->getCenterOfMassTransform().getOrigin().getY(),
		m_rigidBody->getCenterOfMassTransform().getOrigin().getZ());

	glm::quat rotation = glm::quat(m_rigidBody->getCenterOfMassTransform().getRotation().getW(),
		m_rigidBody->getCenterOfMassTransform().getRotation().getX(),
		m_rigidBody->getCenterOfMassTransform().getRotation().getY(),
		m_rigidBody->getCenterOfMassTransform().getRotation().getZ());

	this->m_entity->GetTransform()->SetPosition(position);
	this->m_entity->GetTransform()->SetRotation(rotation);
}

void RigidBody::UpdateRigidBody()
{
	btTransform t = Physics::ConvertTransformToBtTransform(*m_entity->GetTransform());
	m_rigidBody->setWorldTransform(t);
	m_rigidBody->getMotionState()->setWorldTransform(t);
}