#pragma once

#include "..\Atlas\AtlasGame.h"
#include <string>


namespace TerraForma
{
	class TerraFormaGame : public Atlas::AtlasGame
	{
	public:
		TerraFormaGame(std::string& basePath);
		virtual ~TerraFormaGame();

		virtual bool InitialiseGame();
		virtual Atlas::Scene* GetPendingScene();
		virtual void InputProcessing(Atlas::Input* input);
		virtual void UpdateGame(double frameDelta);

	private:
		Atlas::Scene* _scene;


	};
}