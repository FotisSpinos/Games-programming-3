#pragma once
#include "Entity.h"
#include "pch.h"
#include "Mesh.h"
#include "HeightMap.h"
#include "MeshRenderer.h"

class Terrain : public Component
{
public:
	Terrain(std::shared_ptr<HeightMap> heightMap, float xSize, float ySize);

	void UpdateMesh();

	virtual void OnRender() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnAttach() override;

	//Setters / Getters 
	std::shared_ptr<Mesh> GetMesh();
	void SetResolutionX(float resolution);
	void SetResolutionY(float resolution);
	void GenerateTerrain();
	void SetHeight(float height);
	
private:
	float m_xSize;
	float m_ySize;
	float m_resolutionX;
	float m_resolutionY;
	float m_height;

	std::vector<Vertex> m_vertices;
	std::vector<int> m_indexes;

	bool m_meshUpdateRequired;

	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<MeshRenderer> m_meshRenderer;
	std::shared_ptr<HeightMap> m_heightMap;
};

