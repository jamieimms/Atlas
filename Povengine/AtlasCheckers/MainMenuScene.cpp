#include "MainMenuScene.h"

using namespace AtlasCheckers;

MainMenuScene::MainMenuScene(std::string name)
	:Scene(name)
{
	_activeColour = glm::vec3(1.0f, 0, 0);
	_inactiveColour = glm::vec3(1.0f, 1.0f, 1.0f);

	_selectedMenu = MenuItemsEnum::NewResumeGame;

	_newGameLabel = nullptr;
	_loadGameLabel = nullptr;
	_exitLabel = nullptr;
}

void MainMenuScene::SceneLoaded()
{
	// Populate the items we need to track
	_newGameLabel = GetSpriteById(std::string("m_newresume"));
	_loadGameLabel = GetSpriteById(std::string("m_loadgame"));
	_exitLabel = GetSpriteById(std::string("m_exit"));

	_sndPipId = GetSoundByName(std::string("pip01.wav"))->soundId;
	_sndSelectId = GetSoundByName(std::string("porcSmall.wav"))->soundId;

	SetSelectedLabel(_newGameLabel, true);
}


void MainMenuScene::UpdateMenuSelection(bool prev)
{
	switch (_selectedMenu)
	{
	case MenuItemsEnum::NewResumeGame:
		_selectedMenu = prev ? MenuItemsEnum::Exit : MenuItemsEnum::LoadGame;
		break;
	case MenuItemsEnum::LoadGame:
		_selectedMenu = prev ? MenuItemsEnum::NewResumeGame : MenuItemsEnum::Exit;
		break;
	case MenuItemsEnum::Exit:
		_selectedMenu = prev ? MenuItemsEnum::LoadGame : MenuItemsEnum::NewResumeGame;
	default:
		break;
	}

	PlaySound(_sndPipId);

	SetSelectedLabel(_newGameLabel, _selectedMenu == MenuItemsEnum::NewResumeGame);
	SetSelectedLabel(_loadGameLabel, _selectedMenu == MenuItemsEnum::LoadGame);
	SetSelectedLabel(_exitLabel, _selectedMenu == MenuItemsEnum::Exit);
}

void MainMenuScene::SetSelectedLabel(Atlas::Sprite* label, bool isSelected)
{
	label->SetColour(isSelected ? _activeColour : _inactiveColour);
}

void MainMenuScene::MakeSelection()
{
	PlaySound(_sndSelectId);

	if (_selectedMenu == MenuItemsEnum::Exit) {
		exit(0);
	}
}

void MainMenuScene::UpdateScene(double& fps)
{
	GetCamera().Strafe(false);

	Scene::UpdateScene(fps);
}

