#include "HeightMap.h"
#include "Log.h"


HeightMap::HeightMap(const std::string& fileName) :
	m_fileName(fileName)
{
	LoadHeightMap();
}

std::vector<std::vector<float>>* HeightMap::GetHeights()
{
	return &m_heights;
}

float HeightMap::GetHeight(const float& x, const float& y)
{	
	if (x == std::floor(x) && y == std::floor(y))
		return GetHeight((int)x, (int)y);

	int intX = int(x);
	int intY = int(y);

	std::vector<float> effect;
	float height = 0;

	float testDist = (1 + ((glm::vec2(x, y) - glm::vec2(intX, intY)).length()));
	float testData2 = 1 / (1 + ((glm::vec2(x, y) - glm::vec2(intX, intY)).length()));

	//Get Neighbors
	//if (intX > 0 && intY < m_heights.size())
	float dist = 1 + ((glm::vec2(x, y) - glm::vec2(intX, intY)).length());
		effect.push_back(1 / dist);

	//if(intX + 1 > 0 && intY < m_heights.size())
		dist = (1 + ((glm::vec2(x, y) - glm::vec2(intX + 1, intY)).length()));
		effect.push_back(1 / dist);


	//if (intX > 0 && intY + 1 < m_heights.size())
		dist = (1 + (glm::vec2(x, y) - glm::vec2(intX, intY + 1)).length());
		effect.push_back(1 / dist);

	//if (intX + 1> 0 && intY + 1 < m_heights.size())
		dist = 1 + (glm::vec2(x, y) - glm::vec2(intX + 1, intY + 1)).length();
		effect.push_back(1 / dist);


	for (int i = 0; i < effect.size(); i++)
	{
		height += effect[i];
	}

	height /= effect.size();
	return height;
}

float HeightMap::GetHeight(const int& x, const int& y)
{
	int indxX = 0;
	int indxY = 0;
	

	//std::cout << x << std::endl;
	//std::cout << y << std::endl;
 
	indxY = y - std::floor(y / m_heights.size()) * m_heights.size();
	indxX = x - std::floor(x / m_heights.at(indxY).size()) * m_heights.at(indxY).size();
	
	/*
	if (m_heights.size() > y)
		indxY = y;

	if (m_heights.at(indxY).size() > x)
		indxX = x;
	*/
	return m_heights.at(indxY).at(indxX);
}

void HeightMap::LoadHeightMap()
{
	SDL_Surface* img = SDL_LoadBMP(m_fileName.c_str());

	if (img == nullptr)
	{
		LOG_DEBUG("height map could not be loaded");
		return;
	}

	std::vector<float> tmpHeights;

	int imgHeight = img->h;
	int imgWidth = img->w;
	m_heights.reserve(imgHeight);
	tmpHeights.reserve(imgWidth);

	//Requires referensing? 
	for (int h = 0; h < imgHeight; h++)
	{
		tmpHeights.clear();
		for (int w = 0; w < imgWidth; w++)
		{
			Uint32 pixel = ((Uint32*)img->pixels)[h * img->pitch / 4 + w];
			Uint8 r, g, b;
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			tmpHeights.emplace_back((float)r / 255.0f);
		}
		m_heights.emplace_back(tmpHeights);
	}
}