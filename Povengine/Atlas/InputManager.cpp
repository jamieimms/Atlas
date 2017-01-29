#include "InputManager.h"

using namespace Atlas;

InputManager::InputManager(AtlasUtil::AtlasLog* log)
	: BaseManager(log)
{
	for (int i = 0; i < 256; i++) {
		_keyStates[i] = false;
	}

	_sensitivity = 3.0f;
	_mouseInvertedY = false;

	_initialised = true;
}

/// <summary>
/// Handles a key press (key up or down) by setting that key's state
/// </summary>
/// <param name="keyID">ID of the key to set/unset</param>
/// <param name="isDown">bool indicating if the new key state is down or up</param>
void InputManager::HandleKeyPress(unsigned int keyID, bool isDown)
{
	if (keyID >= 256) {
		return;
	}

	_keyStates[keyID] = isDown;
}

/// <summary>
///	Get the pressed state of the given key
/// </summary>
/// <param name="keyID">ID of the key to set/unset</param>
/// <param name="isDown">bool indicating if the new key state is down or up</param>
/// <returns>true if key is pressed, otherwise false. False if invalid key</returns>
bool InputManager::IsKeyPressed(unsigned int keyID)
{
	if (keyID >= 256) {
		return false;
	}

	return _keyStates[keyID];
}

/// <summary>
///	Receive mouse input from window
/// </summary>
/// <param name="keyID">ID of the key to set/unset</param>
/// <param name="isDown">bool indicating if the new key state is down or up</param>
/// <returns>true if key is pressed, otherwise false. False if invalid key</returns>
void InputManager::HandleMouseInput(int x, int y)
{
	_mouseX = x - (_width /2);
	_mouseY = y - (_height / 2);
}

void InputManager::ResetMouseInput()
{
	_mouseX = 0;
	_mouseY = 0;
}