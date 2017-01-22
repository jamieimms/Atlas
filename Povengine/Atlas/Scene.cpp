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

	//Triangle* t = new Triangle(1.0f, 0.0f, 0.0f, 0.0f, shader1);
	//Triangle* u = new Triangle(0.5f, 0.0f, -1.0f, 0.0f, shader1);

	AddEntity(new Origin(1.0f, shader1));

	//_entities.push_back(new Cube(1.0f, 0, 0, 0, shader2));
	//_entities.push_back(new Cube(1.0f, 0, -100, 0, shader2));
	//AddEntity(new Cube(1.0f, 0, 100, 0, shader2));
	//AddEntity(new Cube(1.0f, -1.0f, -1.0f, -1.0f, shader1));

	//AddEntity(new Cone(10, 1.0f, 0, 1.0f, 0, shader1));
	//AddEntity(new Cone(5, 1.0f, 0, -1.0f, 0, shader1));

	AddEntity(new Plane(1.0f, 0, -0.01f, 0, shader2));
	AddEntity(new Plane(1.0f, 1.0f, -0.01f, 0, shader2));
	AddEntity(new Plane(1.0f, 2.0f, -0.01f, 0, shader2));
	AddEntity(new Plane(1.0f, 3.0f, -0.01f, 0, shader2));
	AddEntity(new Plane(1.0f, 4.0f, -0.01f, 0, shader2));
	AddEntity(new Plane(1.0f, 5.0f, -0.01f, 0, shader2));
	AddEntity(new Plane(1.0f, -1.0f, -0.01f, 0, shader2));
	AddEntity(new Plane(1.0f, -2.0f, -0.01f, 0, shader2));
	AddEntity(new Plane(1.0f, -3.0f, -0.01f, 0, shader2));

	_cam.SetPosition(0, 3.0f, 5.0f);
	_cam.SetLookAt(0, 0, 0);
}

void Scene::AddEntity(IRenderable* entity)
{
	_entities.push_back(entity);
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