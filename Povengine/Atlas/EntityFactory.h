#pragma once
#include <string>
#include "glm.hpp"
#include "Entities.h"
#include "EntityTypeEnum.h"

namespace Atlas
{
	struct EntityCreateInfo
	{
		EntityTypeEnum type;
		glm::vec3 pos;
		unsigned int shader;

		float size;
		int quality;

		unsigned int textureID;
	};

	class EntityFactory
	{
	public:

		static IRenderable* CreateEntity(EntityCreateInfo& info, PhysicsManager* phys);
	};
}