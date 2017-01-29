#include "PhysicsEntity.h"

using namespace Atlas;

PhysicsEntity::PhysicsEntity(float x, float y, float z, unsigned int shaderProgramID)
	:BaseEntity(x, y, z, shaderProgramID), _physEnable(false)
{

}

void PhysicsEntity::Initialise()
{
	BaseEntity::Initialise();

	// Initialise physics stuff
}


void PhysicsEntity::SetPhysicsProperties(PhysicsManager* phys, bool physicsEnabled, float mass, float w, float h, float d)
{
	_mass = mass;
	_physEnable = physicsEnabled;

	_physicsBody =  phys->addBoxRigidBody(GetTransform(), GetPosition(), _mass, w, h, d);
}

void PhysicsEntity::UpdateFromPhysics(PhysicsManager* phys)
{
	glm::mat4 newTransform;
	phys->getTransformForRigid(newTransform, _physicsBody);

	SetTransform(newTransform);
}
