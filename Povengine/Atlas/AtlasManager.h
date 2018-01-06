#pragma once
#include "BaseManager.h"
#include <chrono>
#include "Window.h"
#include "Scene.h"
#include "../AtlasUtil/AtlasLog.h"
#include "Subsystems.h"
#include "../AtlasUtil/AtlasStopwatch.h"
#include "AtlasGame.h"

namespace Atlas
{
	class AtlasManager : protected BaseManager
	{
	public:
		AtlasManager(AtlasGame* game);
		~AtlasManager();

		Window* getWindow();

		bool Initialise();

		void windowSizeChanged(int width, int height);

		int start();

		Input* GetInput() { return _subsystems._input; }

		void BeginSceneChange(Scene* nextScene);


	private:

		void inputProcessing();
		void frameProcessing();
		void FinishSceneChange();

		void toggleMouseLook(bool enable);

		void LoadShaders();

		// Members
		Window* _applicationWindow;	// The desktop window we're rendering inside

		Subsystems _subsystems;

		std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrame;
		double _frameDelta;
		double _fps;

		Scene* _oldScene;
		Scene* _currentScene;
		Scene* _nextScene;

		AtlasGame* _game;

		std::string _name;
		std::string _mainDir;

		bool _enableMouseLook;

		glm::mat4 _2DProjection;
	};
}
