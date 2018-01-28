#pragma once
// Atlas includes
#include "..\Atlas\Scene.h"

// Game includes


namespace AtlasCheckers
{
	class GameScene : public Atlas::Scene
	{
	public:
		GameScene(std::string name);

		// Overidden scene methods
		virtual void UpdateScene(double& fps);
		virtual void SceneLoaded();

		void ChangeTurn(bool isWhite, int redX, int redY, int whiteX, int whiteY);

	private:

		Atlas::Text* _turnLabel;

		Atlas::EntityInstance* _redSelect;
		Atlas::EntityInstance* _whiteSelect;

	};
}