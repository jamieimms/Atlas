#include "Scene.h"
#include "glew.h"
#include "Triangle.h"
#include "Origin.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cone.h"
#include "Plane.h"
#include "FileManager.h"

using namespace Atlas;


Scene::Scene(TextureManager* texManager, PhysicsManager* physManager)
	: _texManager(texManager), _physicsManager(physManager)
{

}


///
void Scene::LoadScene(unsigned int shader1, unsigned int shader2)
{
	std::string texDir = FileManager::GetTextureDirectory();
	auto dirt = _texManager->LoadTexture(texDir + "Dirt.png");
	auto grassBoundary = _texManager->LoadTexture(texDir + "DirtGrassBorder01.png");
	auto patchyGrass = _texManager->LoadTexture(texDir + "PatchyDirt.png");

	//Triangle* t = new Triangle(1.0f, 0.0f, 0.0f, 0.0f, shader1);
	//Triangle* u = new Triangle(0.5f, 0.0f, -1.0f, 0.0f, shader1);

	AddEntity(new Origin(1.0f, shader1));

	//AddEntity(new Cube(1.0f, 0, 100, 0, shader2));
	
	Cube* c;
	float x = 0;
	for (float y = 10.0f; y < 30.0f; y += 2.0f) {
		c = new Cube(0.5f, x, y, 0.0f, shader1);
		AddEntity(c);
		c->SetPhysicsProperties(_physicsManager, true, 1.0f, 0.5f, 0.5f, 0.5f);
		x += 0.2f;
	}

	auto p = new Plane(5.0f, 0, -0.01f, 0, shader2);
	AddEntity(p);
	p->SetTexture(dirt);
	p->SetPhysicsProperties(_physicsManager, true, 0.0f, 5.0f, 0.1f, 5.0f);

	// Boundaries
	//p = new Plane(5.0f, 0.0f, -0.01f, -10.0f, shader2);
	//AddEntity(p);
	//p->SetTexture(grassBoundary);

	//p = new Plane(5.0f, 0.0f, -0.01f, 10.0f, shader2);
	//AddEntity(p);
	//p->SetTexture(grassBoundary);
	//p->SetRotation(0, glm::radians(180.0f), 0);
	//p = new Plane(5.0f, 10.0f, -0.01f, 0.0f, shader2);
	//AddEntity(p);
	//p->SetTexture(grassBoundary);
	//p->SetRotation(0, glm::radians(-90.0f), 0);
	//p = new Plane(5.0f, -10.0f, -0.01f, 0.0f, shader2);
	//AddEntity(p);
	//p->SetTexture(grassBoundary);
	//p->SetRotation(0, glm::radians(90.0f), 0);

	////grass ring
	//p = new Plane(5.0f, 0.0f, -0.01f, -20.0f, shader2);
	//AddEntity(p);
	//p->SetTexture(patchyGrass);
	//p = new Plane(5.0f, 0.0f, -0.01f, 20.0f, shader2);
	//AddEntity(p);
	//p->SetTexture(patchyGrass);	
	//p = new Plane(5.0f, 20.0f, -0.01f, 00.0f, shader2);
	//AddEntity(p);
	//p->SetTexture(patchyGrass);
	//p = new Plane(5.0f, -20.0f, -0.01f, 00.0f, shader2);
	//AddEntity(p);
	//p->SetTexture(patchyGrass);

	_cam.SetPosition(0, 3.0f, 5.0f);
	_cam.SetLookAt(0, 0, 0);
}

IRenderable* Scene::AddEntity(IRenderable* entity)
{
	_entities.push_back(entity);

	return entity;
}

///
void Scene::UnloadScene()
{
	for (auto i : _entities)
	{
		delete i;
	}
}

///
void Scene::DrawScene(glm::mat4 proj)
{
	auto view = _cam.GetViewMatrix();

	for (auto i : _entities)
	{
		PhysicsEntity* tmp = dynamic_cast<PhysicsEntity*>(i);
		if (tmp != nullptr) {
			tmp->UpdateFromPhysics(_physicsManager);
		}

		i->Render(view, proj);
	}
}