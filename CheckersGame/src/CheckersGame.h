#pragma once

#include <string>
#include "Atlas/AtlasGame.h"
#include "AtlasUtil/AtlasStopwatch.h"

#include "scenes/scenes.h"
#include "CheckersGameState.h"

namespace AtlasCheckers
{
	class CheckersGame : public Atlas::AtlasGame
	{
	public:
		CheckersGame(std::string& basePath);
		virtual ~CheckersGame() { }

		virtual bool InitialiseGame();

		virtual Atlas::Scene* GetPendingScene();

		virtual void InputProcessing(Atlas::Input* input);
		virtual void UpdateGame(double frameDelta);

		//void SetState(PlayStateEnum newState);

	private:

		Atlas::Scene * _currentScene;
		MainMenuScene* _mainMenuScene;
		GameScene* _gameScene;

		CheckersGameState _gameState;

		Atlas::Scene* _pendingScene;

		double _lastStateCheck;

		AtlasUtil::AtlasStopwatch _gameTick;

	};
}