#pragma once

#include "pch.h"
#include "Component.h"

class ShaderProgram;
class PointLight;

class LightingEnvironment
{
private:
	static LightingEnvironment* m_instance;
	std::vector<std::shared_ptr<PointLight>> m_pointLights;

	int m_lightCount;

public:
	static LightingEnvironment* GetInstance();

	LightingEnvironment();
	~LightingEnvironment();

	void AddPointLight(std::shared_ptr<PointLight> pointLight);
	void PassPointLightsToShader(std::shared_ptr<ShaderProgram> m_program);
};