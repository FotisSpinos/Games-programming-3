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

void Terrain::OnRender()
{
}

void Terrain::OnUpdate(float deltaTime)
{
	if (m_meshUpdateRequired)
		UpdateMesh();
}

void Terrain::OnAttach()
{
	// Generate and create mesh
	GenerateTerrain();
	UpdateMesh();

	// Attach the mesh renderer to the entity
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
	//Measures the x and y dimentions of each quad
	float sizeX = m_xSize / (m_resolutionX);
	float sizeY = m_ySize / (m_resolutionY);

	//Records the amount of quads generated
	int quadCounter = 0;

	//Reserve space for vertices and indexes
	float area = m_xSize * m_ySize;
	m_vertices.reserve(area * 4);
	m_indexes.reserve(area * 6);

	for (int y = 0; y < m_ySize; y++)
	{
		for (int x = 0; x < m_xSize; x++)
		{
			float originX = sizeX * x;
			float originY = sizeY * y;

			//Create indeces
			Vertex topLeft(Vertex(glm::vec3(originX, 1 - (m_heightMap->GetHeight(x, y + 1)) * m_height, originY + sizeY),
				glm::vec4(1),
				glm::vec2(0.0f, 1.0f)));

			Vertex topRight(Vertex(glm::vec3(originX + sizeX, 1 - (m_heightMap->GetHeight(x + 1, y + 1)) * m_height, originY + sizeY),
				glm::vec4(1),
				glm::vec2(1.0f, 1.0f)));

			Vertex botLetft(Vertex(glm::vec3(originX, 1 - (m_heightMap->GetHeight(x, y)) * m_height, originY),
				glm::vec4(1),
				glm::vec2(0.0f, 0.0f)));

			Vertex botRight(Vertex(glm::vec3(originX + sizeX, 1 - (m_heightMap->GetHeight(x + 1, y)) * m_height, originY),
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