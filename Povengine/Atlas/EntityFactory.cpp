#include "EntityFactory.h"

using namespace Atlas;

EntityCreateInfo::EntityCreateInfo()
{
	texCount = 0;
	for (int i = 0; i < 6; i++) {
		textureID[i] = 0;
	}
}

/// <summary>
/// Receives entity creation info and returns an entity based on that info
/// </summary>
/// <param name="character">character to retrieve the glyph index for</param>
EntityHolder* EntityFactory::CreateEntity(EntityCreateInfo& info, Physics* phys, EntityHolder* holder)
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
		auto p = new Plane(info.uniformScale, info.pos.x, info.pos.y, info.pos.z, info.shader);
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

	if (holder != nullptr) {
		return holder->Initialise(newEntity) ? holder : nullptr;
	}
	else {
		EntityHolder* newHolder = new EntityHolder();
		newHolder->Initialise(newEntity);
		return newHolder;
	}
}