#include "TestScene.h"
#include "../Atlas/IO.h"

using namespace Atlas;
using namespace TerraForma;
using namespace AtlasUtil;

TestScene::TestScene()
	: Scene("main.as")
{

}

void TestScene::SceneLoaded()
{
	Scene::SceneLoaded();

	std::string texDir = IO::GetTextureDirectory();
	_crateTex = _subsystems._texManager->LoadTexture(texDir + "crate.jpg");
}

void TestScene::UpdateScene(double frameDelta)
{
	Scene::UpdateScene(frameDelta);

	if (GetRuntimeMs() - _lastSpawn > 1000) {
		int random = rand() % 10;
		int random2 = rand() % 10;
		double diff = (rand() % 10) / 10.0;

		// Test finite
		EntityCreateInfo ei;
		ei.type = EntityTypeEnum::ET_Cube;
		ei.pos = glm::vec3(random - 5, 5, random2 - 5);
		ei.uniformScale = 1;
		ei.textureID[0] = _crateTex;
		ei.shader = _subsystems._shaderManager->GetShaderByName("littex");
		ei.lifetimeMs = 10000;
		AddEntity(_subsystems._geometry->CreateEntity(ei, _subsystems._phys));


		//random = rand() % 10;
		//diff = (rand() % 10) / 10.0;
		//ei.uniformScale = diff;
		//ei.pos = glm::vec3(random - 5, 15, 5);
		////FiniteEntity* shortEntity = new FiniteEntity(10);
		//AddEntity(_subsystems._geometry->CreateEntity(ei, _subsystems._phys));

		//random = rand() % 10;
		//diff = (rand() % 10) / 10.0;
		//ei.uniformScale = diff;
		//ei.pos = glm::vec3(random - 5, 15, -5);
		////shortEntity = new FiniteEntity(10);
		//AddEntity(_subsystems._geometry->CreateEntity(ei, _subsystems._phys));

		_lastSpawn = GetRuntimeMs();
	}

	//if (_textClock.GetElapsedMs() > 100) {
	//	std::string info = "Scene: " + _name + ", FPS: " + std::to_string(fps);
	//	_textItems[0]->SetText(_titleText + info);

	//	std::string entityInfo = "Total entities: " + std::to_string(_entities.size());
	//	_textItems[1]->SetText(entityInfo);

	//	_textClock.Restart();
	//}
}
