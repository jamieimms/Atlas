#include "GameScene.h"

using namespace AtlasCheckers;

GameScene::GameScene(std::string name)
	:Scene(name)
{

}

// Overidden scene methods
void GameScene::UpdateScene(double& fps)
{
	Scene::UpdateScene(fps);
}


void GameScene::SceneLoaded()
{

}