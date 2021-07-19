#pragma once
#include "pch.h"

class QuaternionHelper
{
public:

	// *Converts an angle in degrees into a quaternion
	static glm::quat AngleToQuaternion(float angle, glm::vec3 rotAxis)
	{
		float a = glm::cos(angle / 2);
		float b = rotAxis.x * glm::sin(angle / 2);
		float c = rotAxis.y * glm::sin(angle / 2);
		float d = rotAxis.z * glm::sin(angle / 2);

		return glm::quat(a, b, c, d);
	}

private:
	QuaternionHelper() = delete;
};