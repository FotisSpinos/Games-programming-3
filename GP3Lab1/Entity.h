#pragma once
#include "pch.h"
#include "Transform.h"
#include "Component.h"
#include "Log.h"

class Entity
{
protected:
	std::vector<std::shared_ptr<Component>> m_components;
	Transform* m_transform = nullptr;
public:
	Entity();
	void AddComponent(std::shared_ptr<Component> c);
	template<class T> void AddComponent();
	template<class T> std::shared_ptr<T> GetComponent();

	virtual void CollisionUpdate();
	virtual void OnUpdate(float deltaTime);
	virtual void OnRender();

	Transform* GetTransform() { return m_transform; };

	std::string name;
};

template<class T>
void Entity::AddComponent()
{
	std::shared_ptr<T> t = std::make_shared<T>();
	std::shared_ptr<Component> c = std::dynamic_pointer_cast<Component>(t);
	if (c != nullptr)
	{
		c->m_entity = this;
		m_components.push_back(c);
		c->OnAttach();
	}
	else
	{
		LOG_DEBUG("Can't add component, does not inherit from Component");
	}
}

template<class T>
std::shared_ptr<T> Entity::GetComponent()
{
	std::shared_ptr<T> t = std::make_shared<T>();

	std::shared_ptr<Component> c = std::dynamic_pointer_cast<Component>(t);

	if (c == nullptr)
	{
		return nullptr;
	}

	for (std::shared_ptr<Component> c : m_components)
	{
		std::shared_ptr<T> compToType = std::dynamic_pointer_cast<T>(c);
		if (compToType != nullptr)
			return compToType;
	}

	return nullptr;
}