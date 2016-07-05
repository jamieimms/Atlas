#pragma once
#include "BaseManager.h"
#include "Window.h"

namespace Atlas
{
	class AtlasManager : protected BaseManager
	{
	public:
		AtlasManager();
		~AtlasManager();

		Window* getWindow();

		int start();

	private:

		// Members
		Window* _applicationWindow;
			
	};
}
