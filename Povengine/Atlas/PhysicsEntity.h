#pragma once
#include "BaseEntity.h"
#include "btBulletDynamicsCommon.h"


namespace Atlas
{
	class PhysicsEntity : protected BaseEntity
	{

	public:
		virtual void Initialise();

		bool TogglePhysics(bool enabled) { _physEnable = enabled; }

		void SetPhysicsProperties();

	private:

		btRigidBody* _physicsBody;
		btConvexHullShape* _physicsMesh;

		bool _physEnable;
	};
}