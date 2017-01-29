#pragma once
#include "BaseManager.h"
#include "AtlasKeyEnum.h"

namespace Atlas
{
	class InputManager : protected BaseManager
	{
	public:
		InputManager(AtlasUtil::AtlasLog* log);

		void SetSize(int w, int h) { _width = w; _height = h; }

		void HandleKeyPress(unsigned int keyID, bool isDown);
		void HandleMouseInput(int x, int y);
		void ResetMouseInput();

		bool IsKeyPressed(unsigned int keyID);

		int GetMouseX() { return _mouseX; }
		int GetMouseY() { return _mouseInvertedY ? _mouseY : -_mouseY; }

		float GetMouseSensitivity() { return _sensitivity; }

	private:
		bool _keyStates[256];

		int _width;
		int _height;

		int _mouseX;
		int _mouseY;

		float _sensitivity;
		bool _mouseInvertedY;

	};

}