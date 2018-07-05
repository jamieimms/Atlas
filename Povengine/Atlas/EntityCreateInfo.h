#pragma once
#include <string>
#include "glm.hpp"
#include "EntityTypes.h"
#include "EntityTypeEnum.h"
#include "Shader.h"

namespace Atlas
{
	class EntityCreateInfo
	{
	public:
		EntityCreateInfo();

		EntityTypeEnum type;
		glm::vec3 pos;
		glm::vec3 colour;
		Shader* shader;
		bool visible;

		float uniformScale;
		int quality;
		float lifetimeMs;

		unsigned int texCount;
		unsigned int textureID[6];
		unsigned int texRepeat;
		std::string id;
		int numID;

		// Physics properties
		bool enablePhysics;
		float mass;
	};
}