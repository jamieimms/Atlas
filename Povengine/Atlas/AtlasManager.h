#pragma once
#include "BaseManager.h"
#include "Window.h"
#include "AtlasRenderer.h"
#include "Scene.h"
#include "../AtlasUtil/AtlasLog.h"
#include "ShaderManager.h"

namespace Atlas
{
	class AtlasManager : protected BaseManager
	{
	public:
		AtlasManager();
		~AtlasManager();

		Window* getWindow();

		bool Initialise();

		int start();

		void HandleKeyPress(unsigned int keyID, bool isDown);

	private:

		void inputProcessing();
		void frameProcessing();

		// Members
		Window* _applicationWindow;	// The desktop window we're rendering inside

		AtlasRenderer* _renderer;	// The renderer, could be DirectX (win32 only) or OpenGL (win32 and linux), currently we only support OpenGL
		ShaderManager* _shaderManager; // The shader loader

		AtlasUtil::AtlasLog* _log;

		Scene* _currentScene;

		std::string _name;
		std::string _mainDir;

		bool _keyStates[256];
	};
}
