#pragma once
#include "glm.hpp"

namespace Atlas
{
	struct Material
	{
		glm::vec3 ambientColour;
		glm::vec3 diffuseColour;
		glm::vec3 specularColour;
		float shininess;
	};
}