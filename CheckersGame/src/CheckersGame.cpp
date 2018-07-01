#include <string>
#include "CheckersGame.h"
#include "scenes/scenes.h"
//#include "CheckersConstants.h"

using namespace AtlasCheckers;
using namespace Atlas;

/// <summary>
// Set the initial state for the game
/// </summary>
CheckersGame::CheckersGame(std::string& basePath)
	: AtlasGame(basePath), _pendingScene(nullptr), _mainMenuScene(nullptr), _gameScene(nullptr)
{
	_pendingScene = _mainMenuScene = new MainMenuScene("menu.as");
}


/// <summary>
// Set the initial state for the game
/// </summary>
bool CheckersGame::InitialiseGame()
{
	//SetState(PlayStateEnum::MainMenu);

	_gameTick.Start();
	_lastStateCheck = 0;

	return true;
}

/// <summary>
// If the game wishes to change the scene being displayed, this method is called 
/// </summary>
Atlas::Scene* CheckersGame::GetPendingScene()
{
	if (_pendingScene != nullptr) {
		Scene* temp = _pendingScene;
		_currentScene = temp;
		_pendingScene = nullptr;
		return temp;
	}

	return nullptr;
}


/// <summary>
// Process game input
/// </summary>
void CheckersGame::InputProcessing(Input* input)
{
	if (_currentScene != nullptr) {
		_currentScene->InputProcessing(input);
	}

	if (input->IsKeyPressed((unsigned int)AtlasKey::Escape, 1000)) {
		if (_pendingScene == nullptr && _currentScene == _mainMenuScene) {
			_pendingScene = _gameScene;
		}
		else {
			_pendingScene = _mainMenuScene;
		}
	
	}


}

/// <summary>
// Render the text string
/// </summary>
void CheckersGame::UpdateGame(double frameDelta)
{
	if (_gameTick.GetElapsedMs() >= (_lastStateCheck + 200)) {
		if (_currentScene == _mainMenuScene) {
			if (_mainMenuScene->IsSelectionPending()) {
				switch (_mainMenuScene->GetSelection()) {
				case MainMenuItemsEnum::NewResumeGame:
					if (_gameScene == nullptr) {
						_gameScene = new GameScene("game.as");
					}
					_pendingScene = _gameScene;
					break;
				case MainMenuItemsEnum::Exit:
					exit(0);
					break;
				}
			}
		}
		_lastStateCheck = _gameTick.GetElapsedMs();
	}

}


