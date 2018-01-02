#pragma once

#include <string>
#include "Input.h"

namespace Atlas
{
	class AtlasGame
	{
	public:
		AtlasGame() {}
		~AtlasGame() {}

		virtual std::string GetInitialScene() = 0;

		virtual void InputProcessing(const Input* input) = 0;

		virtual void UpdateGame() = 0;

	private:

	};
}