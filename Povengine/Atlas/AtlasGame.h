#pragma once

#include <string>
#include "Input.h"
#include "Scene.h"

namespace Atlas
{
	class AtlasGame
	{
	public:
		AtlasGame(std::string& baseDirectory);
		~AtlasGame() {}

		virtual bool InitialiseGame() = 0;

		virtual Scene* GetPendingScene() = 0;

		virtual void InputProcessing(Input* input) = 0;

		virtual void UpdateGame(double frameDelta) = 0;

	};
}