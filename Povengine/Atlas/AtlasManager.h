#pragma once
#include "BaseManager.h"
#include <chrono>
#include "Window.h"
#include "AtlasRenderer.h"
#include "Scene.h"
#include "../AtlasUtil/AtlasLog.h"
#include "ShaderManager.h"
#include "Input.h"
#include "Audio.h"
#include "Physics.h"
#include "TextureManager.h"
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

		Input* GetInput() { return _input; }

	private:

		void inputProcessing();
		void frameProcessing();

		void toggleMouseLook(bool enable);

		// Members
		Window* _applicationWindow;	// The desktop window we're rendering inside

		AtlasRenderer* _renderer;	// The renderer, could be DirectX (win32 only) or OpenGL (win32 and linux), currently we only support OpenGL
		ShaderManager* _shaderManager; // The shader loader
		Input* _input;	// Handles user input
		Audio* _audio;	// Handles audio functions
		Physics* _phys;	// Handles physics calculations
		TextureManager* _texManager; // Handles textures

		std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrame;
		double _frameDelta;
		long _frameCount;

		Scene* _currentScene;

		AtlasGame* _game;

		std::string _name;
		std::string _mainDir;

		bool _enableMouseLook;
	};
}
