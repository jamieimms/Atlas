#pragma once
#include "BaseManager.h"
#include "Window.h"
#include "AtlasRenderer.h"
#include "Scene.h"
#include "DirectXEntity.h"
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

	private:

		void frameProcessing();

		// Members
		Window* _applicationWindow;	// The desktop window we're rendering inside

		AtlasRenderer* _renderer;	// The renderer, could be DirectX (win32 only) or OpenGL (win32 and linux)
		ShaderManager* _shaderManager; // The shader loader

		AtlasUtil::AtlasLog* _log;

		Scene* _currentScene;
		DirectXEntity* _testEntity;


		std::string _name;
		std::string _mainDir;
	};
}
