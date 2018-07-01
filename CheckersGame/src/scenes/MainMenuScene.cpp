#include "MainMenuScene.h"
#include <string>

using namespace Atlas;
using namespace AtlasCheckers;

MainMenuScene::MainMenuScene(std::string name)
	:Scene(name), _selectionPending(false)
{
	//_activeColour = glm::vec3(1.0f, 0, 0);
	//_inactiveColour = glm::vec3(1.0f, 1.0f, 1.0f);

	_currentMenuSelection = MainMenuItemsEnum::NewResumeGame;

	_newGameLabel = nullptr;
	_loadGameLabel = nullptr;
	_exitLabel = nullptr;
}

//
//
//
void MainMenuScene::SceneLoaded()
{
	//// Populate the items we need to track
	std::string temp = "m_newresume";
	_newGameLabel = GetSpriteById(temp);
	_loadGameLabel = GetSpriteById(temp = "m_loadgame");
	_exitLabel = GetSpriteById(temp = "m_exit");
	_helpLabel = GetSpriteById(temp = "m_help");

	_sndPipId = GetSoundByName(temp = "pip01.wav")->soundId;
	_sndSelectId = GetSoundByName(temp = "porcSmall.wav")->soundId;

	SetSelectedLabel(_newGameLabel, true);

	Scene::SceneLoaded();
}

//
//
//
void MainMenuScene::UpdateMenuSelection(bool prev)
{
	if (!_isLoaded) {
		return;
	}
	switch (_currentMenuSelection)
	{
	case MainMenuItemsEnum::NewResumeGame:
		_currentMenuSelection = prev ? MainMenuItemsEnum::Exit : MainMenuItemsEnum::LoadGame;
		break;
	case MainMenuItemsEnum::LoadGame:
		_currentMenuSelection = prev ? MainMenuItemsEnum::NewResumeGame : MainMenuItemsEnum::Help;
		break;
	case MainMenuItemsEnum::Help:
		_currentMenuSelection = prev ? MainMenuItemsEnum::LoadGame : MainMenuItemsEnum::Exit;
		break;
	case MainMenuItemsEnum::Exit:
		_currentMenuSelection = prev ? MainMenuItemsEnum::Help : MainMenuItemsEnum::NewResumeGame;
		break;
	default:
		break;
	}

	PlaySound(_sndPipId);

	SetSelectedLabel(_newGameLabel, _currentMenuSelection == MainMenuItemsEnum::NewResumeGame);
	SetSelectedLabel(_loadGameLabel, _currentMenuSelection == MainMenuItemsEnum::LoadGame);
	SetSelectedLabel(_helpLabel, _currentMenuSelection == MainMenuItemsEnum::Help);
	SetSelectedLabel(_exitLabel, _currentMenuSelection == MainMenuItemsEnum::Exit);
}

//
//
//
void MainMenuScene::SetSelectedLabel(Atlas::Sprite* label, bool isSelected)
{
	label->SetColour(isSelected ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(1.0f, 1.0f, 1.0f));
}

///
///
///
void MainMenuScene::UpdateScene(double frameDelta)
{
	GetCamera().Strafe(false);

	Scene::UpdateScene(frameDelta);
}

///
///
///
void MainMenuScene::InputProcessing(Input* input)
{
	if (!_selectionPending) {
		if (input->IsKeyPressed((int)AtlasKey::Enter)) {
			PlaySound(_sndSelectId);
			_selectionPending = true;
		}

		if (input->IsKeyPressed((unsigned int)AtlasKey::Up, 200)) {
			// Change menu selection
			UpdateMenuSelection(true);
		}
		if (input->IsKeyPressed((unsigned int)AtlasKey::Down, 200)) {
			UpdateMenuSelection(false);
		}
	}
}

