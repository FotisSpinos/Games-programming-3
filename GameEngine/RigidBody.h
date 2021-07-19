#pragma once
#include "Component.h"
#include "Physics.h"
#include "CollisionShape.h"


class RigidBody : public Component, public std::enable_shared_from_this<RigidBody>
{
private:
	CollisionShape* m_shape;
	btRigidBody* m_rigidBody;
	btMotionState* m_mState = nullptr;
	float m_mass;
	std::unordered_set<std::shared_ptr<RigidBody>> m_collidedBodies;
	std::unordered_set<std::shared_ptr<RigidBody>> m_prevCollidedBodies;

public:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	virtual void OnCollision(std::shared_ptr<RigidBody> rb);
	virtual void OnCollisionEnter(std::shared_ptr<RigidBody> rb);
	virtual void OnCollisionExit(std::shared_ptr<RigidBody> rb);

	void CollisionOccured(std::shared_ptr<RigidBody> rb);

	std::unordered_set<std::shared_ptr<RigidBody>>* GetCollidedBodies() { return &m_collidedBodies; }
	std::unordered_set<std::shared_ptr<RigidBody>>* GetPrevColldedBodies() { return &m_prevCollidedBodies; }

	void Init(CollisionShape* shape, float mass = 1.f, const glm::vec3 localInertia = glm::vec3(1), const glm::vec3 shapeOffset = glm::vec3());
	virtual void UpdateParent();
	virtual void UpdateRigidBody();
	btRigidBody* Get() { return m_rigidBody; }
	
	void ApplyForce(glm::vec3 direction);
	void ApplyImpulse(glm::vec3 direction);
	void ApplyTorque(glm::vec3 direction);

	~RigidBody();
};