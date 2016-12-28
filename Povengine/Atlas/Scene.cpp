#include "Scene.h"
#include "glew.h"
#include "Primitive.h"

using namespace Atlas;

///
void Scene::LoadScene()
{
	Primitive* t = new Primitive();
	_entities.push_back(t);
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