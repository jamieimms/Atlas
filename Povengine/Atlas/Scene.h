#pragma once
#include <vector>

#include "../AtlasUtil/IRenderable.h"
#include "Camera.h"
#include "TextureManager.h"
#include "PhysicsManager.h"
#include "ShaderManager.h"
#include "glm.hpp"

namespace Atlas
{
	class Scene
	{
	public:
		Scene(TextureManager* texManager, PhysicsManager* physManager, ShaderManager* shaderManager);
		void LoadFromFile(std::string& path);

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
		ShaderManager* _shaderManager;

		glm::vec3 _ambientLight;


	};
}