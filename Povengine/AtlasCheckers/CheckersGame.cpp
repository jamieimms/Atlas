#include "CheckersGame.h"
#include "MainMenuScene.h"
#include <string>

using namespace AtlasCheckers;
using namespace Atlas;

/// <summary>
// Set the initial state for the game
/// </summary>
CheckersGame::CheckersGame()
	: _pendingScene(nullptr), _menuScene(nullptr), _gameScene(nullptr)
{

}


/// <summary>
// Set the initial state for the game
/// </summary>
bool CheckersGame::InitialiseGame()
{
	SetState(CheckersStateEnum::MainMenu);

	return true;
}

/// <summary>
// If the game wishes to change the scene being displayed, this method is called 
/// </summary>
Atlas::Scene* CheckersGame::GetPendingScene()
{
	if (_pendingScene != nullptr) {
		Scene* temp = _pendingScene;
		_pendingScene = nullptr;
		return temp;
	}

	return nullptr;
}

/// <summary>
// Process game input
/// </summary>
void CheckersGame::NewGame()
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

	_whiteSelectedSquareX = 0;
	_whiteSelectedSquareY = 0;

	_redSelectedSquareX = 7;
	_redSelectedSquareY = 7;

	SetState(CheckersStateEnum::Playing);
	_playerTurn = BoardStatesEnum::White;
	_gameScene->ChangeTurn(true, _redSelectedSquareX, _redSelectedSquareY, _whiteSelectedSquareX, _whiteSelectedSquareY);

	_gameClock.Restart();
}

/// <summary>
// Process game input
/// </summary>
void CheckersGame::InputProcessing(const Input* input)
{
	if (_gameState == CheckersStateEnum::MainMenu && _menuScene != nullptr) {
		if (_uiKeystrokeDelay.GetElapsedMs() < 120) {
			return;
		}
		_uiKeystrokeDelay.Stop();

		if (input->IsKeyPressed((int)AtlasKey::Up)) {
			// Change menu selection
			_menuScene->UpdateMenuSelection(true);
		}
		if (input->IsKeyPressed((int)AtlasKey::Down)) {
			_menuScene->UpdateMenuSelection(false);
		}

		if (input->IsKeyPressed((int)AtlasKey::Enter)) {
			// Make menu selection
			switch (_menuScene->MakeSelection()) {
				case MenuItemsEnum::NewResumeGame:
					NewGame();
					break;
				case MenuItemsEnum::Exit:
					exit(0);
					break;
			}
		}
	}
	else if (_gameState == CheckersStateEnum::Playing && _gameScene != nullptr) {
		if (input->IsKeyPressed((int)AtlasKey::Up)) {
			// cursor position up
			_gameScene->GetCamera().MoveForward();
		}
		if (input->IsKeyPressed((int)AtlasKey::Down)) {
			// Cursor position down
			_gameScene->GetCamera().Backpedal();
		}
		if (input->IsKeyPressed((int)AtlasKey::Left)) {
			// cursor position left
			_gameScene->GetCamera().Strafe(true);
		}
		if (input->IsKeyPressed((int)AtlasKey::Right)) {
			// cursor position right
			_gameScene->GetCamera().Strafe(false);
		}
		if (input->IsKeyPressed((int)AtlasKey::Enter)) {
			EndTurn();
		}
	}

	_uiKeystrokeDelay.Restart();
}

void CheckersGame::EndTurn()
{
	_playerTurn = _playerTurn == BoardStatesEnum::White ? BoardStatesEnum::Red : BoardStatesEnum::White;
	_gameScene->ChangeTurn(_playerTurn == BoardStatesEnum::White, _redSelectedSquareX, _redSelectedSquareY, _whiteSelectedSquareX, _whiteSelectedSquareY);
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
		if (_menuScene == nullptr) {
			_menuScene = new MainMenuScene("menu.as");
		}
		_pendingScene = _menuScene;
	}
	else if (_gameState == CheckersStateEnum::Playing) {
		if (_gameScene == nullptr) {
			_gameScene = new GameScene("game.as");
		}
		_pendingScene = _gameScene;
	}
}


