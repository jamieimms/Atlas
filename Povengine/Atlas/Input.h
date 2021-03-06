#pragma once
#include "BaseManager.h"
#include "AtlasKey.h"
#include "../AtlasUtil/AtlasStopwatch.h"

namespace Atlas
{
	struct KeyState
	{
		bool pressed;
		bool hasToggled;
		AtlasUtil::AtlasStopwatch toggleTimer;
		double toggleRepeat;
	};

	class Input : protected BaseManager
	{
	public:
		Input(AtlasUtil::AtlasLog* log);

		void SetSize(int w, int h) { _width = w; _height = h; }

		void HandleKeyPress(unsigned int keyID, bool isDown);
		void HandleMouseInput(int x, int y);
		void HandleMouseClick(int x, int y, bool isLeft);

		void ResetMouseInput();

		bool IsKeyPressed(const unsigned int keyID, double noRepeat = 0);
		bool IsToggleKeyPressed(const unsigned int keyID);

		int GetMouseX() { return _mouseX; }
		int GetMouseY() { return _mouseInvertedY ? _mouseY : -_mouseY; }

		float GetMouseSensitivity() { return _sensitivity; }

	private:
		KeyState _keyStates[256];

		int _width;
		int _height;

		int _mouseX;
		int _mouseY;

		int _lastClickX;
		int _lastClickY;
		bool _clickPending;
		bool _wasLastClickLeft;

		float _sensitivity;
		bool _mouseInvertedY;

	};

}