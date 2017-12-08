#pragma once
#include <string>
#include "glm.hpp"
#include "Entities.h"
#include "EntityTypeEnum.h"
#include "Shader.h"

namespace Atlas
{
	struct EntityCreateInfo
	{
		EntityTypeEnum type;
		glm::vec3 pos;
		Shader* shader;

		float size;
		int quality;

		unsigned int textureID;
	};

	class EntityFactory
	{
	public:

		static EntityHolder* CreateEntity(EntityCreateInfo& info, Physics* phys, EntityHolder* holder = nullptr);
	};
}