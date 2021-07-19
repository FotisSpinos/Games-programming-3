#include "LightingEnvironment.h"
#include "VectorHelper.h"
#include "PointLight.h"
#include "ShaderProgram.h"

LightingEnvironment* LightingEnvironment::m_instance;

LightingEnvironment* LightingEnvironment::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new LightingEnvironment();
	}

	return m_instance;
}

LightingEnvironment::LightingEnvironment() : 
	m_lightCount(0)
{
}

LightingEnvironment::~LightingEnvironment()
{
	delete m_instance;
}

void LightingEnvironment::AddPointLight(std::shared_ptr<PointLight> pointLight)
{
	// store point light
	m_pointLights.push_back(pointLight);
	m_lightCount++;
}

void LightingEnvironment::PassPointLightsToShader(std::shared_ptr<ShaderProgram> m_program)
{
	int size, loc;
	
	size = m_pointLights.size();	
	loc = glGetUniformLocation(m_program->Get(), "lightsCount");
	glProgramUniform1i(m_program->Get(), loc, size);

	for (int i = 0; i < m_pointLights.size(); i++)
	{
		// lights index string
		std::string lightsInx = std::string("lights[") + std::to_string(i) + std::string("].");

		// Set position
		loc = glGetUniformLocation(m_program->Get(), (lightsInx + std::string("pos")).c_str());
		glProgramUniform3fv(m_program->Get(), loc, 1, (GLfloat*) &m_pointLights[i]->m_position);

		// Set ambient
		loc = glGetUniformLocation(m_program->Get(), (lightsInx + std::string("ambient")).c_str());
		glProgramUniform3fv(m_program->Get(), loc, 1, m_pointLights[i]->m_ambientColor);

		// Set diffuse
		loc = glGetUniformLocation(m_program->Get(), (lightsInx + std::string("diffuse")).c_str());
		glProgramUniform3fv(m_program->Get(), loc, 1, m_pointLights[i]->m_diffuseColor);

		// Set specular
		loc = glGetUniformLocation(m_program->Get(), (lightsInx + std::string("specular")).c_str());
		glProgramUniform3fv(m_program->Get(), loc, 1, m_pointLights[i]->m_specularColor);

		// Set specular exponent
		loc = glGetUniformLocation(m_program->Get(), (lightsInx + std::string("specularExponent")).c_str());
		glProgramUniform1fv(m_program->Get(), loc, 1, &m_pointLights[i]->m_specularExponent);

		//Pass attenuation to shader
		loc = glGetUniformLocation(m_program->Get(), (lightsInx + std::string("attenuation")).c_str());
		glProgramUniform1fv(m_program->Get(), loc, 1, &m_pointLights[i]->m_attenuation);

		//Pass attenuation to shader
		loc = glGetUniformLocation(m_program->Get(), (lightsInx + std::string("intensity")).c_str());
		glProgramUniform1fv(m_program->Get(), loc, 1, &m_pointLights[i]->m_intensity);
	}
}
