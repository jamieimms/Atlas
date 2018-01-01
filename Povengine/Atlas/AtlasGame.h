#pragma once

#include <string>

namespace Atlas
{
	class AtlasGame
	{
	public:
		AtlasGame() {}
		~AtlasGame() {}

		virtual std::string GetInitialScene() = 0;

	private:

	};
}