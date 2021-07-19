#pragma once
#include "pch.h"

class VectorHelper
{
public:
	static void Vec3TofloatArray(glm::vec3 vector, float* arr)
	{
		arr[0] = vector.x;
		arr[1] = vector.y;
		arr[2] = vector.z;
	}

	static std::vector<float> Vec3TofloatVector(glm::vec3 vector)
	{
		std::vector<float> output;
		output.reserve(3);

		output.emplace_back(vector.x);
		output.emplace_back(vector.y);
		output.emplace_back(vector.z);

		return output;
	}

private:
	VectorHelper();
	static float m_outputArray[3];
};