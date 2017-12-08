#include "PhysicsEntity.h"

using namespace Atlas;

PhysicsEntity::PhysicsEntity(float x, float y, float z, Shader* shader)
	:BaseEntity(x, y, z, shader), _physEnable(false), _physBox(nullptr)
{

}

PhysicsEntity::PhysicsEntity(glm::vec3 pos, Shader* shader)
	: BaseEntity(pos, shader), _physEnable(false), _physBox(nullptr)
{

}

PhysicsEntity::~PhysicsEntity()
{
	if (!_physicsBody) {
		return;
	}

	if (_physicsBody->getMotionState()) {
		delete _physicsBody->getMotionState();
	}

	delete _physicsBody;

	if (_physBox) {
		delete _physBox;
	}

}

void PhysicsEntity::RemoveFromSimulation(Physics* phys)
{
	if (!_physicsBody) {
		return;
	}

	phys->removeBody(_physicsBody);
}

void PhysicsEntity::SetPhysicsProperties(Physics* phys, bool physicsEnabled, float mass, float w, float h, float d)
{
	_mass = mass;
	_physEnable = physicsEnabled;

	_physicsBody =  phys->addBoxRigidBody(GetTransform(), GetPosition(), _mass, w, h, d);
	//phys->ToggleEnableSimulation(_physicsBody, false);
}

void PhysicsEntity::UpdateFromPhysics(Physics* phys)
{
	glm::mat4 newTransform;
	phys->getTransformForRigid(newTransform, _physicsBody);

	SetTransform(newTransform);
}
