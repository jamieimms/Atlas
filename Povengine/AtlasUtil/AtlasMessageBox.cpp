#include "AtlasMessageBox.h"
#ifdef WIN32
#include <Windows.h>
#endif

using namespace AtlasUtil;

void AtlasMessageBox::ErrorMessageBox(char* message, char* title)
{
#ifdef WIN32
	
	//MessageBox(NULL, message, title, MB_OK | MB_ICONSTOP);

#endif
#ifdef __linux__

	// Linux message box???

#endif

}
