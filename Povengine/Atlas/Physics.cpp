#include "Physics.h"

using namespace Atlas;

Physics::Physics(AtlasUtil::AtlasLog* log)
	:BaseManager(log)
{
	//_debugDrawer = 0;
	_debugMode = false;
}

Physics::~Physics()
{
	//cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	for (int i = _dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = _dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		_dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j<_collisionShapes.size(); j++)
	{
		btCollisionShape* shape = _collisionShapes[j];
		_collisionShapes[j] = 0;
		delete shape;
	}

	// delete dynamics world
	delete _dynamicsWorld;

	// delete solver
	delete _solver;

	// delete broadphase
	delete _overlappingPairCache;

	// delete collision dispatcher
	delete _dispatcher;

	// delete configuration
	delete _collisionConfiguration;

	//delete _debugDrawer;
}

bool Physics::initialisePhysicsEngine()
{
	try {
		_log->Debug("Initialising Physics System");

		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		_collisionConfiguration = new btDefaultCollisionConfiguration();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		_dispatcher = new	btCollisionDispatcher(_collisionConfiguration);

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		_overlappingPairCache = new btDbvtBroadphase();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		_solver = new btSequentialImpulseConstraintSolver;

		_dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _overlappingPairCache, _solver, _collisionConfiguration);

		_dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));

		// Create the debug drawer
		//if (_system->getRenderer()->getType() == RENDERER_DIRECTX10) {
		//	setDebugDrawer(new DirectXPhysicsDrawer(EntityProperties(DEBUG_ENTITY, L"physDraw"), (ID3D10Device*)_system->getRenderer()->getDevice()));
		//}
		//else {
		//	setDebugDrawer(0);
		//}
	}
	catch (...) {
		_log->Error("Physics system failed to initialise.");
		// memory alloc failed
		return false;
	}

	_log->Debug("Physics initialised successfully");

	return true;
}

//	doFrame()
//	Advances the simulation by the seconds elapsed since last frame.
//
//
void Physics::doFrame(double delta)
{
		_dynamicsWorld->stepSimulation(delta, 10);
}

//	addRigidBody()
//
//	Adds a new rigid body with the specified parameters.  Returns the index the adder should use if it
//  wants to find out info about this body later.
//
btRigidBody* Physics::addRigidBody(glm::mat4& startRot, glm::vec3& startPos, float mass, btCollisionShape* colShape)
{
	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic) {
		colShape->calculateLocalInertia(mass, localInertia);
	}

	startTransform.setOrigin(btVector3(startPos.x, startPos.y, startPos.z));

	// Set the rotation matrix (basis).  Convert our matrix into the bullet matrix type first
	btMatrix3x3 basis;
	basis[0][0] = startRot[0][0]; basis[0][1] = startRot[0][1]; basis[0][2] = startRot[0][2];
	basis[1][0] = startRot[1][0]; basis[1][1] = startRot[1][1]; basis[1][2] = startRot[1][2];
	basis[2][0] = startRot[2][0]; basis[2][1] = startRot[2][1]; basis[2][2] = startRot[2][2];

	startTransform.setBasis(basis);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	_dynamicsWorld->addRigidBody(body);

	return body;
}


// addSphereRigidBody()
//
//	Adds a rigid body with a sphere shaped collision shape with the given dimensions.
//
btRigidBody* Physics::addSphereRigidBody(glm::mat4& startRot, glm::vec3& startPos, float mass, float size)
{
	btCollisionShape* colShape = new btSphereShape(btScalar(size));

	_collisionShapes.push_back(colShape);

	return addRigidBody(startRot, startPos, mass, colShape);
}

/********************************
//    Entity::addBoxRigidBody()
*********************************/
//
//<Summary>
//	Adds a rigid body with a box shaped collision shape with the given dimensions.
//</Summary>
//<Params>
//	startRot - physics entity initial rotation
//	startPos - initial position
//	mass - mass of the entity
//	w - width of the entity in physics sim
//	h - height of the entity
//	d - depth
//</Params>
btRigidBody* Physics::addBoxRigidBody(glm::mat4& startRot, glm::vec3& startPos, float mass, float w, float h, float d)
{
	btCollisionShape* colShape = new btBoxShape(btVector3(w, h, d));

	_collisionShapes.push_back(colShape);

	return addRigidBody(startRot, startPos, mass, colShape);
}

/********************************
//    Entity::addConvexRigidBody()
*********************************/
//
//<Summary>
//	Adds a rigid convex (mesh) shaped collision shape
//</Summary>
//<Params>
//	pe - physics entity (e.g. box)
//	mass - mass of the entity
//</Params>
btRigidBody* Physics::addConvexRigidBody(glm::mat4& startRot, glm::vec3& startPos, float mass, btCollisionShape *colShape)
{
	if (!_collisionShapes.findBinarySearch(colShape)) {
		_collisionShapes.push_back(colShape);
	}

	return addRigidBody(startRot, startPos, mass, colShape);
}

/********************************
//    PhysicsManager::disableBody()
*********************************/
//
//<Summary>
//	disables the rigid body with the given id so that it is included in the physics
//	simulation
//</Summary>
//<Params>
//	body - physics body to remove and destroy
//</Params>
void Physics::ToggleEnableSimulation(btRigidBody* body, bool enable)
{
	if (!body) {
		return;
	}

	body->forceActivationState(enable ? ACTIVE_TAG : DISABLE_SIMULATION);
}

/********************************
//	PhysicsManager::getTransformForRigid()
*********************************/
//
//<Summary>
//	Fills the given matrix with the transform the physics engine currently has
//	for the given id.  Will contain rotation and position info. Returns false if the bodyId is invalid
//</Summary>
//<Params>
//	m - the matrix to fill
//	body - the body to re-add.
//</Params>
bool Physics::getTransformForRigid(glm::mat4& m, btRigidBody* body)
{

	if (!body) {
		return false;
	}

	if (body->getMotionState())
	{
		btTransform trans;
		body->getMotionState()->getWorldTransform(trans);

		const btVector3 row = trans.getOrigin();

		m[3][0] = row.x();
		m[3][1] = row.y();
		m[3][2] = row.z();
		btMatrix3x3 b;

		// I don't know why this is the case, but I need the inverse of the rotation basis matrix
		// for some reason for the rotation of my objects to match the physics objects.
		b = trans.inverse().getBasis();

		m[0][0] = b[0][0]; m[0][1] = b[0][1]; m[0][2] = b[0][2];
		m[1][0] = b[1][0]; m[1][1] = b[1][1]; m[1][2] = b[1][2];
		m[2][0] = b[2][0]; m[2][1] = b[2][1]; m[2][2] = b[2][2];
	}

	return true;
}

void Physics::removeBody(btRigidBody* toRemove)
{
	if (toRemove == nullptr) {
		return;
	}

	_dynamicsWorld->removeCollisionObject(toRemove);

}
