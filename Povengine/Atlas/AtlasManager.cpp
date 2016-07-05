#include "AtlasManager.h"
#include "Win32Window.h"

using namespace Atlas;

AtlasManager::AtlasManager()
	:_applicationWindow(nullptr)
{

}

AtlasManager::~AtlasManager()
{
	if (_applicationWindow != nullptr) {
		delete _applicationWindow;
	}
}

Window* AtlasManager::getWindow()
{
	// Get different windows based on platform?

	_applicationWindow = new Win32Window();

	return _applicationWindow;
}

int AtlasManager::start()
{
	return 0;
}