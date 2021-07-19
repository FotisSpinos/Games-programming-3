#pragma once
#include "pch.h"
#include "Common.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "HeightMap.h"

class Resources
{
private:
	std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaderPrograms;
	std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
	std::unordered_map<std::string, std::shared_ptr<HeightMap>> m_heightMaps;

	static Resources* m_instance;
	Resources();
	~Resources();

public:
	static Resources* GetInstance();
	//adds shader to the map, should be done at the start of application
	void AddShader(std::shared_ptr<ShaderProgram> shader, std::string name) {
		m_shaderPrograms[name] = shader;
	}
	void AddModel(const std::string& directory);
	void AddModel(const std::string& name, std::shared_ptr<Model> m) {
		m_models[name] = m;
	}
	void AddTexture(const std::string& dictionary);
	void AddTexture(const std::string& name, std::shared_ptr<Texture> t) {
		m_textures[name] = t; };

	void AddHeightMap(const std::string& dictionary);
	void AddHeightMap(const std::string& name, std::shared_ptr<HeightMap> h) {
		m_heightMaps[name] = h;
	}
		
	std::shared_ptr<ShaderProgram> GetShader(const std::string& name);
	std::shared_ptr<Model> GetModel(const std::string& name);
	std::shared_ptr<Texture> GetTexture(const std::string& name);
	std::shared_ptr<HeightMap> GetHeightMap(const std::string& name);

	//Deletes all the things!
	void ReleaseResources();
	void ReleaseUnusedResources();
};