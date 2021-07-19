#pragma once
#include "pch.h"
//forward declaring to avoid circular includes
class Entity;
class RigidBody;

class Component
{
protected:
	Entity* m_entity = nullptr;
	friend class Entity;

public:

	// Called to update the object's state
	virtual void OnUpdate(float deltaTime) = 0;

	//Called to render the object
	virtual void OnRender() = 0;

	//Called when a compoennt is attached to an entity 
	virtual void OnAttach() {};

	// Called when the entity collides with another rigidbody
	virtual void OnCollision(std::shared_ptr<RigidBody> rb) {};

	// Called if a collision start in the current frame
	virtual void OnCollisionEnter(std::shared_ptr<RigidBody> rb) {};

	// Called when a collision stops in the current frame
	virtual void OnCollisionExit(std::shared_ptr<RigidBody> rb) {};
};