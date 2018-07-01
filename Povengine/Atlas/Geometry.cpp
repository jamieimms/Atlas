#include "Geometry.h"

using namespace Atlas;

Mesh* Geometry::GetMesh(std::string& id)
{
	for (auto it : _loadedMeshes) {
		if (it->GetID() == id) {
			return it;
		}
	}

	return nullptr;
}

void Geometry::AddMesh(Mesh* mesh)
{
	for (auto it : _loadedMeshes) {
		if (it == mesh) {
			return;
		}
	}

	_loadedMeshes.push_back(mesh);
}

/// <summary>
/// Receives entity creation info and returns an entity based on that info
/// </summary>
/// <param name="character">character to retrieve the glyph index for</param>
EntityInstance* Geometry::CreateEntity(EntityCreateInfo& info, Physics* phys)
{	
	BaseEntity* newEntity = nullptr;
	switch (info.type)
	{
	case EntityTypeEnum::ET_Cone:
		newEntity = new Cone(info.quality, info.uniformScale, info.pos, info.shader);
		break;
	case EntityTypeEnum::ET_Cube:
	{
		auto c = new Cube(info.uniformScale, info.pos, info.shader);
		c->SetPhysicsProperties(phys, true, 1.0f, info.uniformScale, info.uniformScale, info.uniformScale);
		newEntity = c;
		break;
	}
	case EntityTypeEnum::ET_Origin:
		newEntity = new Origin(info.uniformScale, info.shader);
		break;
	case EntityTypeEnum::ET_Plane:
	{
		auto p = new Plane(info.uniformScale, info.pos.x, info.pos.y, info.pos.z, info.shader, info.texRepeat);
		p->SetPhysicsProperties(phys, true, 0.0f, info.uniformScale, 0.1f, info.uniformScale);
		newEntity = p;
		break;
	}
	case EntityTypeEnum::ET_Sphere:
		newEntity = new Sphere(10, 10, info.uniformScale, info.pos.x, info.pos.y, info.pos.z, info.shader);
		break;
	case EntityTypeEnum::ET_Triangle:
		newEntity = new Triangle(info.uniformScale, info.pos.x, info.pos.y, info.pos.z, info.shader);
		break;
	case EntityTypeEnum::ET_Skybox:
		newEntity = new Skybox(info.uniformScale, info.pos, info.shader, info.textureID);
		break;
	}

	dynamic_cast<BaseEntity*>(newEntity)->SetTexture(info.textureID[0]);

	_loadedEntities.push_back(newEntity);

	EntityInstance* inst;
	if (info.lifetimeMs > 0) {
		inst = new FiniteEntity(info.lifetimeMs / 1000);
	}
	else {
		inst = new EntityInstance();
	}
	inst->Initialise(info.id, newEntity);
	inst->SetPosition(info.pos);
	inst->SetUniformScale(info.uniformScale);

	return inst;
}