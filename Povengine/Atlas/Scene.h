#pragma once
#include <vector>

#include "../AtlasUtil/IRenderable.h"
#include "Camera.h"

namespace Atlas
{
	class Scene
	{
	public:
		void LoadScene(unsigned int shader1, unsigned int shader2);
		void UnloadScene();

		void DrawScene(glm::mat4 proj);

		IRenderable* GetEntity(int index) { return _entities[index]; }
		Camera& GetCamera() { return _cam; }

	private:
		std::vector<IRenderable*> _entities;

		Camera _cam;
	};
}