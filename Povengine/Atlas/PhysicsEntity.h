#pragma once
#include "BaseEntity.h"
#include "btBulletDynamicsCommon.h"
#include "Physics.h"


namespace Atlas
{
	class PhysicsEntity : public BaseEntity
	{

	public:
		PhysicsEntity(float x, float y, float z, Shader* shader);
		PhysicsEntity(glm::vec3 pos, Shader* shader);

		virtual ~PhysicsEntity();

		bool TogglePhysics(bool enabled) { _physEnable = enabled; }

		void SetPhysicsProperties(Physics* phys, bool physicsEnabled, float mass, float w, float h, float d);
		void SetPhysicsBody(btRigidBody* body) { _physicsBody = body; }

		void RemoveFromSimulation(Physics* phys);
		void UpdateFromPhysics(Physics* phys);

		float GetMass() { return _mass; }
		bool IsPhysicsEnabled() { return _physEnable; }

	protected:

		btRigidBody* _physicsBody;
		//btConvexHullShape* _physicsMesh;
		btBoxShape* _physBox;

	private:

		float _mass;

		bool _physEnable;
	};
}