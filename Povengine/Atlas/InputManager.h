#pragma once
#include "BaseManager.h"
#include "AtlasKeyEnum.h"

namespace Atlas
{
	class InputManager : protected BaseManager
	{
	public:
		InputManager();

		void SetSize(int w, int h) { _width = w; _height = h; }

		void HandleKeyPress(unsigned int keyID, bool isDown);
		void HandleMouseInput(int x, int y);


		bool IsKeyPressed(unsigned int keyID);

		int GetMouseX() { return _mouseX; }
		int GetMouseY() { return _mouseY; }


	private:
		bool _keyStates[256];

		int _width;
		int _height;

		int _mouseX;
		int _mouseY;

	};

}