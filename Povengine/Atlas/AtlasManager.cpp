#include "AtlasManager.h"

#include <sstream>
#include <string>

#include "Win32Window.h"
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"
#include "../AtlasUtil/AtlasMessageBox.h"
#include "../AtlasAPI/AtlasAPIHelper.h"

using namespace Atlas;
using namespace AtlasUtil;

AtlasManager::AtlasManager()
	:_name("Atlas"), _applicationWindow(nullptr), _renderer(nullptr), _currentScene(nullptr)
{
	for (int i = 0; i < 256; i++) {
		_keyStates[i] = false;
	}

	std::stringstream fmt;
	fmt << AtlasAPI::AtlasAPIHelper::GetUserDataPath() << AtlasAPI::AtlasAPIHelper::GetPathSeparator() << _name;
	_mainDir = fmt.str();
	fmt << AtlasAPI::AtlasAPIHelper::GetPathSeparator() << _name << ".log";

	AtlasAPI::AtlasAPIHelper::EnsureDirectory(_mainDir);
	_log = new AtlasLog(fmt.str(), false, 5);

	_log->Debug("Atlas Engine Starting");

	_shaderManager = new ShaderManager(_log, _mainDir);
}

AtlasManager::~AtlasManager()
{
	_log->Debug("Atlas Engine Stopping");

	if (_currentScene != nullptr) {
		delete _currentScene;
	}

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

	// Get different windows based on platform, currently only Win32
#ifdef _WIN32
	_log->Debug("Creating new (Win32) window");
	_applicationWindow = new Win32Window(this);
#endif
#ifdef __linux__
	_log->Debug("Creating new (Linux) window");
	_applicationWindow = new LinuxWindow(this);
#endif
	return _applicationWindow;
}


bool AtlasManager::Initialise()
{
	if (_applicationWindow == nullptr) {
		return false;
	}

	_log->Debug("Creating and initialising renderer (DirectX)");

	//_renderer = new DirectXRenderer();

	_renderer = new OpenGLRenderer();
	_renderer->Initialise(800, 600, ((Win32Window*)_applicationWindow)->getWindowHandle());

	_currentScene = new Scene();
	_currentScene->LoadScene();

	std::string vertexShader = "S:\\Development\\Povengine\\Povengine\\Debug\\vertexshader.glsl";
	std::string fragShader = "S:\\Development\\Povengine\\Povengine\\Debug\\fragmentshader.glsl";

	_shaderManager->CreateShaderProgram(vertexShader, fragShader);

	return true;
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

void AtlasManager::HandleKeyPress(unsigned int keyID, bool isDown)
{
	if (keyID > 256) {
		return;
	}

	_keyStates[keyID] = isDown;
}

void AtlasManager::frameProcessing()
{
	// Update game state
	inputProcessing();

	_renderer->beginRender();
	_renderer->SetShader(_shaderManager->GetShaderProgramID());

	// Render game objects
	_currentScene->DrawScene();

	_renderer->endRender();
}

void AtlasManager::inputProcessing()
{
	// Check bindings for key presses
	_renderer->ToggleWireframe(_keyStates[0x57]);
}