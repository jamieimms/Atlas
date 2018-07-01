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
	: BaseManager(nullptr), _name("Atlas"), _applicationWindow(nullptr), _currentScene(nullptr)
{
	std::stringstream fmt;
	fmt << AtlasAPI::AtlasAPIHelper::GetUserDataPath() << AtlasAPI::AtlasAPIHelper::GetPathSeparator() << _name;
	_mainDir = fmt.str();
	fmt << AtlasAPI::AtlasAPIHelper::GetPathSeparator() << _name << ".log";

	AtlasAPI::AtlasAPIHelper::EnsureDirectory(_mainDir);
	_subsystems._log = new AtlasLog(fmt.str(), false, 5);

	_game = game;

	_subsystems._log->Debug("Atlas Engine Starting");

	_subsystems._shaderManager = new ShaderManager(_subsystems._log, _mainDir);
	_subsystems._input = new Input(_subsystems._log);
	
	_subsystems._audio = new Audio(_subsystems._log);
	if (!_subsystems._audio->Init()) {
		_subsystems._log->Error("Audio manager failed to init.");
	}

	_subsystems._phys = new Physics(_subsystems._log);
	if (!_subsystems._phys->initialisePhysicsEngine()) {
		// fall over in heap. No recovering from this.
		_subsystems._log->Error("Atlas init failed.");
	}

	_subsystems._texManager = new TextureManager(_subsystems._log);
	_subsystems._fonts = new Fonts(_subsystems._log);
	_subsystems._geometry = new Geometry();

	_lastFrame = std::chrono::high_resolution_clock::now();

	_enableMouseLook = false;
}

/// <summary>
/// Handle retrieving new data from API-based sources
/// </summary>
AtlasManager::~AtlasManager()
{
	_subsystems._log->Debug("Atlas Engine Stopping");

	delete _currentScene;
	delete _subsystems._geometry;
	delete _subsystems._fonts;
	delete _subsystems._texManager;
	delete _subsystems._phys;
	delete _subsystems._audio;
	delete _subsystems._input;
	delete _subsystems._renderer;
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
	_subsystems._log->Debug("Creating new (Win32) window");
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

	_subsystems._log->Debug("Creating and initialising Atlas Engine");

	_subsystems._renderer = new OpenGLRenderer();
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
	if (!_subsystems._renderer->Initialise(_applicationWindow->GetWidth(), _applicationWindow->GetHeight(), context)) {
		_subsystems._log->Debug("Win32 OpenGL renderer failed to initialise.");
	}
#endif

	LoadShaders();
	
	std::string fontName = AtlasAPI::AtlasAPIHelper::GetDataPath() + "Roboto-Regular.ttf";

	_subsystems._fonts->LoadFont(fontName, FontStyleEnum::Small);
	_subsystems._fonts->LoadFont(fontName, FontStyleEnum::Normal);
	_subsystems._fonts->LoadFont(fontName, FontStyleEnum::Big);
	_subsystems._fonts->LoadFont(fontName, FontStyleEnum::Title);

	AtlasAPI::AtlasAPIHelper::GetTicks();

	windowSizeChanged(_applicationWindow->GetWidth(), _applicationWindow->GetHeight());

	//toggleMouseLook(true);

	_game->InitialiseGame();

	_initialised = true;

	return true;
}

/// <summary>
/// Begins a scene change. Will show a loading screen and allow it to render before completing the load of the next
/// scene
/// </summary>
void AtlasManager::BeginSceneChange(Scene* nextScene)
{
	_oldScene = _currentScene;

	_currentScene = new Scene("loading");
	SceneParser::ParseSceneFile(_currentScene, IO::GetSceneDirectory() + "loading.as", _subsystems);
	_currentScene->Start();

	_nextScene = nextScene;
}

/// <summary>
/// If a scene change has begun, finish will actually load the scene
/// </summary>
void AtlasManager::FinishSceneChange()
{
	if (_oldScene != nullptr) {
		_oldScene->Stop();
		//_oldScene->UnloadScene();
		//delete _oldScene;
		_oldScene = nullptr;
	}

	_subsystems._audio->StopAllSounds();

	if (!_nextScene->IsLoaded()) {
		SceneParser::ParseSceneFile(_nextScene, IO::GetSceneDirectory() + _nextScene->GetName(), _subsystems);
	}
	Scene* temp = _currentScene;	// This is the loading screen at this point
	
	_currentScene = _nextScene;
	_currentScene->Start();

	_nextScene = nullptr;
	
	temp->Stop();
	temp->UnloadScene();
	delete temp;
}

/// <summary>
/// Load the shaders
/// </summary>
void AtlasManager::LoadShaders()
{
	_subsystems._shaderManager->LoadShader("colour");
	_subsystems._shaderManager->LoadShader("texture");
	_subsystems._shaderManager->LoadShader("lighting");
	_subsystems._shaderManager->LoadShader("text");
	_subsystems._shaderManager->LoadShader("littex");
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
	auto newScene = _game->GetPendingScene();
	if (newScene != nullptr) {
		BeginSceneChange(newScene);
	}

	auto frameTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsedSec = frameTime - _lastFrame;
	_frameDelta = elapsedSec.count();

	// Update game state
	inputProcessing();

	_game->UpdateGame(_frameDelta);

	_currentScene->UpdateScene(_frameDelta);

	_subsystems._phys->doFrame(_frameDelta);

	_subsystems._renderer->beginRender();

	// Render game objects
	_currentScene->DrawScene(_subsystems._renderer->GetProjection(), _subsystems._renderer->Get2DProjection());

	_subsystems._renderer->endRender();

	_subsystems._audio->ProcessAudio(_currentScene->GetCamera().GetPosition());

	_lastFrame = frameTime;

	if (_nextScene != nullptr) {
		FinishSceneChange();
	}
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

	//if (_subsystems._input->IsKeyPressed(VK_UP))
	//{
	//	_currentScene->GetCamera().MoveForward();
	//}
	//if (_subsystems._input->IsKeyPressed(VK_DOWN))
	//{
	//	_currentScene->GetCamera().Backpedal();
	//}
	//if (_subsystems._input->IsKeyPressed(VK_LEFT))
	//{
	//	_currentScene->GetCamera().Strafe(true);
	//}
	//if (_subsystems._input->IsKeyPressed(VK_RIGHT))
	//{
	//	_currentScene->GetCamera().Strafe(false);
	//}
	//if (_subsystems._input->IsKeyPressed(VK_PRIOR))
	//{

	//}
	//if (_subsystems._input->IsKeyPressed(VK_NEXT))
	//{

	//}
	if (_subsystems._input->IsKeyPressed(VK_SPACE)) {
		_currentScene->GetCamera().SetLookAt(0, 0, 0);
	}

	//if (_subsystems._input->IsToggleKeyPressed(VK_F2)) {
	//}
	//if (_subsystems._input->IsToggleKeyPressed(VK_F3)) {
	//}
	
	//if (_subsystems._input->IsKeyPressed(VK_ESCAPE)) {
	//	exit(0);
	//}

	if (_enableMouseLook) {
		if (camYaw == 0 && camPitch == 0) {
			_currentScene->GetCamera().GetYaw(camYaw);
			_currentScene->GetCamera().GetPitch(camPitch);
		}
		else if (_subsystems._input->GetMouseX() != 0 && _subsystems._input->GetMouseY() != 0) {

			camYaw += (_subsystems._input->GetMouseX() * _frameDelta) * _subsystems._input->GetMouseSensitivity();
			camPitch += (_subsystems._input->GetMouseY() * _frameDelta) * _subsystems._input->GetMouseSensitivity();

			if (camPitch >= 90.0f) {
				camPitch = 89.0f;
			}
			if (camPitch <= -90.0f) {
				camPitch = -89.0f;
			}

			_currentScene->GetCamera().SetAngle(camPitch, camYaw);

			_subsystems._input->ResetMouseInput();
		}
	}
	
	// Enable/disable mouse look
	if (_subsystems._input->IsToggleKeyPressed(VK_PAUSE)) {
		toggleMouseLook(!_enableMouseLook);
	}

	// Check bindings for key presses
	_subsystems._renderer->ToggleWireframe(_subsystems._input->IsKeyPressed(0x57));

	_game->InputProcessing(_subsystems._input);
}

/// <summary>
/// Enable/disable mouse look with the camera 
/// </summary>
void AtlasManager::toggleMouseLook(bool enable)
{
	_enableMouseLook = enable;
	_applicationWindow->setCaptureMouse(_enableMouseLook);
	_subsystems._input->ResetMouseInput();
}

/// <summary>
/// If the size of the window changes, this method adjusts the viewport
/// </summary>
void AtlasManager::windowSizeChanged(int width, int height)
{
	_subsystems._input->SetSize(width, height);
	if (_subsystems._renderer != nullptr) {
		_subsystems._renderer->Resize(width, height);
	}
}