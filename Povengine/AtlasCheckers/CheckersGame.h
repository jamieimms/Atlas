#pragma once

#include "..\Atlas\AtlasGame.h"
#include "..\AtlasUtil\AtlasStopwatch.h"

#include "BoardStatesEnum.h"
#include "MainMenuScene.h"

namespace AtlasCheckers
{
	enum CheckersStateEnum
	{
		MainMenu,
		Playing
	};

	class CheckersGame : public Atlas::AtlasGame
	{
	public:
		CheckersGame() { }
		virtual ~CheckersGame() { }

		virtual bool InitialiseGame();

		virtual Atlas::Scene* GetInitialScene();

		virtual void InputProcessing(const Atlas::Input* input);
		virtual void UpdateGame();

		void SetState(CheckersStateEnum newState);

	private:
		void SetupGame();

		int gameBoard[8][8];

		int _turnsCount;
		BoardStatesEnum _playerTurn;

		CheckersStateEnum _gameState;
		
		MainMenuScene* _menuScene;

		AtlasUtil::AtlasStopwatch _uiKeystrokeDelay;

	};
}