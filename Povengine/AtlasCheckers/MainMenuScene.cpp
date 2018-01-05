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


	_newGameLabel->SetColour(_selectedMenu == MenuItemsEnum::NewResumeGame ? _activeColour : _inactiveColour);
	_loadGameLabel->SetColour(_selectedMenu == MenuItemsEnum::LoadGame ? _activeColour : _inactiveColour);
	_exitLabel->SetColour(_selectedMenu == MenuItemsEnum::Exit ? _activeColour : _inactiveColour);
}

