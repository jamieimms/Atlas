#include "TerraFormaGame.h"
#include "TestScene.h"

using namespace Atlas;
using namespace TerraForma;

TerraFormaGame::TerraFormaGame(std::string& basePath)
	:AtlasGame(basePath), _scene(nullptr)
{

}

TerraFormaGame::~TerraFormaGame()
{
	//delete _scene;
}

bool TerraFormaGame::InitialiseGame()
{
	return true;
}

Atlas::Scene* TerraFormaGame::GetPendingScene()
{
	return _scene == nullptr ? _scene = new TestScene() : nullptr;
}

void TerraFormaGame::InputProcessing(Atlas::Input* input)
{
	if (_scene != nullptr) {
		_scene->InputProcessing(input);
	}


}

void TerraFormaGame::UpdateGame(double frameDelta)
{

}