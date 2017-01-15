#pragma once
#include "BaseManager.h"
#include "AtlasKeyEnum.h"

namespace Atlas
{
	class InputManager : protected BaseManager
	{
	public:
		InputManager();

		void HandleKeyPress(unsigned int keyID, bool isDown);

		bool IsKeyPressed(unsigned int keyID);

	private:
		bool _keyStates[256];

	};

}