#pragma once
#include <list>

#include "../AtlasUtil/IRenderable.h"

namespace Atlas
{
	class Scene
	{
	public:
		void LoadScene();
		void UnloadScene();

		void DrawScene();
	private:
		std::list<IRenderable*> _entities;
	};
}