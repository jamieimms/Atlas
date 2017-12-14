#include "Scene.h"
#include "glew.h"
#include "IO.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include "Text.h"
#include "MapFileIndex.h"

using namespace Atlas;


Scene::Scene(std::string name, TextureManager* texManager, Physics* physManager, ShaderManager* shaderManager, Audio* audioManager)
	: _name(name), _texManager(texManager), _physicsManager(physManager), _shaderManager(shaderManager), _audio(audioManager)
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
	info.soundId = 999;
	if (!_audio->LoadSound(fileName, &info)) {
		return false;
	}
	_bgMusicId = info.soundId;
	return true;
}

void Scene::SetAmbientLight(float r, float g, float b)
{
	_ambientLight.r = r;
	_ambientLight.g = g;
	_ambientLight.b = b;
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

///// Loads a scene from the very basic text-based scene file
///// 
/////
//void Scene::LoadFromFile(std::string& path)
//{
//	std::string texDir = IO::GetTextureDirectory();
//	auto dirt = _texManager->LoadTexture(texDir + "Dirt.png");
//	auto grassBoundary = _texManager->LoadTexture(texDir + "DirtGrassBorder01.png");
//	auto patchyGrass = _texManager->LoadTexture(texDir + "PatchyDirt.png");
//	auto crate = _texManager->LoadTexture(texDir + "crate.jpg");
//
//	std::string sceneFile;
//	char curLine[256];
//	char line[256];
//
//	EntityTypeEnum type = ET_Unknown;
//
//	std::stringstream s(sceneFile);
//	while (!s.eof()) {
//		s.getline(curLine, 256);
//		if (curLine[0] == '\0') {
//			continue;
//		}
//		else if (line[0] == AS_SKY) {

//		}
//		else {
//			EntityCreateInfo eci;
//			ParseEntity((EntityTypeEnum)atoi(line), ln, eci);
//			if (eci.type == EntityTypeEnum::ET_Plane) {
//				eci.texCount = 1;
//			}
//
//			for (int i = 0; i < eci.texCount; i++) {
//				if (eci.textureID[i] == 0) {
//					eci.textureID[i] = dirt;
//				}
//				else if (eci.textureID[i] == 1) {
//					eci.textureID[i] = grassBoundary;
//				}
//				else if (eci.textureID[i] == 2) {
//					eci.textureID[i] = patchyGrass;
//				}
//				else if (eci.textureID[i] == 3) {
//					eci.textureID[i] = patchyGrass;
//				}
//				else if (eci.textureID[i] == 4) {
//					eci.textureID[i] = crate;
//				}
//				eci.shader->texLoc = eci.textureID[i];
//			}
//			_entities.push_back(EntityFactory::CreateEntity(eci, _physicsManager));
//		}
//	}
//}

void Scene::Start()
{
	if (_bgMusicId != 0) {
		_audio->queueSoundForNextFrame(_bgMusicId, glm::vec3(), glm::vec3());
	}

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

			int random = rand() % 10;
			double diff = random / 10.0;
			// Test finite
			EntityCreateInfo ei;
			ei.type = EntityTypeEnum::ET_Cube;
			ei.pos = glm::vec3(random - 5, 15, 0);
			ei.size = diff;
			ei.textureID[0] = 0;
			ei.shader = _shaderManager->GetShaderAtIndex(2);
			FiniteEntity* shortEntity = new FiniteEntity(10);
			_entities.push_back(EntityFactory::CreateEntity(ei, _physicsManager, shortEntity));

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