#include "EntityFactory.h"

using namespace Atlas;

IRenderable* EntityFactory::CreateEntity(EntityCreateInfo& info, PhysicsManager* phys)
{
	IRenderable* newEntity = nullptr;
	switch (info.type)
	{
	case EntityTypeEnum::ET_Cone:
		newEntity = new Cone(info.quality, info.size, info.pos, info.shader);
		break;
	case EntityTypeEnum::ET_Cube:
	{
		auto c = new Cube(info.size, info.pos, info.shader);
		c->SetPhysicsProperties(phys, true, 1.0f, info.size, info.size, info.size);
		newEntity = c;
		break;
	}
	case EntityTypeEnum::ET_Origin:
		newEntity = new Origin(info.size, info.shader);
		break;
	case EntityTypeEnum::ET_Plane:
	{
		auto p = new Plane(info.size, info.pos.x, info.pos.y, info.pos.z, info.shader);
		p->SetPhysicsProperties(phys, true, 0.0f, info.size, 0.1f, info.size);
		newEntity = p;
		break;
	}
	case EntityTypeEnum::ET_Sphere:
		newEntity = new Sphere(10, 10, info.size, info.pos.x, info.pos.y, info.pos.z, info.shader);
		break;
	case EntityTypeEnum::ET_Triangle:
		newEntity = new Triangle(info.size, info.pos.x, info.pos.y, info.pos.z, info.shader);

		break;
	}

	dynamic_cast<BaseEntity*>(newEntity)->SetTexture(info.textureID);

	return newEntity;
}