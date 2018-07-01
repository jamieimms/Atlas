#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "..\Atlas\AtlasManager.h"
#include "..\Atlas\Win32Window.h"
#include "TerraFormaGame.h"
#include "..\Atlas\AtlasMessageBoxEnums.h"

using namespace Atlas;
using namespace TerraForma;
//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	std::string baseDir = "S:\\Development\\Povengine\\Build";
	TerraFormaGame game(baseDir);
	AtlasManager atlasManager(&game);

	Win32Window* window = (Win32Window*)atlasManager.getWindow();

	window->setWindowVariables(hInstance, nCmdShow);

	window->createWindow(std::string("Atlas Engine"), 1024, 768);

	if (!atlasManager.Initialise()) {
		window->showMessageBox(AtlasMessageTypeEnum::AMT_Error, "Fatal Error", "Failed to initialise.", AtlasMessageButtonsEnum::AB_OK);
		return -1;
	}

	int retVal = atlasManager.start();

	return retVal;
}