#include "CheckersGameState.h"

using namespace AtlasCheckers;

///
///
//
void CheckersGameState::NewGame()
{
	_turnsCount = 1;
	_whiteCaptures = 0;
	_redCaptures = 0;
	_currentTurnColour = PlayerColours::White;

	_whiteSelectedSquareX = -7;
	_whiteSelectedSquareY = -7;
	_redSelectedSquareX = 7;
	_redSelectedSquareY = 7;

	_gameClock.Restart();
}

///
void CheckersGameState::EndTurn()
{
	_currentTurnColour = _currentTurnColour == PlayerColours::White ? PlayerColours::Red : PlayerColours::White;

	if (_currentTurnColour == PlayerColours::White) {
		_turnsCount++;
	}
}

void CheckersGameState::MoveCursor(Direction2D direction)
{
	auto currentX = _currentTurnColour == PlayerColours::Red ? &_redSelectedSquareX : &_whiteSelectedSquareX;
	auto currentY = _currentTurnColour == PlayerColours::Red ? &_redSelectedSquareY : &_whiteSelectedSquareY;

	int increment = 2;

	// Red's view is upside down, so we need to invert their directions;
	if (_currentTurnColour == PlayerColours::Red) {
		increment = -2;
	}

	switch (direction) {
	case Direction2D::Up:
		*currentY+=increment;
		break;
	case Direction2D::Down:
		*currentY-= increment;

		break;
	case Direction2D::Left:
		*currentX+= increment;

		break;
	case Direction2D::Right:
		*currentX-= increment;
		break;
	}

	if (*currentX < -7) {
		*currentX = -7;
	}
	else if (*currentX > 7) {
		*currentX = 7;
	}	
	if (*currentY < -7) {
		*currentY = -7;
	}
	else if (*currentY > 7) {
		*currentY = 7;
	}
}
