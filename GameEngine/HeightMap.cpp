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

float HeightMap::GetHeight(const int& x, const int& y)
{
	int indxX = 0;
	int indxY = 0;

	indxY = y - std::floor(y / m_heights.size()) * m_heights.size();
	indxX = x - std::floor(x / m_heights.at(indxY).size()) * m_heights.at(indxY).size();
	
	return m_heights.at(indxY).at(indxX);
}

void HeightMap::LoadHeightMap()
{
	SDL_Surface* img = SDL_LoadBMP(m_fileName.c_str());

	if (img == nullptr)
	{
		LOG_WARNING("Unable to open file " + m_fileName);
		return;
	}

	std::vector<float> tmpHeights;

	//Get image width and height
	int imgHeight = img->h;
	int imgWidth = img->w;

	// Reserve vector space
	m_heights.reserve(imgHeight);

	//Clears heights on the current row
	tmpHeights.reserve(imgWidth);

	for (int h = 0; h < imgHeight; h++)
	{
		for (int w = 0; w < imgWidth; w++)
		{
			//Define height for current pixel 
			Uint32 pixel = ((Uint32*)img->pixels)[h * img->pitch / 4 + w];
			Uint8 r, g, b;
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			tmpHeights.emplace_back((float)r / 255.0f);
		}
		m_heights.emplace_back(tmpHeights);

		//Clears heights on the current row
		tmpHeights.clear();
		tmpHeights.reserve(imgWidth);
	}
}