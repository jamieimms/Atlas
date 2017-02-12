#include "AtlasManager.h"

#include <sstream>
#include <string>

#include "Win32Window.h"
#include "OpenGLRenderer.h"
#include "../AtlasUtil/AtlasMessageBox.h"
#include "../AtlasAPI/AtlasAPIHelper.h"
#include "FileManager.h"


using namespace Atlas;
using namespace AtlasUtil;

/// <summary>
/// Construct the manager
/// </summary>
AtlasManager::AtlasManager()
	: BaseManager(nullptr), _name("Atlas"), _applicationWindow(nullptr), _renderer(nullptr), _currentScene(nullptr), _inputManager(nullptr), _shaderManager(nullptr), _phys(nullptr)
{
	std::stringstream fmt;
	fmt << AtlasAPI::AtlasAPIHelper::GetUserDataPath() << AtlasAPI::AtlasAPIHelper::GetPathSeparator() << _name;
	_mainDir = fmt.str();
	fmt << AtlasAPI::AtlasAPIHelper::GetPathSeparator() << _name << ".log";

	AtlasAPI::AtlasAPIHelper::EnsureDirectory(_mainDir);
	_log = new AtlasLog(fmt.str(), false, 5);

	_log->Debug("Atlas Engine Starting");

	_shaderManager = new ShaderManager(_log, _mainDir);

	_inputManager = new InputManager(_log);

	_audio = new AudioManager(_log);

	if (!_audio->Init()) {
		_log->Error("Audio manager failed to init.");
	}

	_phys = new PhysicsManager(_log);

	if (!_phys->initialisePhysicsEngine()) {
		// fall over in heap. No recovering from this.
		_log->Error("Atlas init failed.");
	}

	_texManager = new TextureManager(_log);

	std::string s = "S:\\Development\\Povengine\\Data\\Sound\\";

	_audio->LoadSound(s + "118.wav", 0);

	_lastFrame = std::chrono::high_resolution_clock::now();
}

/// <summary>
/// Handle retrieving new data from API-based sources
/// </summary>
AtlasManager::~AtlasManager()
{
	_log->Debug("Atlas Engine Stopping");

	delete _texManager;

	delete _phys;

	delete _audio;

	delete _currentScene;

	delete _inputManager;

	delete _renderer;

	delete _applicationWindow;

	delete _log;
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

	_log->Debug("Creating and initialising Atlas Engine");

	_renderer = new OpenGLRenderer();
#ifdef _WIN32
	HDC context = GetDC(((Win32Window*)_applicationWindow)->getWindowHandle());
	/*      Pixel format index
	*/
	int nPixelFormat;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
		1,                                      //default version
		PFD_DRAW_TO_WINDOW |                    //window drawing support
		PFD_SUPPORT_OPENGL |                    //opengl support
		PFD_DOUBLEBUFFER,                       //double buffering support
		PFD_TYPE_RGBA,                          //RGBA color mode
		32,                                     //32 bit color mode
		0, 0, 0, 0, 0, 0,                       //ignore color bits
		0,                                      //no alpha buffer
		0,                                      //ignore shift bit
		0,                                      //no accumulation buffer
		0, 0, 0, 0,                             //ignore accumulation bits
		16,                                     //16 bit z-buffer size
		0,                                      //no stencil buffer
		0,                                      //no aux buffer
		PFD_MAIN_PLANE,                         //main drawing plane
		0,                                      //reserved
		0, 0, 0 };                              //layer masks ignored

												/*      Choose best matching format*/
	nPixelFormat = ChoosePixelFormat(context, &pfd);

	/*      Set the pixel format to the device context*/
	SetPixelFormat(context, nPixelFormat, &pfd);
	if (!_renderer->Initialise(1024, 768, context)) {
		_log->Debug("Win32 OpenGL renderer failed to initialise.");
	}
#endif

	std::string shaderName = "colour";
	_shaderManager->LoadShader(shaderName);
	shaderName = "texture";
	_shaderManager->LoadShader(shaderName);
	shaderName = "lighting";
	_shaderManager->LoadShader(shaderName);
	
	_currentScene = new Scene(_texManager, _phys, _shaderManager);
	_currentScene->LoadFromFile(FileManager::GetSceneDirectory() + "01.as");

	AtlasAPI::AtlasAPIHelper::GetTicks();

	_frameCount = 0;

	_initialised = true;

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
/// Called each time a frame can be processed.
/// </summary>
void AtlasManager::frameProcessing()
{
	auto frameTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsedSec = frameTime - _lastFrame;
	_frameDelta = elapsedSec.count();

	// Update game state
	inputProcessing();

	_audio->ProcessAudio();
	
	_phys->doFrame(_frameDelta);

	_renderer->beginRender();

	// Render game objects
	_currentScene->DrawScene(_renderer->GetProjection());

	_renderer->endRender();

	_lastFrame = frameTime;
	_frameCount++;
}

/// <summary>
/// Called once per frame, allows us to process any pending user inputs 
/// </summary>
void AtlasManager::inputProcessing()
{
	static bool enableMouseLook = true;
	static float xPos = 0;
	static float yPos = 3.0f;
	static float zPos = 5.0f;

	static float camPitch = 0.0f;
	static float camYaw = 0.0f;

	if (_inputManager->IsKeyPressed(VK_UP))
	{
		_currentScene->GetCamera().MoveForward();
	}
	if (_inputManager->IsKeyPressed(VK_DOWN))
	{
		_currentScene->GetCamera().Backpedal();
	}
	if (_inputManager->IsKeyPressed(VK_LEFT))
	{
		_currentScene->GetCamera().Strafe(true);
	}
	if (_inputManager->IsKeyPressed(VK_RIGHT))
	{
		_currentScene->GetCamera().Strafe(false);
	}
	if (_inputManager->IsKeyPressed(VK_PRIOR))
	{

	}
	if (_inputManager->IsKeyPressed(VK_NEXT))
	{

	}
	if (_inputManager->IsKeyPressed(VK_SPACE)) {
		_currentScene->GetCamera().SetLookAt(0, 0, 0);
	}

	if (_inputManager->IsKeyPressed(VK_F1)) {
		_audio->QueueSound(0);
	}

	if (_inputManager->IsKeyPressed(VK_ESCAPE)) {
		exit(0);
	}

	// Enable/disable mouse look
	if (_inputManager->IsToggleKeyPressed(VK_PAUSE)) {
		enableMouseLook = !enableMouseLook;
		_applicationWindow->setCaptureMouse(enableMouseLook);
		_inputManager->ResetMouseInput();
	}

	if (enableMouseLook) {
		if (!_frameCount) {

			_currentScene->GetCamera().SetPosition(20, 10, 0);
			_currentScene->GetCamera().SetLookAt(0, 0, 0);

			_inputManager->ResetMouseInput();
		}
		else if (_inputManager->GetMouseX() != 0 && _inputManager->GetMouseY() != 0) {
			camYaw += ((_inputManager->GetMouseX()) * _frameDelta) * _inputManager->GetMouseSensitivity();
			camPitch += (_inputManager->GetMouseY() * _frameDelta) * _inputManager->GetMouseSensitivity();

			if (camPitch >= 90.0f) {
				camPitch = 89.0f;
			}
			if (camPitch <= -90.0f) {
				camPitch = -89.0f;
			}

			_currentScene->GetCamera().SetAngle(camPitch, camYaw);

			_inputManager->ResetMouseInput();
		}
	}

	// Check bindings for key presses
	_renderer->ToggleWireframe(_inputManager->IsKeyPressed(0x57));
}

void AtlasManager::windowSizeChanged(int width, int height)
{
	_inputManager->SetSize(width, height);
	if (_renderer != nullptr) {
		_renderer->Resize(width, height);
	}
}