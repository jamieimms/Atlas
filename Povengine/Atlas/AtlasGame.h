#pragma once

#include <string>
#include "Input.h"
#include "Scene.h"

namespace Atlas
{
	class AtlasGame
	{
	public:
		AtlasGame() {}
		~AtlasGame() {}

		virtual bool InitialiseGame() = 0;

		virtual Scene* GetInitialScene() = 0;

		virtual void InputProcessing(const Input* input) = 0;

		virtual void UpdateGame() = 0;

	private:

	};
}