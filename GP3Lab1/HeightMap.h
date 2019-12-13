#pragma once
#include "pch.h"

class HeightMap
{
public:
	HeightMap(const std::string& fileName);

	//Setters / Getters
	std::vector<std::vector<float>>* GetHeights();
	float GetHeight(const int& x, const int& y);

private:
	std::vector<std::vector<float>> m_heights;
	std::string m_fileName;
	void LoadHeightMap();
};