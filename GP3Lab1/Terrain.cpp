#include "Terrain.h"
#include "Resources.h"
#include "Log.h"
#include "Application.h"
#include "RigidBody.h"
#include "BoxShape.h"

Terrain::Terrain(std::shared_ptr<HeightMap> heightMap, float xSize, float ySize) :
	m_heightMap(heightMap), m_xSize(xSize), m_ySize(ySize), m_resolutionX(1), m_resolutionY(1), m_height(1), m_meshUpdateRequired(true)
{
	if(heightMap == nullptr)
		LOG_DEBUG("terrain height map is empty");
}

void Terrain::UpdateMesh()
{
	m_mesh = std::make_shared<Mesh>(m_vertices, m_indexes);
	m_meshUpdateRequired = false;
}

void Terrain::UseHeights()
{

}

void Terrain::OnRender()
{
	m_meshRenderer->OnRender();
}

void Terrain::OnUpdate(float deltaTime)
{
	if (m_meshUpdateRequired)
		UpdateMesh();
}

void Terrain::OnAttach()
{
	GenerateTerrain();
	UpdateMesh();

	m_meshRenderer = std::make_shared<MeshRenderer>(
		m_mesh,
		Resources::GetInstance()->GetShader("light"),
		Resources::GetInstance()->GetTexture("Box_Texture.jpg"));

	this->m_entity->AddComponent(m_meshRenderer);
}

std::shared_ptr<Mesh> Terrain::GetMesh()
{
	return m_mesh;
}

void Terrain::SetResolutionX(float resolution)
{
	m_resolutionX = resolution;
	m_meshUpdateRequired = true;
}

void Terrain::SetResolutionY(float resolution)
{
	m_resolutionY = resolution;
	m_meshUpdateRequired = true;
}

void Terrain::GenerateTerrain()
{
	float sizeX = m_xSize / (m_resolutionX);
	float sizeY = m_ySize / (m_resolutionY);

	//Reserve space for vertices and indexes
	float area = m_xSize * m_ySize;
	m_vertices.reserve(area * 4);
	m_indexes.reserve(area * 6);

	int quadCounter = 0;

	std::vector<float> tmp;

	for (int y = 0; y < m_ySize; y++)
	{
		for (int x = 0; x < m_xSize; x++)
		{
			float centerX = 2 * sizeX * x;
			float centerY = 2 * sizeY * y;

			Vertex topLeft(Vertex(glm::vec3(centerX - sizeX, 1 - (m_heightMap->GetHeight(x, y + 1)) * m_height, centerY + sizeY),
				glm::vec4(1),
				glm::vec2(0.0f, 1.0f)));

			Vertex topRight(Vertex(glm::vec3(centerX + sizeX, 1 - (m_heightMap->GetHeight(x + 1, y + 1)) * m_height, centerY + sizeY),
				glm::vec4(1),
				glm::vec2(1.0f, 1.0f)));

			Vertex botLetft(Vertex(glm::vec3(centerX - sizeX, 1 - (m_heightMap->GetHeight(x, y)) * m_height, centerY - sizeY),
				glm::vec4(1),
				glm::vec2(0.0f, 0.0f)));

			Vertex botRight(Vertex(glm::vec3(centerX + sizeX, 1 - (m_heightMap->GetHeight(x + 1, y)) * m_height, centerY - sizeY),
				glm::vec4(1),
				glm::vec2(1.0f, 0.0f)));

			//Culculate quad normal
			glm::vec3 dir1 = glm::normalize(topLeft.pos - botLetft.pos);
			glm::vec3 dir2 = glm::normalize(botRight.pos - botLetft.pos);

			glm::vec3 normal = glm::cross(dir1, dir2);
			botLetft.normal += normal;
			botRight.normal += normal;
			topRight.normal += normal;
			topLeft.normal += normal;

			//Add vertices
			m_vertices.emplace_back(topLeft);
			m_vertices.emplace_back(topRight);
			m_vertices.emplace_back(botRight);
			m_vertices.emplace_back(botLetft);

			// Store indexes
			m_indexes.push_back(4 * quadCounter);
			m_indexes.push_back((4 * quadCounter) + 1);
			m_indexes.push_back((4 * quadCounter) + 3);

			m_indexes.push_back((4 * quadCounter) + 1);
			m_indexes.push_back((4 * quadCounter) + 2);
			m_indexes.push_back((4 * quadCounter) + 3);

			quadCounter++;
		}
	}
}

void Terrain::SetHeight(float height)
{
	m_height = height;
	m_meshUpdateRequired = true;
}

void Terrain::SmoothTerrain()
{
	
}


/*
			Vertex topLeft(Vertex(glm::vec3(centerX - sizeX, 1 - (m_heightMap->GetHeight(z + 1, x)) * m_height, centerY + sizeY),
				glm::vec4(1),
				glm::vec2(0.0f, 1.0f)));

			Vertex topRight(Vertex(glm::vec3(centerX + sizeX, 1 - (m_heightMap->GetHeight(z + 1, x + 1)) * m_height, centerY + sizeY),
				glm::vec4(1),
				glm::vec2(1.0f, 1.0f)));

			Vertex botLetft(Vertex(glm::vec3(centerX - sizeX, 1 - (m_heightMap->GetHeight(z, x)) * m_height, centerY - sizeY),
				glm::vec4(1),
				glm::vec2(0.0f, 0.0f)));

			Vertex botRight(Vertex(glm::vec3(centerX + sizeX, 1 - (m_heightMap->GetHeight(z, x + 1)) * m_height, centerY - sizeY),
				glm::vec4(1),
				glm::vec2(1.0f, 0.0f)));

				for (float z = 0; z < m_ySize; z++)
	{
		for (float x = 0; x < m_xSize; x++)
		{
			float centerX = 2 * sizeX * x;
			float centerY = 2 * sizeY * z;

			Vertex topLeft(Vertex(glm::vec3(centerX - sizeX, 1 - (m_heightMap->GetHeight(z + 0.1f, x)) * m_height, centerY + sizeY),
				glm::vec4(1),
				glm::vec2(0.0f, 1.0f)));

			Vertex topRight(Vertex(glm::vec3(centerX + sizeX, 1 - (m_heightMap->GetHeight(z + 0.1f, x + 1.0f)) * m_height, centerY + sizeY),
				glm::vec4(1),
				glm::vec2(1.0f, 1.0f)));

			Vertex botLetft(Vertex(glm::vec3(centerX - sizeX, 1 - (m_heightMap->GetHeight(z, x)) * m_height, centerY - sizeY),
				glm::vec4(1),
				glm::vec2(0.0f, 0.0f)));

			Vertex botRight(Vertex(glm::vec3(centerX + sizeX, 1 - (m_heightMap->GetHeight(z, x + 0.1f)) * m_height, centerY - sizeY),
				glm::vec4(1),
				glm::vec2(1.0f, 0.0f)));

			//Culculate quad normal
			glm::vec3 dir1 = glm::normalize(topLeft.pos - botLetft.pos);
			glm::vec3 dir2 = glm::normalize(botRight.pos - botLetft.pos);

			glm::vec3 normal = glm::cross(dir1, dir2);
			botLetft.normal += normal;
			botRight.normal += normal;
			topRight.normal += normal;
			topLeft.normal += normal;

			//Add vertices
			m_vertices.emplace_back(topLeft);
			m_vertices.emplace_back(topRight);
			m_vertices.emplace_back(botRight);
			m_vertices.emplace_back(botLetft);

			// Store indexes
			m_indexes.push_back(4 * quadCounter);
			m_indexes.push_back((4 * quadCounter) + 1);
			m_indexes.push_back((4 * quadCounter) + 3);

			m_indexes.push_back((4 * quadCounter) + 1);
			m_indexes.push_back((4 * quadCounter) + 2);
			m_indexes.push_back((4 * quadCounter) + 3);

			quadCounter++;
		}
	}
*/