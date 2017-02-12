#pragma once
#include "BaseManager.h"
#include <chrono>
#include "Window.h"
#include "AtlasRenderer.h"
#include "Scene.h"
#include "../AtlasUtil/AtlasLog.h"
#include "ShaderManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "TextureManager.h"

namespace Atlas
{
	class AtlasManager : protected BaseManager
	{
	public:
		AtlasManager();
		~AtlasManager();

		Window* getWindow();

		bool Initialise();

		void windowSizeChanged(int width, int height);

		int start();

		InputManager* Input() { return _inputManager; }

	private:

		void inputProcessing();
		void frameProcessing();

		// Members
		Window* _applicationWindow;	// The desktop window we're rendering inside

		AtlasRenderer* _renderer;	// The renderer, could be DirectX (win32 only) or OpenGL (win32 and linux), currently we only support OpenGL
		ShaderManager* _shaderManager; // The shader loader
		InputManager* _inputManager;	// Handles user input
		AudioManager* _audio;	// Handles audio functions
		PhysicsManager* _phys;	// Handles physics calculations
		TextureManager* _texManager; // Handles textures

		std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrame;
		double _frameDelta;
		long _frameCount;

		Scene* _currentScene;

		std::string _name;
		std::string _mainDir;
	};
}
