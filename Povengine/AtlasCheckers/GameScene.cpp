#include "GameScene.h"

using namespace AtlasCheckers;

GameScene::GameScene(std::string name)
	:Scene(name)
{
	_turnLabel = nullptr;
	_redSelect = nullptr;
	_whiteSelect = nullptr;
}

// Overidden scene methods
void GameScene::UpdateScene(double& fps)
{
	static double lastRuntimeSec = 0;
	if (GetRuntimeSec() > (lastRuntimeSec + 1.0f)) {
		lastRuntimeSec = GetRuntimeSec();
		std::stringstream fpsstr("FPS: ");
		fpsstr << fps;
		_turnLabel->SetText(fpsstr.str());
	}
	Scene::UpdateScene(fps);
}


void GameScene::SceneLoaded()
{
	_turnLabel = (Atlas::Text*)GetSpriteById(std::string("m_playerTurn"));
	_redSelect = GetEntityById(std::string("red_overlay"));
	_whiteSelect = GetEntityById(std::string("white_overlay"));

	Scene::SceneLoaded();
}

void GameScene::ChangeTurn(bool isWhite, int redX, int redY, int whiteX, int whiteY)
{
	if (_turnLabel != nullptr) {
		_turnLabel->SetText(isWhite ? std::string("White Turn") : std::string("Red Turn"));
	}

	if (_isLoaded) {
		_redSelect->SetVisibility(!isWhite);
		_whiteSelect->SetVisibility(isWhite);

		_redSelect->SetPosition(glm::vec3(redX, 0, redY));
		_whiteSelect->SetPosition(glm::vec3(whiteX, 0, whiteY));

		_cam.SetPosition(0, 15, isWhite ? -20 : 20);
	}

	
}