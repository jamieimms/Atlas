#include "Scene.h"
#include "glew.h"
#include "Triangle.h"
#include "Origin.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cone.h"
#include "Plane.h"

using namespace Atlas;

///
void Scene::LoadScene(unsigned int shader1, unsigned int shader2)
{
	std::string texDir = "S:\\Development\\Povengine\\Data\\Textures\\";
	auto tex1 = _texManager.LoadTexture(texDir + "Dirt.png");
	auto tex2 = _texManager.LoadTexture(texDir + "PatchyDirt.png");
	auto tex3 = _texManager.LoadTexture(texDir + "DirtGrassBorder01.png");

	//Triangle* t = new Triangle(1.0f, 0.0f, 0.0f, 0.0f, shader1);
	//Triangle* u = new Triangle(0.5f, 0.0f, -1.0f, 0.0f, shader1);

	AddEntity(new Origin(1.0f, shader1));

	//_entities.push_back(new Cube(1.0f, 0, 0, 0, shader2));
	//_entities.push_back(new Cube(1.0f, 0, -100, 0, shader2));
	//AddEntity(new Cube(1.0f, 0, 100, 0, shader2));
	//AddEntity(new Cube(1.0f, -1.0f, -1.0f, -1.0f, shader1));

	//AddEntity(new Cone(10, 1.0f, 0, 1.0f, 0, shader1));
	//AddEntity(new Cone(5, 1.0f, 0, -1.0f, 0, shader1));
	auto p = new Plane(10.0f, 0, -0.01f, 0, shader2);
	AddEntity(p);
	p->SetTexture(tex1);

	// Grass edge
	for (float z = -9.5f; z < 10.5f; z += 2.0f) {
		p = new Plane(1.0f, 11.0f, -0.01f, z, shader2);
		p->SetTexture(tex3);
		p->SetRotation(0, glm::radians(270.0f), 0);
		AddEntity(p);
	}

	// Grass
	for (float z = -10.5f; z < 10.0f; z += 2.0f) {
		p = new Plane(1.0f, 13.0f, -0.01f, z, shader2);
		p->SetTexture(tex2);
		AddEntity(p);
	}
	
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
		i->Render(view, proj);
	}
}