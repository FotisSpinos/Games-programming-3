#pragma once

#include "Component.h"
#include "pch.h"
#include "LightingEnvironment.h"
#include "Entity.h"
#include "MeshRenderer.h"
#include "Resources.h"

class PointLight : public Component, public std::enable_shared_from_this<PointLight>
{
public:

	PointLight(float intensity, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor) :
		m_intensity(intensity), m_specularExponent(32.0f), m_attenuation(0.0001f)
	{
		VectorHelper::Vec3TofloatArray(ambientColor, m_ambientColor);
		VectorHelper::Vec3TofloatArray(diffuseColor, m_diffuseColor);
		VectorHelper::Vec3TofloatArray(specularColor, m_specularColor);
	}

	PointLight()
	{

	}

	void SetSpecularExponent(float specularExponent) {
		m_specularExponent = specularExponent;
	}

	void SetAtteniation(float attenuation) {
		m_attenuation = attenuation;
	}

	virtual void OnAttach() override
	{
		//SpawnBox 
		m_entity->AddComponent(
			std::make_shared<MeshRenderer>(
				Resources::GetInstance()->GetModel("SimpleCube.obj"),
				Resources::GetInstance()->GetShader("simpleColor"),
				Resources::GetInstance()->GetTexture("crate_1 texture.jpg")));

		//Add To light Environment
		std::shared_ptr<PointLight> light = shared_from_this();
		LightingEnvironment::GetInstance()->AddPointLight(light);
	}

	virtual void OnRender() override {};
	virtual void OnUpdate(float deltaTime) override 
	{
		VectorHelper::Vec3TofloatArray(m_entity->GetTransform()->GetPosition(), m_position);
	};

	glm::vec3* GetPosition()
	{
		if(m_entity != nullptr)
			return &m_entity->GetTransform()->GetPosition();
		return nullptr;
	}

	float m_intensity;
	float m_ambientColor[3] = {0};
	float m_diffuseColor[3] = {0};
	float m_specularColor[3] = {0};

	float m_position[3] = { 0 };

	float m_specularExponent = 0;
	float m_attenuation = 0;
};