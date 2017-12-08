#pragma once
#include <vector>

#include "../AtlasUtil/IRenderable.h"
#include "../AtlasUtil/AtlasStopwatch.h"
#include "Audio.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Physics.h"
#include "ShaderManager.h"
#include "glm.hpp"
#include "EntityTypeEnum.h"
#include "EntityFactory.h"
#include <sstream>

namespace Atlas
{
	class Scene
	{
	public:
		Scene(TextureManager* texManager, Physics* physManager, ShaderManager* shaderManager, Audio* audioManager);
		void LoadFromFile(std::string& path);

		void UnloadScene();

		void Start();
		void Stop();

		void UpdateScene();
		void DrawScene(glm::mat4 proj);

		//IRenderable* GetEntity(int index) { return _entities[index]; }
		Camera& GetCamera() { return _cam; }

		void RemoveEntity(BaseEntity* entity);

	private:
		void ParseEntity(EntityTypeEnum type, std::stringstream& ss, EntityCreateInfo& eci);

		std::vector<EntityHolder*> _entities;	// Entities contained within holders (things that need to be updated regularly but are not rendered, game objects etc.)

		Camera _cam;

		TextureManager* _texManager;
		Physics* _physicsManager;
		ShaderManager* _shaderManager;
		Audio* _audio;

		glm::vec3 _ambientLight;

		AtlasUtil::AtlasStopwatch _sceneClock;

		unsigned long _bgMusicId;

		void Test();

	};
}