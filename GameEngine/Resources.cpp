#include "Resources.h"
#include "pch.h"

Resources* Resources::m_instance;

Resources::Resources()
{

}

Resources::~Resources()
{
	delete m_instance;
}

Resources* Resources::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Resources();
	}

	return m_instance;
}

void Resources::AddModel(const std::string& directory)
{
	if (m_models.find(directory) == m_models.end())
	{
		m_models[directory] = std::make_shared<Model>(ASSETS_PATH + directory);
		LOG_DEBUG("Model Loaded from " + directory);
	}
}

void Resources::AddTexture(const std::string& directory)
{
	if (m_textures.find(directory) == m_textures.end())
	{
		m_textures[directory] = std::make_shared<Texture>(ASSETS_PATH + directory);
		LOG_DEBUG("Texture Loaded from " + directory);
	}
}

void Resources::AddHeightMap(const std::string& directory)
{
	if (m_heightMaps.find(directory) == m_heightMaps.end())
	{
		m_heightMaps[directory] = std::make_shared<HeightMap>(ASSETS_PATH + directory);
		LOG_DEBUG("HeightMap Loaded from " + directory);
	}
}

std::shared_ptr<ShaderProgram> Resources::GetShader(const std::string& name)
{
	return m_shaderPrograms[name];
}

std::shared_ptr<Model> Resources::GetModel(const std::string& name)
{
	return m_models[name];
}

std::shared_ptr<Texture> Resources::GetTexture(const std::string& name)
{
	return m_textures[name];
}

std::shared_ptr<HeightMap> Resources::GetHeightMap(const std::string& name)
{
	return m_heightMaps[name];
}

void Resources::ReleaseResources()
{
	// release models
	for (auto iter = m_models.begin(); iter != m_models.end(); iter++)
		iter->second.reset();

	//release shaders
	for (auto iter = m_shaderPrograms.begin(); iter != m_shaderPrograms.end(); iter++)
		iter->second.reset();

	//delete textures
	for (auto iter = m_textures.begin(); iter != m_textures.end(); iter++)
		iter->second.reset();

	//delete heightMaps
	for (auto iter = m_heightMaps.begin(); iter != m_heightMaps.end(); iter++)
		iter->second.reset();
}

void Resources::ReleaseUnusedResources()
{

	for (auto iter = m_models.begin(); iter != m_models.end(); iter++)
	{
		if (iter->second.use_count() == 1)
		{
			iter->second.reset();
		}
	}

	for (auto iter = m_shaderPrograms.begin(); iter != m_shaderPrograms.end(); iter++)
	{
		if (iter->second.use_count() == 1)
		{
			iter->second.reset();
		}
	}

	for (auto iter = m_textures.begin(); iter != m_textures.end(); iter++)
	{
		if (iter->second.use_count() == 1)
		{
			iter->second.reset();
		}
	}

	for (auto iter = m_heightMaps.begin(); iter != m_heightMaps.end(); iter++)
	{
		if (iter->second.use_count() == 1)
		{
			iter->second.reset();
		}
	}
}