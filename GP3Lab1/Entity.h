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
	template<class T> std::shared_ptr<T> AddComponent();
	template<class T> std::shared_ptr<T> GetComponent();

	void CollisionUpdate();
	void OnUpdate(float deltaTime);
	void OnRender();

	Transform* GetTransform() { return m_transform; };

	std::string name;
};

template<class T>
std::shared_ptr<T> Entity::AddComponent()
{
	//Create a shared pointer
	std::shared_ptr<T> t = std::make_shared<T>();

	//Dynamicly cast the object to a Component
	std::shared_ptr<Component> c = std::dynamic_pointer_cast<Component>(t);

	//Check if the type is a component
	if (c != nullptr)
	{
		c->m_entity = this;
		m_components.push_back(c);
		c->OnAttach();
		return t;
	}
	else
	{
		LOG_WARNING("Can't add component, does not inherit from Component");
		return std::shared_ptr<T>();
	}
}

template<class T>
std::shared_ptr<T> Entity::GetComponent()
{
	std::shared_ptr<T> t = std::make_shared<T>();

	//Casts type to a component
	std::shared_ptr<Component> c = std::dynamic_pointer_cast<Component>(t);

	if (c == nullptr)
	{
		//return null if cast is unsuccessful
		LOG_WARNING("GetComponent cannot use a non conponent type object");
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