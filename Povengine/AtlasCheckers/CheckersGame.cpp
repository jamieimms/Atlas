#include "CheckersGame.h"
#include "MainMenuScene.h"
#include <string>

using namespace AtlasCheckers;
using namespace Atlas;

/// <summary>
// Set the initial state for the game
/// </summary>
bool CheckersGame::InitialiseGame()
{
	SetState(CheckersStateEnum::MainMenu);

	return true;
}

/// <summary>
// Process game input
/// </summary>
Scene* CheckersGame::GetInitialScene()
{
	_menuScene = new MainMenuScene("01.as");
	return _menuScene;
}

/// <summary>
// Process game input
/// </summary>
void CheckersGame::SetupGame()
{
	// Is a game already running? Ask if sure they want to restart

	gameBoard[7][0] = BoardStatesEnum::Empty; gameBoard[7][1] = BoardStatesEnum::Red; gameBoard[7][2] = BoardStatesEnum::Empty; gameBoard[7][3] = BoardStatesEnum::Red; gameBoard[7][4] = BoardStatesEnum::Empty; gameBoard[7][5] = BoardStatesEnum::Red; gameBoard[7][6] = BoardStatesEnum::Empty; gameBoard[7][7] = BoardStatesEnum::Red;
	gameBoard[6][0] = BoardStatesEnum::Red; gameBoard[6][1] = BoardStatesEnum::Empty; gameBoard[6][2] = BoardStatesEnum::Red; gameBoard[6][3] = BoardStatesEnum::Empty; gameBoard[6][4] = BoardStatesEnum::Red; gameBoard[6][5] = BoardStatesEnum::Empty; gameBoard[6][6] = BoardStatesEnum::Red; gameBoard[6][7] = BoardStatesEnum::Empty;
	gameBoard[5][0] = BoardStatesEnum::Empty; gameBoard[5][1] = BoardStatesEnum::Red; gameBoard[5][2] = BoardStatesEnum::Empty; gameBoard[5][3] = BoardStatesEnum::Red; gameBoard[5][4] = BoardStatesEnum::Empty; gameBoard[5][5] = BoardStatesEnum::Red; gameBoard[5][6] = BoardStatesEnum::Empty; gameBoard[5][7] = BoardStatesEnum::Red;
	
	gameBoard[4][0] = BoardStatesEnum::Empty; gameBoard[4][1] = BoardStatesEnum::Empty; gameBoard[4][2] = BoardStatesEnum::Empty; gameBoard[4][3] = BoardStatesEnum::Empty; gameBoard[4][4] = BoardStatesEnum::Empty; gameBoard[4][5] = BoardStatesEnum::Empty; gameBoard[4][6] = BoardStatesEnum::Empty; gameBoard[4][7] = BoardStatesEnum::Empty;
	gameBoard[3][0] = BoardStatesEnum::Empty; gameBoard[3][1] = BoardStatesEnum::Empty; gameBoard[3][2] = BoardStatesEnum::Empty; gameBoard[3][3] = BoardStatesEnum::Empty; gameBoard[3][4] = BoardStatesEnum::Empty; gameBoard[3][5] = BoardStatesEnum::Empty; gameBoard[3][6] = BoardStatesEnum::Empty; gameBoard[3][7] = BoardStatesEnum::Empty;
	
	gameBoard[2][0] = BoardStatesEnum::White; gameBoard[2][1] = BoardStatesEnum::Empty; gameBoard[2][2] = BoardStatesEnum::White; gameBoard[2][3] = BoardStatesEnum::Empty; gameBoard[2][4] = BoardStatesEnum::White; gameBoard[2][5] = BoardStatesEnum::Empty; gameBoard[2][6] = BoardStatesEnum::White; gameBoard[2][7] = BoardStatesEnum::Empty;
	gameBoard[1][0] = BoardStatesEnum::Empty; gameBoard[1][1] = BoardStatesEnum::White; gameBoard[1][2] = BoardStatesEnum::Empty; gameBoard[1][3] = BoardStatesEnum::White; gameBoard[1][4] = BoardStatesEnum::Empty; gameBoard[1][5] = BoardStatesEnum::White; gameBoard[1][6] = BoardStatesEnum::Empty; gameBoard[1][7] = BoardStatesEnum::White;
	gameBoard[0][0] = BoardStatesEnum::White; gameBoard[0][1] = BoardStatesEnum::Empty; gameBoard[0][2] = BoardStatesEnum::White; gameBoard[0][3] = BoardStatesEnum::Empty; gameBoard[0][4] = BoardStatesEnum::White; gameBoard[0][5] = BoardStatesEnum::Empty; gameBoard[0][6] = BoardStatesEnum::White; gameBoard[0][7] = BoardStatesEnum::Empty;

	_turnsCount = 0;
	_playerTurn = BoardStatesEnum::White;
}

/// <summary>
// Process game input
/// </summary>
void CheckersGame::InputProcessing(const Input* input)
{
	if (_gameState == CheckersStateEnum::MainMenu) {
		if (_uiKeystrokeDelay.GetElapsedMs() < 100) {
			return;
		}
		_uiKeystrokeDelay.Restart();
		if (input->IsKeyPressed((int)AtlasKey::Up)) {
			// Change menu selection
			_menuScene->UpdateMenuSelection(true);
		}
		if (input->IsKeyPressed((int)AtlasKey::Down)) {
			_menuScene->UpdateMenuSelection(false);
		}

		if (input->IsKeyPressed((int)AtlasKey::Enter)) {
			// Make menu selection
			_menuScene->MakeSelection();
		}
	}
}

/// <summary>
// Render the text string
/// </summary>
void CheckersGame::UpdateGame()
{


}

/// <summary>
// Render the text string
/// </summary>
void CheckersGame::SetState(CheckersStateEnum newState)
{
	_gameState = newState;
	if (_gameState == CheckersStateEnum::MainMenu) {
		_uiKeystrokeDelay.Restart();
	}
}


