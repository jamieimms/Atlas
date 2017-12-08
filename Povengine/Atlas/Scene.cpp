#include "Scene.h"
#include "glew.h"
#include "IO.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include "Text.h"
#include "MapFileIndex.h"

using namespace Atlas;


Scene::Scene(TextureManager* texManager, Physics* physManager, ShaderManager* shaderManager, Audio* audioManager)
	: _texManager(texManager), _physicsManager(physManager), _shaderManager(shaderManager), _audio(audioManager)
{

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

void Scene::ParseEntity(EntityTypeEnum type, std::stringstream& ss, EntityCreateInfo& eci)
{
	eci.type = type;

	// All types specify a shader (for now)
	eci.shader = _shaderManager->GetShaderAtIndex(GetInt(ss));

	switch (type)
	{
	case ET_Origin:	// size
		eci.size = GetFloat(ss);
		break;
	case ET_Plane: // x, y, z, size tex
		eci.pos.x = GetFloat(ss);
		eci.pos.y = GetFloat(ss);
		eci.pos.z = GetFloat(ss);
		eci.size = GetFloat(ss);

		eci.textureID = GetInt(ss);
		break;
	case ET_Cube:
		eci.pos.x = GetFloat(ss);
		eci.pos.y = GetFloat(ss);
		eci.pos.z = GetFloat(ss);

		eci.size = GetFloat(ss);

		eci.textureID = GetInt(ss);
		break;
	case ET_Cone:
		eci.pos.x = GetFloat(ss);
		eci.pos.y = GetFloat(ss);
		eci.pos.z = GetFloat(ss);

		eci.size = GetFloat(ss);
		eci.quality = GetInt(ss);
		break;
	}
}

/// Loads a scene from the very basic text-based scene file
/// 
///
void Scene::LoadFromFile(std::string& path)
{
	std::string texDir = IO::GetTextureDirectory();
	auto dirt = _texManager->LoadTexture(texDir + "Dirt.png");
	auto grassBoundary = _texManager->LoadTexture(texDir + "DirtGrassBorder01.png");
	auto patchyGrass = _texManager->LoadTexture(texDir + "PatchyDirt.png");
	auto crate = _texManager->LoadTexture(texDir + "crate.jpg");

	std::string sceneFile;
	char curLine[256];
	char line[256];
	AtlasAPI::AtlasAPIHelper::LoadTextFile(path, sceneFile);

	EntityTypeEnum type = ET_Unknown;

	std::stringstream s(sceneFile);
	while (!s.eof()) {
		s.getline(curLine, 256);
		if (curLine[0] == '\0') {
			continue;
		}
		std::stringstream ln(curLine);

		ln.getline(line, 256, ' ');
		if (line[0] == AS_COMMENT) {
			continue;
		}
		else if (line[0] == AS_AMBIENT_LIGHT) {
			_ambientLight.r = GetFloat(ln);
			_ambientLight.g = GetFloat(ln);
			_ambientLight.b = GetFloat(ln);			
		}
		else if (line[0] == AS_BG_MUSIC) {
			char soundFile[256];
			ln.getline(soundFile, 256, ' ');
			SoundInfo info;
			_audio->LoadSound(soundFile, &info);
			_bgMusicId = info.soundId;
		}
		else {
			EntityCreateInfo eci;
			ParseEntity((EntityTypeEnum)atoi(line), ln, eci);

			if (eci.textureID == 0) {
				eci.textureID = dirt;
			}
			else if (eci.textureID == 1) {
				eci.textureID = grassBoundary;
			}
			else if (eci.textureID == 2) {
				eci.textureID = patchyGrass;
			}
			else if (eci.textureID == 3) {
				eci.textureID = patchyGrass;
			}
			else if (eci.textureID == 4) {
				eci.textureID = crate;
			}
			_entities.push_back(EntityFactory::CreateEntity(eci, _physicsManager));

		}
	}

	_cam.SetPosition(0, 3.0f, 5.0f);
	_cam.SetLookAt(0, 0, 0);

	//std::string test = "T";
	//
	//Text* t = new Text(_shaderManager->GetShaderAtIndex(0));
	//t->init(test, 60, 60);
	//
	//AddEntity(t);
}

void Scene::Test()
{
	int random = rand() % 10;
	double diff = random / 10.0;
	// Test finite
	EntityCreateInfo ei;
	ei.type = EntityTypeEnum::ET_Cube;
	ei.pos = glm::vec3(random - 5, 15, 0);
	ei.size = diff;
	ei.textureID = 0;
	ei.shader = _shaderManager->GetShaderAtIndex(2);
	FiniteEntity* shortEntity = new FiniteEntity(10);
	_entities.push_back(EntityFactory::CreateEntity(ei, _physicsManager, shortEntity));
}

void Scene::Start()
{
	//_audio->queueSoundForNextFrame(_bgMusicId, glm::vec3(), glm::vec3());

	_sceneClock.Start();

	srand(48674);
}

void Scene::Stop()
{
	_audio->UnloadSound(_bgMusicId);
}


void Scene::RemoveEntity(BaseEntity* entity)
{
	// Remove entity from the list
	delete entity;
}

///
void Scene::UnloadScene()
{
	for (auto i : _entities)
	{
		delete i;
	}

	_entities.clear();
}

void Scene::UpdateScene()
{
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
			(*it)->Update();
			it++;
		}
	}

	if (_sceneClock.GetElapsedMs() > 100) {
		Test();
		_sceneClock.Reset();
		_sceneClock.Start();
	}
}

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
			entity->Render(view, proj, _cam.GetPosition());
		}
	}
}