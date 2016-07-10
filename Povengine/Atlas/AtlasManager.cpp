#include "AtlasManager.h"
#include "Win32Window.h"
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"
#include "../AtlasUtil/AtlasMessageBox.h"

using namespace Atlas;
using namespace AtlasUtil;

AtlasManager::AtlasManager()
	:_applicationWindow(nullptr), _renderer(nullptr)
{
	_log = new AtlasLog(L"Atlas.log", false, 5);

	_log->Debug(L"Atlas Engine Starting");
}

AtlasManager::~AtlasManager()
{
	_log->Debug(L"Atlas Engine Stopping");

	if (_renderer != nullptr) {
		delete _renderer;
	}
	if (_applicationWindow != nullptr) {
		delete _applicationWindow;
	}

	if (_log != nullptr) {
		delete _log;
	}
}

Window* AtlasManager::getWindow()
{
	if (_applicationWindow != nullptr) {
		return _applicationWindow;
	}

	// Get different windows based on platform?
#ifdef WIN32
	_log->Debug(L"Creating new (Win32) window");
	_applicationWindow = new Win32Window();
#endif
#ifdef __linux__
	_log->Debug(L"Creating new (Linux) window");
	_applicationWindow = new LinuxWindow();
#endif
	return _applicationWindow;
}


bool AtlasManager::Initialise()
{
	if (_applicationWindow == nullptr) {
		return false;
	}

	_log->Debug(L"Creating and initialising renderer (DirectX)");

	//_renderer = new DirectXRenderer();
	_renderer = new OpenGLRenderer();
	_renderer->Initialise(800, 600, ((Win32Window*)_applicationWindow)->getWindowHandle());
}


int AtlasManager::start()
{
#ifdef WIN32
	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			frameProcessing();
		}
	}

	return (int)msg.wParam;
#endif
}

void AtlasManager::frameProcessing()
{
	// Update game state

	_renderer->beginRender();

	// Render game objects

	_renderer->endRender();

}