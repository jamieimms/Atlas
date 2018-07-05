#pragma once
#include "AtlasUtil/AtlasStopwatch.h"
#include "enums/Direction2D.h"

namespace AtlasCheckers
{
	enum PlayerColours
	{
		White,
		Red
	};

	class CheckersGameState
	{
	public:
//		CheckersGameState();
//
//		void InitialiseGame();
		void NewGame();
		void MoveCursor(Direction2D direction);
		void EndTurn();
//
//		const PlayStateEnum GetPlayState() { return _sceneState; }

		PlayerColours GetCurrentTurnPlayer() const { return _currentTurnColour; }
		int GetTurn() const { return _turnsCount; }

		int GetScore(PlayerColours colour) const { return colour == PlayerColours::Red ? _redCaptures : _whiteCaptures; }

		int GetCursorX(PlayerColours colour) const { return colour == PlayerColours::Red ? _redSelectedSquareX : _whiteSelectedSquareX; }
		int GetCursorY(PlayerColours colour) const { return colour == PlayerColours::Red ? _redSelectedSquareY : _whiteSelectedSquareY; }
//
	private:
		int _turnsCount;

		int _redCaptures;
		int _whiteCaptures;
//		BoardStatesEnum _playerTurn;
//
		int _whiteSelectedSquareX;
		int _whiteSelectedSquareY;
		int _redSelectedSquareX;
		int _redSelectedSquareY;
//
//		BoardTileState* _gameBoard[ENGLISH_BOARD_SZ][ENGLISH_BOARD_SZ];
//
//		PlayStateEnum _sceneState;
//
		AtlasUtil::AtlasStopwatch _gameClock;

		PlayerColours _currentTurnColour;
//
	};
} 