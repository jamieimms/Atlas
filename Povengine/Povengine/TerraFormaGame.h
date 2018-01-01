#pragma once

#include "..\Atlas\AtlasGame.h"

namespace TerraForma
{
	class TerraFormaGame : public Atlas::AtlasGame
	{
	public:
		TerraFormaGame() { }
		virtual ~TerraFormaGame() { }

		virtual std::string GetInitialScene();


	};
}