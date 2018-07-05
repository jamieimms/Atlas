#include "MainMenuScene.h"
#include <string>

#include "Atlas/IO.h"


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
	_menuBackground = GetSpriteById("s0");
	_newGameLabel = GetTextById("m_newresume");
	_loadGameLabel = GetTextById("m_loadgame");
	_exitLabel = GetTextById("m_exit");
	_helpLabel = GetTextById("m_help");

	_helpBackground = GetSpriteById("s1");
	_helpText1 = GetTextById("m_helpText1");
	_helpText2 = GetTextById("m_helpText2");
	_helpText3 = GetTextById("m_helpText3");
	_helpText4 = GetTextById("m_helpText4");
	_helpText5 = GetTextById("m_helpText5");
	_helpText6 = GetTextById("m_helpText6");
	_helpText7 = GetTextById("m_helpText7");

	_sndPipId = GetSoundByName("pip01.wav")->soundId;
	_sndSelectId = GetSoundByName("porcSmall.wav")->soundId;

	SetSelectedLabel(_newGameLabel, true);

	LoadDynamicAssets();

	Scene::SceneLoaded();
}

/// LoadDynamicAssets
///
///	Called when the Scene is being loaded, after the file load is complete. This is the scene's opportunity to
/// load any dynamic assets before the scene finishes loading.
///
void MainMenuScene::LoadDynamicAssets()
{
	int xPos = -7, zPos = -7;
	bool isWhite = false;

	int id = 0;

	// Generate game board
	for (int i = 0; i < 8; i++) {
		isWhite = i % 2 == 0;
		for (int j = 0; j < 8; j++) {
			AddBoardTile(xPos, zPos, isWhite);
			if (!isWhite && (i <= 2 || i >= 5)) {
				AddPiece(xPos, zPos, id++, i <= 2);
			}
			isWhite = !isWhite;
			xPos += 2;
		}
		zPos += 2;
		xPos = -7;
	}
}

///
///
///
void MainMenuScene::AddBoardTile(int xPos, int zPos, bool isWhite)
{
	std::string texDir = Atlas::IO::GetTextureDirectory();
	std::string black = texDir + "black_leather_01.png";
	std::string white = texDir + "white_leather_01.png";

	Atlas::EntityCreateInfo tile;
	tile.shader = _subsystems._shaderManager->GetShaderByName("littex");
	tile.pos = glm::vec3(xPos, 0, zPos);
	tile.texCount = 1;
	tile.uniformScale = 1;
	tile.texRepeat = 1;
	tile.type = Atlas::EntityTypeEnum::ET_Plane;
	tile.textureID[0] = _subsystems._texManager->LoadTexture(isWhite ? white : black);

	this->AddEntity(_subsystems._geometry->CreateEntity(tile, _subsystems._phys));
}

///
///
///
void MainMenuScene::AddPiece(int xPos, int zPos, int numID, bool isWhite)
{
	Atlas::EntityCreateInfo piece;
	piece.shader = _subsystems._shaderManager->GetShaderByName("lighting");
	piece.pos = glm::vec3(xPos, 0.1f, zPos);
	piece.uniformScale = 0.7f;
	piece.colour = isWhite ? glm::vec3(1.0f, 1.0f, 1.0f) : glm::vec3(1.0f, 0, 0);
	piece.type = Atlas::EntityTypeEnum::ET_Mesh;
	piece.numID = numID;

	std::string mesh = "piece.obj";

	AddMesh(mesh, piece);
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


void MainMenuScene::ShowHelp()
{
	_menuBackground->SetVisibility(false);
	_newGameLabel->SetVisibility(false);
	_loadGameLabel->SetVisibility(false);
	_exitLabel->SetVisibility(false);
	_helpLabel->SetVisibility(false);

	_helpBackground->SetVisibility(true);
	_helpText1->SetVisibility(true);
	_helpText2->SetVisibility(true);
	_helpText3->SetVisibility(true);
	_helpText4->SetVisibility(true);
	_helpText5->SetVisibility(true);
	_helpText6->SetVisibility(true);
	_helpText7->SetVisibility(true);
}