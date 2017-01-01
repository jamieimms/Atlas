#include "Scene.h"
#include "glew.h"
#include "Primitive.h"
#include "Origin.h"

using namespace Atlas;

///
void Scene::LoadScene(unsigned int shader1, unsigned int shader2)

{
	Origin* o = new Origin(1.0f, shader2);
	Primitive* t = new Primitive(1.0f, 0.0f, 0.0f, 0.0f, shader1);
	Primitive* u = new Primitive(0.5f, 0.0f, -1.0f, 0.0f, shader1);
	_entities.push_back(o);
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