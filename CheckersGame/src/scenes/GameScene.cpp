#include "GameScene.h"
#include "../enums/Direction2D.h"

#include "Atlas/IO.h"


using namespace AtlasCheckers;
using namespace Atlas;

GameScene::GameScene(std::string name)
	: Scene(name)
{
	_turnLabel = nullptr;
	_redCapturesLabel = nullptr;
	_whiteCapturesLabel = nullptr;
	_redSelect = nullptr;
	_whiteSelect = nullptr;

	_state.NewGame();
	_stateUpdatePending = true;

	_uiTick = 0;
}

// Overidden scene methods
void GameScene::UpdateScene(double frameDelta)
{
	Scene::UpdateScene(frameDelta);

	if (_stateUpdatePending) {
			_whiteSelect->SetVisibility(_state.GetCurrentTurnPlayer() == PlayerColours::White);
			_redSelect->SetVisibility(_state.GetCurrentTurnPlayer() == PlayerColours::Red);
		if (_state.GetCurrentTurnPlayer() == PlayerColours::White) {
			_turnLabel->SetText("White's Turn");
		}
		else {
			_turnLabel->SetText("Red's Turn");
		}

		_turnCountLabel->SetText("Turns: " + std::to_string(_state.GetTurn()));
		_redCapturesLabel->SetText("Red Captures: " + std::to_string(_state.GetScore(PlayerColours::Red)));
		_whiteCapturesLabel->SetText("White Captures: " + std::to_string(_state.GetScore(PlayerColours::Red)));

		_whiteSelect->SetPosition(_state.GetCursorX(PlayerColours::White), 0.1f, _state.GetCursorY(PlayerColours::White));
		_redSelect->SetPosition(_state.GetCursorX(PlayerColours::Red), 0.1f, _state.GetCursorY(PlayerColours::Red));

		_uiTick = GetRuntimeMs();
	}
}

//
//
//
void GameScene::SceneLoaded()
{
	_turnLabel = GetTextById("m_playerTurn");
	_turnCountLabel = GetTextById("m_turnCounter");
	_redCapturesLabel = GetTextById("m_redScore");
	_whiteCapturesLabel = GetTextById("m_whiteScore");
	_redSelect = GetEntityById("red_overlay");
	_whiteSelect = GetEntityById("white_overlay");

	LoadDynamicAssets();

	_whiteCamHome = glm::vec3(5, 15, -20);
	_redCamHome = glm::vec3(5, 15, 20);

	Scene::SceneLoaded();
}

//
//
//
void GameScene::InputProcessing(Atlas::Input* input)
{
	if (input->IsKeyPressed((int)AtlasKey::Space)) {
		// Select a piece or complete move if a piece is selected
	}

	if (input->IsKeyPressed((int)AtlasKey::Enter, 1000 )) {
		_state.EndTurn();
		_stateUpdatePending = true;

		if (_state.GetCurrentTurnPlayer() == PlayerColours::White) {
			_cam.SetPosition(_whiteCamHome.x, _whiteCamHome.y, _whiteCamHome.z);
		}
		else {
			_cam.SetPosition(_redCamHome.x, _redCamHome.y, _redCamHome.z);
		}
	}

	// Check for camera movement
	if (input->IsKeyPressed((int)AtlasKey::Shift)) {
		if (input->IsKeyPressed((int)AtlasKey::Up)) {
			GetCamera().MoveForward();
		}
		if (input->IsKeyPressed((int)AtlasKey::Down)) {
			GetCamera().Backpedal();
		}
		if (input->IsKeyPressed((int)AtlasKey::Left)) {
			GetCamera().Strafe(true);
		}
		if (input->IsKeyPressed((int)AtlasKey::Right)) {
			GetCamera().Strafe(false);
		}
	}
	else {
		int cursorPause = 150;

		if (input->IsKeyPressed((int)AtlasKey::Up, cursorPause)) {
			// cursor position up
			_state.MoveCursor(Direction2D::Up);
		}
		if (input->IsKeyPressed((int)AtlasKey::Down, cursorPause)) {
			// Cursor position down
			_state.MoveCursor(Direction2D::Down);
		}
		if (input->IsKeyPressed((int)AtlasKey::Left, cursorPause)) {
			// cursor position left
			_state.MoveCursor(Direction2D::Left);
		}
		if (input->IsKeyPressed((int)AtlasKey::Right, cursorPause)) {
			// cursor position right
			_state.MoveCursor(Direction2D::Right);
		}
	}
}

/// LoadDynamicAssets
///
///	Called when the Scene is being loaded, after the file load is complete. This is the scene's opportunity to
/// load any dynamic assets before the scene finishes loading.
///
void GameScene::LoadDynamicAssets()
{
	int xPos = -7, zPos = -7;
	bool isWhite = false;

	int id = 0;

	// Generate game board
	for (int i = 0; i < BOARD_SIZE; i++) {
		isWhite = i % 2 == 0;
		for (int j = 0; j < BOARD_SIZE; j++) {
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

	_whiteSelect->SetVisibility(false);
	_redSelect->SetVisibility(false);
	_whiteSelect->SetPosition(0, 0.1, 0);
	_redSelect->SetPosition(0, 0.1, 0);
}

///
///
///
void GameScene::AddBoardTile(int xPos, int zPos, bool isWhite)
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
void GameScene::AddPiece(int xPos, int zPos, int numID, bool isWhite)
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