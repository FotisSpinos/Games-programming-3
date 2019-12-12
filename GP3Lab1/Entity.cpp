#include "pch.h"
#include "Entity.h"
#include "RigidBody.h"

Entity::Entity()
{
	m_transform = new Transform();
}

void Entity::AddComponent(std::shared_ptr<Component> c)
{
	c->m_entity = this;
	m_components.push_back(c);
	c->OnAttach();
}

void Entity::OnUpdate(float deltaTime)
{
	for (auto& c : m_components)
	{
		c->OnUpdate(deltaTime);
	}
}

void Entity::OnRender()
{
	for (auto& c : m_components)
	{
		c->OnRender();
	}
}

void Entity::CollisionUpdate()
{
	std::shared_ptr<RigidBody> rb = GetComponent<RigidBody>();

	if (rb == nullptr)
		return;
	
	for (const auto& iter : *rb->GetCollidedBodies())
	{
		for (auto& c : m_components)
		{
			if (rb->GetPrevColldedBodies()->empty() || rb->GetPrevColldedBodies()->find(iter) == rb->GetPrevColldedBodies()->end())
				c->OnCollisionEnter(iter);

			c->OnCollision(iter);
		}
	}


	*rb->GetPrevColldedBodies() = *rb->GetCollidedBodies();

	//m_prevCollidedBodies = m_collidedBodies;
	rb->GetCollidedBodies()->clear();
}
