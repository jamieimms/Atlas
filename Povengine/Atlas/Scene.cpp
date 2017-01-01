#include "Scene.h"
#include "glew.h"
#include "Primitive.h"

using namespace Atlas;

///
void Scene::LoadScene()
{
	Primitive* t = new Primitive(0.5f, -0.5f, 0, 0);
	Primitive* u = new Primitive(0.5f, 0.5f, 0, 0);
	_entities.push_back(t);
	_entities.push_back(u);
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
void Scene::DrawScene()
{
	for (auto i : _entities)
	{
		i->Render();
	}
}