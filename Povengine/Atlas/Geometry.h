#pragma once
#include <string>

#include "EntityTypes.h"

#include "EntityCreateInfo.h"

namespace Atlas
{
	class Geometry
	{
	public:

		void AddMesh(Mesh* mesh);
		Mesh* GetMesh(std::string& id);

		EntityInstance* CreateEntity(EntityCreateInfo& info, Physics* phys);


	private:
		std::vector<Mesh*> _loadedMeshes;
		std::vector<BaseEntity*> _loadedEntities;

	};
}