#pragma once
#include "BaseEntity.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicsManager.h"


namespace Atlas
{
	class PhysicsEntity : public BaseEntity
	{

	public:
		PhysicsEntity(float x, float y, float z, unsigned int shaderProgramID);
		PhysicsEntity(glm::vec3 pos, unsigned int shaderProgramID);

		bool TogglePhysics(bool enabled) { _physEnable = enabled; }

		void SetPhysicsProperties(PhysicsManager* phys, bool physicsEnabled, float mass, float w, float h, float d);
		void SetPhysicsBody(btRigidBody* body) { _physicsBody = body; }
		
		void UpdateFromPhysics(PhysicsManager* phys);


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