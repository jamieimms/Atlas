#include "AtlasManager.h"

#include <sstream>
#include <string>

#include "Win32Window.h"
#include "OpenGLRenderer.h"
#include "../AtlasUtil/AtlasMessageBox.h"
#include "../AtlasAPI/AtlasAPIHelper.h"
#include "IO.h"
#include "SceneParser.h"


using namespace Atlas;
using namespace AtlasUtil;

/// <summary>
/// Construct the manager
/// </summary>
AtlasManager::AtlasManager(AtlasGame* game)
	: BaseManager(nullptr), _name("Atlas"), _applicationWindow(nullptr), _renderer(nullptr), _currentScene(nullptr), _input(nullptr), _shaderManager(nullptr), _phys(nullptr)
{
	std::stringstream fmt;
	fmt << AtlasAPI::AtlasAPIHelper::GetUserDataPath() << AtlasAPI::AtlasAPIHelper::GetPathSeparator() << _name;
	_mainDir = fmt.str();
	fmt << AtlasAPI::AtlasAPIHelper::GetPathSeparator() << _name << ".log";

	AtlasAPI::AtlasAPIHelper::EnsureDirectory(_mainDir);
	_log = new AtlasLog(fmt.str(), false, 5);

	_log->Debug("Atlas Engine Starting");

	_shaderManager = new ShaderManager(_log, _mainDir);

	_input = new Input(_log);

	_audio = new Audio(_log);

	if (!_audio->Init()) {
		_log->Error("Audio manager failed to init.");
	}

	_phys = new Physics(_log);

	if (!_phys->initialisePhysicsEngine()) {
		// fall over in heap. No recovering from this.
		_log->Error("Atlas init failed.");
	}

	_texManager = new TextureManager(_log);

	_fonts = new Fonts(_log);

	_lastFrame = std::chrono::high_resolution_clock::now();
}

/// <summary>
/// Handle retrieving new data from API-based sources
/// </summary>
AtlasManager::~AtlasManager()
{
	_log->Debug("Atlas Engine Stopping");

	delete _fonts;

	delete _texManager;

	delete _phys;

	delete _audio;

	delete _currentScene;

	delete _input;

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

	_shaderManager->LoadShader("colour");
	_shaderManager->LoadShader("texture");
	_shaderManager->LoadShader("lighting");
	_shaderManager->LoadShader("text");
 	_shaderManager->LoadShader("littex");

	_fonts->LoadFont(AtlasAPI::AtlasAPIHelper::GetDataPath() + "Roboto-Regular.ttf");
	
	_currentScene = SceneParser::ParseSceneFile(IO::GetSceneDirectory() + "main.as", _texManager, _phys, _shaderManager, _audio, _fonts);
	if (_currentScene == nullptr) {
		_log->Debug("The scene failed to load.");
		return false;
	}
	_currentScene->Start();

	AtlasAPI::AtlasAPIHelper::GetTicks();

	_frameCount = 0;

	toggleMouseLook(true);

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

	_fps = 1.0f / _frameDelta;

	// Update game state
	inputProcessing();

	_currentScene->UpdateScene(_fps);

	_phys->doFrame(_frameDelta);

	_renderer->beginRender();

	// Render game objects
	_currentScene->DrawScene(_renderer->GetProjection());

	_renderer->endRender();

	_audio->ProcessAudio(_currentScene->GetCamera().GetPosition());

	_lastFrame = frameTime;
	_frameCount++;
}

/// <summary>
/// Called once per frame, allows us to process any pending user inputs 
/// </summary>
void AtlasManager::inputProcessing()
{
	static float xPos = 0;
	static float yPos = 3.0f;
	static float zPos = 5.0f;

	static float camPitch = 0.0f;
	static float camYaw = 0.0f;

	if (_input->IsKeyPressed(VK_UP))
	{
		_currentScene->GetCamera().MoveForward();
	}
	if (_input->IsKeyPressed(VK_DOWN))
	{
		_currentScene->GetCamera().Backpedal();
	}
	if (_input->IsKeyPressed(VK_LEFT))
	{
		_currentScene->GetCamera().Strafe(true);
	}
	if (_input->IsKeyPressed(VK_RIGHT))
	{
		_currentScene->GetCamera().Strafe(false);
	}
	if (_input->IsKeyPressed(VK_PRIOR))
	{

	}
	if (_input->IsKeyPressed(VK_NEXT))
	{

	}
	if (_input->IsKeyPressed(VK_SPACE)) {
		_currentScene->GetCamera().SetLookAt(0, 0, 0);
	}

	if (_input->IsKeyPressed(VK_F1)) {
		//_audio->QueueSound(0);
	}
	if (_input->IsToggleKeyPressed(VK_F2)) {
	}
	if (_input->IsToggleKeyPressed(VK_F3)) {
	}

	if (_input->IsKeyPressed(VK_ESCAPE)) {
		exit(0);
	}

	if (_enableMouseLook) {
		if (camYaw == 0 && camPitch == 0) {
			_currentScene->GetCamera().GetYaw(camYaw);
			_currentScene->GetCamera().GetPitch(camPitch);
		}
		if (!_frameCount) {
			//_currentScene->GetCamera().SetPosition(20, 10, 0);
			//_currentScene->GetCamera().SetLookAt(0, 0, 0);

			_input->ResetMouseInput();
		}
		else if (_input->GetMouseX() != 0 && _input->GetMouseY() != 0) {
			//_input->ResetMouseInput();

			camYaw += (_input->GetMouseX() * _frameDelta) * _input->GetMouseSensitivity();
			camPitch += (_input->GetMouseY() * _frameDelta) * _input->GetMouseSensitivity();

			if (camPitch >= 90.0f) {
				camPitch = 89.0f;
			}
			if (camPitch <= -90.0f) {
				camPitch = -89.0f;
			}

			_currentScene->GetCamera().SetAngle(camPitch, camYaw);

			_input->ResetMouseInput();
		}
	}

	// Enable/disable mouse look
	if (_input->IsToggleKeyPressed(VK_PAUSE)) {
		toggleMouseLook(!_enableMouseLook);
	}

	// Check bindings for key presses
	_renderer->ToggleWireframe(_input->IsKeyPressed(0x57));
}

void AtlasManager::toggleMouseLook(bool enable)
{
	_enableMouseLook = enable;
	_applicationWindow->setCaptureMouse(_enableMouseLook);
	_input->ResetMouseInput();
}

void AtlasManager::windowSizeChanged(int width, int height)
{
	_input->SetSize(width, height);
	if (_renderer != nullptr) {
		_renderer->Resize(width, height);
	}
}