#pragma once
#include <vector>
#include <string>
#include <sstream>

#include "IRenderable.h"
#include "../AtlasUtil/AtlasStopwatch.h"
#include "Audio.h"
#include "Camera.h"
#include "glm.hpp"
#include "EntityTypeEnum.h"
#include "Text.h"
#include "Subsystems.h"
#include "EntityInstance.h"
#include "EntityCreateInfo.h"

namespace Atlas
{
	class Scene
	{
	public:
		Scene(std::string name);

		bool Initialise(Subsystems subsystems);

		// Methods we expect to be implemented by inheriting classes
		virtual void SceneLoaded();	// Called after the base scene has loaded
		virtual void UpdateScene(double frameDelta); // Called per-frame 
		virtual void SceneUnloading();	// Called prior to scene unloading

		virtual void InputProcessing(Input* input);

		void UnloadScene();

		void Start();
		void Stop();

		void DrawScene(glm::mat4 proj, glm::mat4 proj2D);

		Camera& GetCamera() { return _cam; }

		void RemoveEntity(BaseEntity* entity);

		bool AddBackgroundMusic(std::string fileName);
		bool AddSound(std::string fileName);
		void SetCamera(glm::vec3 pos, glm::vec3 target);
		void AddEntity(EntityInstance* entity);
		void AddLight(Light* light);
		void AddMesh(std::string& meshName, EntityCreateInfo& info);
		int AddText(std::string& id, std::string& text, int x, int y , FontStyleEnum style, TextAlignmentEnum horizontalAlignment, TextAlignmentEnum verticalAlignment, bool visible);
		void AddSprite(Sprite* sprite);

		std::string GetName() { return _name; }
		bool IsLoaded() { return _isLoaded; }

	protected:
		Text * GetTextById(const std::string& id);
		Sprite* GetSpriteById(const std::string& id);
		SoundInfo* GetSoundByName(const std::string& soundName);
		EntityInstance* GetEntityById(const std::string& id);

		double GetRuntimeMs() { return _sceneClock.GetElapsedMs(); }
		double GetRuntimeSec() { return _sceneClock.GetElapsedSec(); }

		void PlaySound(unsigned int soundID);

		bool _isLoaded;

		Camera _cam;

		Subsystems _subsystems;

	private:

		bool _initialised;

		std::vector<Sprite*> _spriteEntities;
		std::vector<EntityInstance*> _entities; // Entities contained within instances (things that need to be updated regularly but are not rendered, game objects etc.)
		std::vector<Light*> _lights;
		std::vector<SoundInfo*> _loadedSounds;

		AtlasUtil::AtlasStopwatch _sceneClock;
		AtlasUtil::AtlasStopwatch _textClock;

		bool _playMusic;
		unsigned long _bgMusicId;

		glm::mat4 _identity;
		glm::vec3 _zeroVec;

		std::string _name;
		std::string _titleText;

		int _debugSceneNameTextID;
		int _debugFPSTextID;
		int _debugEntitiesTextID;
	};
}