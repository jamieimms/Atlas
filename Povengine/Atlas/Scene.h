#pragma once
#include <vector>

#include "../AtlasUtil/IRenderable.h"
#include "Camera.h"
#include "TextureManager.h"
#include "PhysicsManager.h"

namespace Atlas
{
	class Scene
	{
	public:
		Scene(TextureManager* texManager, PhysicsManager* physManager);
		void LoadScene(unsigned int shader1, unsigned int shader2);
		void UnloadScene();

		void DrawScene(glm::mat4 proj);

		IRenderable* GetEntity(int index) { return _entities[index]; }
		Camera& GetCamera() { return _cam; }

	private:
		IRenderable* AddEntity(IRenderable* entity);


		std::vector<IRenderable*> _entities;

		Camera _cam;

		TextureManager* _texManager;
		PhysicsManager* _physicsManager;
	};
}