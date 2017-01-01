#include "AtlasManager.h"

#include <sstream>
#include <string>

#include "Win32Window.h"
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"
#include "../AtlasUtil/AtlasMessageBox.h"
#include "../AtlasAPI/AtlasAPIHelper.h"
#include "Primitive.h"

using namespace Atlas;
using namespace AtlasUtil;

/// <summary>
/// Construct the manager
/// </summary>
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

/// <summary>
/// Handle retrieving new data from API-based sources
/// </summary>
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

/// <summary>
/// Creates the platform appropriate window and returns it
/// </summary>
/// <returns>a platform specific window based on the Window class</returns>
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

/// <summary>
/// Initialises the sub-systems of the Atlas Engine
/// </summary>
/// <returns>true if initialised successfully, otherwise false</returns>
bool AtlasManager::Initialise()
{
	if (_applicationWindow == nullptr) {
		return false;
	}

	_log->Debug("Creating and initialising renderer (DirectX)");

	//_renderer = new DirectXRenderer();

	_renderer = new OpenGLRenderer();
	_renderer->Initialise(800, 600, ((Win32Window*)_applicationWindow)->getWindowHandle());

	std::string vertexShader = "S:\\Development\\Povengine\\Povengine\\Debug\\vertexshader.glsl";
	std::string fragShader = "S:\\Development\\Povengine\\Povengine\\Debug\\fragmentshader.glsl";
	std::string originVertShader = "S:\\Development\\Povengine\\Povengine\\Debug\\originshader.glsl";

	auto shader1 = _shaderManager->CreateShaderProgram(vertexShader, fragShader);
	auto shader2 = _shaderManager->CreateShaderProgram(originVertShader, fragShader);

	_currentScene = new Scene();
	_currentScene->LoadScene(shader1, shader2);


	return true;
}

/// <summary>
/// Starts the engine running by entering the application loop (this may be better moved to the Window classes)
/// </summary>
/// <returns>returns the exit code when the application loop finishes</returns>
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

/// <summary>
/// Handles a key press (key up or down) by setting that key's state
/// </summary>
/// <param name="keyID">ID of the key to set/unset</param>
/// <param name="isDown">bool indicating if the new key state is down or up</param>
void AtlasManager::HandleKeyPress(unsigned int keyID, bool isDown)
{
	if (keyID > 256) {
		return;
	}

	_keyStates[keyID] = isDown;
}

/// <summary>
/// Called each time a frame can be processed.
/// </summary>
void AtlasManager::frameProcessing()
{
	// Update game state
	inputProcessing();

	_renderer->beginRender();

	// Render game objects
	_currentScene->DrawScene();

	_renderer->endRender();
}

/// <summary>
/// Called once per frame, allows us to process any pending user inputs 
/// </summary>
void AtlasManager::inputProcessing()
{
	static float yPos = 0.0f;
	// Check bindings for key presses
	_renderer->ToggleWireframe(_keyStates[0x57]);

	if (_keyStates[0x26]) {	// Up arrow
		auto temp = (Primitive*)_currentScene->GetEntity(1);
		yPos += 0.01f;
		temp->SetPosition(0, yPos, 0);
	}
}