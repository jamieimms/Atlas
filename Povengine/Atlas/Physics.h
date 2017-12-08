#pragma once
#include "BaseManager.h"

#include "glm.hpp"
#include "btBulletDynamicsCommon.h"


namespace Atlas
{
	class Physics : public BaseManager
	{
	public:
		Physics(AtlasUtil::AtlasLog* log);
		~Physics();

		// abstract Subsystem methods
		//virtual void reset();
		virtual void doFrame(double delta);

		bool initialisePhysicsEngine();

		void toggleDebugMode(bool debug) { _debugMode = debug; }
		bool getDebugMode() { return _debugMode; }

		//void drawDebug();

		// Something for adding an entity to the world
		btRigidBody* addSphereRigidBody(glm::mat4& startRot, glm::vec3& startPos, float mass, float size);
		btRigidBody* addBoxRigidBody(glm::mat4& startRot, glm::vec3& startPos, float mass, float w, float h, float d);
		btRigidBody* addConvexRigidBody(glm::mat4& startRot, glm::vec3& startPos, float mass, btCollisionShape *colShape);

		//void readdBody(btRigidBody* body);

		//// something for removing an entity
		void removeBody(btRigidBody* body);
		//void tempRemoveBody(btRigidBody* body);

		// enable/disable simulation of bodies
		void ToggleEnableSimulation(btRigidBody* body, bool enable);

		// Functions for retrieving info about bodies
		bool getTransformForRigid(glm::mat4& m, btRigidBody* body);
	private:

		//void setDebugDrawer(DirectXPhysicsDrawer* drawer) { _dynamicsWorld->setDebugDrawer(_debugDrawer = drawer); }

		btRigidBody* addRigidBody(glm::mat4& startRot, glm::vec3& startPos, float mass, btCollisionShape* colShape);

		btDefaultCollisionConfiguration* _collisionConfiguration;

		btCollisionDispatcher* _dispatcher;

		btBroadphaseInterface* _overlappingPairCache;

		btSequentialImpulseConstraintSolver* _solver;

		btDiscreteDynamicsWorld* _dynamicsWorld;

		//keep track of the shapes, we release memory at exit.
		//make sure to re-use collision shapes among rigid bodies whenever possible!
		btAlignedObjectArray<btCollisionShape*> _collisionShapes;

		//DirectXPhysicsDrawer* _debugDrawer;

		bool _debugMode;

	};
}