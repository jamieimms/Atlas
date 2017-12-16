#pragma once
#include <string>
#include "glm.hpp"
#include "Entities.h"
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
		Shader* shader;

		float uniformScale;
		int quality;

		unsigned int texCount;
		unsigned int textureID[6];

	};

	class EntityFactory
	{
	public:

		static EntityHolder* CreateEntity(EntityCreateInfo& info, Physics* phys, EntityHolder* holder = nullptr);
	};
}