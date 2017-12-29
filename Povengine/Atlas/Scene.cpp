#include "Scene.h"
#include "glew.h"
#include "IO.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include "Text.h"
#include "MapFileIndex.h"

using namespace Atlas;


Scene::Scene(std::string name, TextureManager* texManager, Physics* physManager, ShaderManager* shaderManager, Audio* audioManager, Fonts* fonts)
	: _name(name), _texManager(texManager), _physicsManager(physManager), _shaderManager(shaderManager), _audio(audioManager), _fonts(fonts)
{
	_bgMusicId = 0;
}

int GetInt(std::stringstream& ss)
{
	char curLine[256];

	ss.getline(curLine, 256, ' ');
	return atoi(curLine);
}

float GetFloat(std::stringstream& ss)
{
	char curLine[256];

	ss.getline(curLine, 256, ' ');
	return atof(curLine);
}


bool Scene::AddBackgroundMusic(std::string fileName)
{
	SoundInfo info;
	if (!_audio->LoadSound(fileName, &info)) {
		return false;
	}
	_bgMusicId = info.soundId;
	_playMusic = false;
	return true;
}


void Scene::SetCamera(glm::vec3 pos, glm::vec3 target)
{
	_cam.SetPosition(pos.x, pos.y, pos.z);
	_cam.SetLookAt(target.x, target.y, target.z);
}

void Scene::AddEntity(EntityHolder* entity)
{
	_entities.push_back(entity);
}

void Scene::AddLight(Light* light)
{
	_lights.push_back(light);
}

void Scene::Start()
{
	if (_playMusic) {
		_audio->queueSoundForNextFrame(_bgMusicId, glm::vec3(), glm::vec3());
	}

	_sceneClock.Start();

	_titleText = "Atlas Engine Test 2017.12. ";
	Text* text = new Text(_titleText, 20, 40, _fonts->GetFont(0), _shaderManager->GetShaderByName("text"));

	_textItems.push_back(text);

	srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

	_textClock.Start();

	std::string test = "Total entities: ";
	text = new Text(test, 20, 60, _fonts->GetFont(0), _shaderManager->GetShaderByName("text"));
	_textItems.push_back(text);
}

void Scene::AddMesh(std::string& meshName, EntityCreateInfo& info)
{
	std::vector<glm::vec3>* verts = new std::vector<glm::vec3>();
	std::vector<glm::vec3>* norms = new std::vector<glm::vec3>();
	std::vector<unsigned short>* indices = new std::vector<unsigned short>();
	std::vector<unsigned short>* normalIndices = new std::vector<unsigned short>();

	IO::ParseObjFile(IO::GetModelDirectory() + meshName, verts, norms, indices, normalIndices);
	auto mesh = new Mesh(verts, norms, indices, normalIndices, info.pos, info.colour, _shaderManager->GetShaderByName("lighting"));
	mesh->SetUniformScale(info.uniformScale);
	auto eh = new EntityHolder();
	eh->Initialise(mesh);
	_entities.push_back(eh);
	delete normalIndices;
	delete indices;
	delete norms;
	delete verts;
}

///
//
//
void Scene::Stop()
{
	_audio->UnloadSound(_bgMusicId);
}

///
//
//
void Scene::RemoveEntity(BaseEntity* entity)
{
	// Remove entity from the list
	delete entity;
}

///
//
//
void Scene::UnloadScene()
{
	for (auto i : _textItems)
	{
		delete i;
	}

	_textItems.clear();

	for (auto i : _entities)
	{
		delete i;
	}

	_entities.clear();

	for (auto i : _lights)
	{
		delete i;
	}

	_lights.clear();
}

///
///
//
void Scene::UpdateScene(double& fps)
{
	//static std::string tex = IO::GetTextureDirectory() + "crate.jpg";
	//static unsigned int texID = _texManager->LoadTexture(tex);

	auto it = _entities.begin();
	while (it != _entities.end()) {
		if (*it == nullptr) {
			it++;
			continue;
		}
		auto entity = (*it)->GetEntity();

		if (entity->IsDead()) {
			auto holder = (*it);
			it = _entities.erase(it);

			PhysicsEntity* tmp = dynamic_cast<PhysicsEntity*>(entity);
			if (tmp != nullptr) {
				tmp->RemoveFromSimulation(_physicsManager);
			}

			delete entity;
			delete holder;
		}
		else {
			if((*it)->GetEntity()->GetType() == EntityTypeEnum::ET_Skybox) {
				auto camPos = _cam.GetPosition();
				(*it)->GetEntity()->SetPosition(camPos.x, camPos.y, camPos.z);
			}
			(*it)->Update();
			it++;
		}
	}

	//if (_sceneClock.GetElapsedMs() > 500) {
	//	int random = rand() % 10;
	//	double diff = (rand() % 10) / 10.0;
	//	
	//	// Test finite
	//	EntityCreateInfo ei;
	//	ei.type = EntityTypeEnum::ET_Cube;
	//	ei.pos = glm::vec3(random - 5, 15, 0);
	//	ei.uniformScale = diff;
	//	ei.textureID[0] = texID;
	//	ei.shader = _shaderManager->GetShaderByName("littex");
	//	//FiniteEntity* shortEntity = new FiniteEntity(10);
	//	//_entities.push_back(EntityFactory::CreateEntity(ei, _physicsManager, shortEntity));

	//	random = rand() % 10;
	//	diff = (rand() % 10) / 10.0;
	//	ei.uniformScale = diff;
	//	ei.pos = glm::vec3(random - 5, 15, 5);
	//	FiniteEntity* shortEntity = new FiniteEntity(10);
	//	_entities.push_back(EntityFactory::CreateEntity(ei, _physicsManager, shortEntity));

	//	random = rand() % 10;
	//	diff = (rand() % 10) / 10.0;
	//	ei.uniformScale = diff;
	//	ei.pos = glm::vec3(random - 5, 15, -5);
	//	shortEntity = new FiniteEntity(10);
	//	_entities.push_back(EntityFactory::CreateEntity(ei, _physicsManager, shortEntity));

	//	_sceneClock.Reset();
	//	_sceneClock.Start();
	//}

	if (_textClock.GetElapsedMs() > 100) {
		std::string info = "Scene: " + _name + ", FPS: " + std::to_string(fps);
		_textItems[0]->SetText(_titleText + info);

		std::string entityInfo = "Total entities: " + std::to_string(_entities.size());
		_textItems[1]->SetText(entityInfo);

		_textClock.Reset();
		_textClock.Start();
	}
}

///
///
///
void Scene::DrawScene(glm::mat4 proj)
{
	auto view = _cam.GetViewMatrix();

	for (auto i : _entities)
	{
		if (i == nullptr) {
			continue;
		}
		if (!i->IsInitialised()) {
			continue;
		}
		auto entity = i->GetEntity();

		PhysicsEntity* tmp = dynamic_cast<PhysicsEntity*>(entity);
		if (tmp != nullptr) {
			tmp->UpdateFromPhysics(_physicsManager);
		}

		if (entity->IsVisible()) {
			entity->Render(view, proj, _cam.GetPosition(), _lights);
		}
	}

	for (auto i : _textItems) {
		if (i == nullptr) {
			continue;
		}

		Text* text = i;
		text->Render(view, proj, _cam.GetPosition(), _lights);
	}
}