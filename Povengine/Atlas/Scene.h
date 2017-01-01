#pragma once
#include <vector>

#include "../AtlasUtil/IRenderable.h"

namespace Atlas
{
	class Scene
	{
	public:
		void LoadScene(unsigned int shader1, unsigned int shader2);
		void UnloadScene();

		void DrawScene();

		IRenderable* GetEntity(int index) { return _entities[index]; }
	private:
		std::vector<IRenderable*> _entities;
	};
}