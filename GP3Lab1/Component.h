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
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender() = 0;
	virtual void OnAttach() {};

	virtual void OnCollision(std::shared_ptr<RigidBody> rb) {};
	virtual void OnCollisionEnter(std::shared_ptr<RigidBody> rb) {};
	virtual void OnCollisionExit(std::shared_ptr<RigidBody> rb) {};
};