#pragma once
// Atlas includes
#include "Atlas/Scene.h"
#include "Atlas/Input.h"

#include "../CheckersGameState.h"

namespace AtlasCheckers
{
	const int BOARD_SIZE = 8;

	class GameScene : public Atlas::Scene
	{
	public:
		GameScene(std::string name);

		// Overidden scene methods
		virtual void UpdateScene(double frameDelta);
		virtual void SceneLoaded();
		virtual void InputProcessing(Atlas::Input* input);

	private:
		virtual void LoadDynamicAssets();
		void AddBoardTile(int xPos, int zPos, bool isWhite);
		void AddPiece(int xPos, int zPos, int numID, bool isWhite);

		glm::vec3 _redCamHome;
		glm::vec3 _whiteCamHome;

		double _uiTick;
		bool _stateUpdatePending;

		// Scene elements
		Atlas::Text* _turnLabel;
		Atlas::Text* _turnCountLabel;
		Atlas::Text* _whiteCapturesLabel;
		Atlas::Text* _redCapturesLabel;
		Atlas::EntityInstance* _redSelect;
		Atlas::EntityInstance* _whiteSelect;

		// State variables
		CheckersGameState _state;
	};
}