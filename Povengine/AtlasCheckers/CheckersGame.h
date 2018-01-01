#pragma once

#include "..\Atlas\AtlasGame.h"

#include "BoardStatesEnum.h"

namespace AtlasCheckers
{
	class CheckersGame : public Atlas::AtlasGame
	{
	public:
		CheckersGame() { }
		virtual ~CheckersGame() { }

		virtual std::string GetInitialScene();

		

	private:
		void SetupGame();

		int gameBoard[8][8];

		int _turnsCount;
		BoardStatesEnum _playerTurn;
		



	};
}