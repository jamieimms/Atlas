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
	_helpLabel = GetSpriteById(std::string("m_help"));

	_sndPipId = GetSoundByName(std::string("pip01.wav"))->soundId;
	_sndSelectId = GetSoundByName(std::string("porcSmall.wav"))->soundId;

	SetSelectedLabel(_newGameLabel, true);

	Scene::SceneLoaded();
}


void MainMenuScene::UpdateMenuSelection(bool prev)
{
	switch (_selectedMenu)
	{
	case MenuItemsEnum::NewResumeGame:
		_selectedMenu = prev ? MenuItemsEnum::Exit : MenuItemsEnum::LoadGame;
		break;
	case MenuItemsEnum::LoadGame:
		_selectedMenu = prev ? MenuItemsEnum::NewResumeGame : MenuItemsEnum::Help;
		break;
	case MenuItemsEnum::Help:
		_selectedMenu = prev ? MenuItemsEnum::LoadGame : MenuItemsEnum::Exit;
		break;
	case MenuItemsEnum::Exit:
		_selectedMenu = prev ? MenuItemsEnum::Help : MenuItemsEnum::NewResumeGame;
		break;
	default:
		break;
	}

	PlaySound(_sndPipId);

	SetSelectedLabel(_newGameLabel, _selectedMenu == MenuItemsEnum::NewResumeGame);
	SetSelectedLabel(_loadGameLabel, _selectedMenu == MenuItemsEnum::LoadGame);
	SetSelectedLabel(_helpLabel, _selectedMenu == MenuItemsEnum::Help);
	SetSelectedLabel(_exitLabel, _selectedMenu == MenuItemsEnum::Exit);
}

void MainMenuScene::SetSelectedLabel(Atlas::Sprite* label, bool isSelected)
{
	label->SetColour(isSelected ? _activeColour : _inactiveColour);
}

///
///
///
MenuItemsEnum MainMenuScene::MakeSelection()
{
	PlaySound(_sndSelectId);

	return _selectedMenu;
}

///
///
///
void MainMenuScene::UpdateScene(double& fps)
{
	GetCamera().Strafe(false);

	Scene::UpdateScene(fps);
}

