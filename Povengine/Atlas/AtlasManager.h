#pragma once
#include "BaseManager.h"
#include "Window.h"
#include "Win32Renderer.h"
#include "../AtlasUtil/AtlasLog.h"

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

		Win32Renderer* _renderer;	// The renderer, TODO: abstract this away from platform if possible

		AtlasUtil::AtlasLog* _log;
	};
}
