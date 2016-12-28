#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "..\Atlas\AtlasManager.h"
#include "..\Atlas\Win32Window.h"

using namespace Atlas;
//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	AtlasManager atlasManager;

	Win32Window* window = (Win32Window*)atlasManager.getWindow();

	window->setWindowVariables(hInstance, nCmdShow);

	window->createWindow("Atlas Engine", 800, 600);

	atlasManager.Initialise();

	int retVal = atlasManager.start();

	return retVal;
}