#include "Input.h"

using namespace Atlas;

Input::Input(AtlasUtil::AtlasLog* log)
	: BaseManager(log)
{
	for (int i = 0; i < 256; i++) {
		_keyStates[i].hasToggled = false;
		_keyStates[i].pressed = false;
		_keyStates[i].toggleRepeat = 0;
		_keyStates[i].toggleTimer.Reset();
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
void Input::HandleKeyPress(unsigned int keyID, bool isDown)
{
	if (keyID >= 256) {
		return;
	}

	_keyStates[keyID].pressed = isDown;
	if (!isDown) {
		_keyStates[keyID].hasToggled = false;
	}
}

/// <summary>
///	Get the pressed state of the given key
/// </summary>
/// <param name="keyID">ID of the key to set/unset</param>
/// <param name="toggleRepeat">specify in milliseconds when this key can be triggered again (default 0 = immediately)</param>
/// <returns>true if key is pressed, otherwise false. False if invalid key</returns>
bool Input::IsKeyPressed(const unsigned int keyID,  double toggleRepeat)
{
	if (keyID >= 256) {
		return false;
	}

	KeyState* key = &_keyStates[keyID];

	if (!key->pressed) {
		return false;
	}

	if (key->toggleTimer.IsRunning()) {
		if (key->toggleRepeat <= key->toggleTimer.GetElapsedMs()) {
			key->toggleRepeat = toggleRepeat;
			key->toggleTimer.Restart();
			return true;
		}
		else {
			return false;
		}
	}

	if (toggleRepeat > 0) {
		key->toggleRepeat = toggleRepeat;
		key->toggleTimer.Start();
	}

	return true;
}

/// <summary>
///	Get the pressed state of the given toggle key. Same as IsKeyPressed but will only return true
/// once per press of the key
/// </summary>
/// <param name="keyID">ID of the key to set/unset</param>
/// <param name="isDown">bool indicating if the new key state is down or up</param>
/// <returns>true if key is pressed, otherwise false. False if invalid key</returns>
bool Input::IsToggleKeyPressed(const unsigned int keyID)
{
	bool pressed = IsKeyPressed(keyID);

	if (pressed && !_keyStates[keyID].hasToggled) {
		_keyStates[keyID].hasToggled = true;
		return true;
	}
	return false;
}

/// <summary>
///	Receive mouse input from window
/// </summary>
/// <param name="keyID">ID of the key to set/unset</param>
/// <param name="isDown">bool indicating if the new key state is down or up</param>
/// <returns>true if key is pressed, otherwise false. False if invalid key</returns>
void Input::HandleMouseInput(int x, int y)
{
	_mouseX = x - (_width / 2);
	_mouseY = y - (_height / 2);
}

void Input::ResetMouseInput()
{
	_mouseX = 0;
	_mouseY = 0;
}

/// <summary>
///	Receive mouse input from window
/// </summary>
void Input::HandleMouseClick(int x, int y, bool isLeft)
{
	_lastClickX = x;
	_lastClickY = y;
	_wasLastClickLeft = isLeft;
	_clickPending = true;
}