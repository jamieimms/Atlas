#include "Scene.h"
#include "glew.h"
#include "IO.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include "EntityInstance.h"

using namespace Atlas;


Scene::Scene(std::string name)
	:_name(name)
{
	_isLoaded = false;
}

bool Scene::Initialise( Subsystems subsystems)
{
	_subsystems = subsystems;
	_bgMusicId = 0;

	_identity = glm::mat4();
	_zeroVec = glm::vec3(0, 0, 0);

	_debugSceneNameTextID = -1;
	_debugFPSTextID = -1;
	_debugEntitiesTextID = -1;

	std::string dummy = "dbg1";
	std::string empty;
	_debugSceneNameTextID = AddText(dummy, empty, 15, 20, FontStyleEnum::Medium, Atlas::TextAlignmentEnum::Left, Atlas::TextAlignmentEnum::Top, true);
	_debugFPSTextID = AddText(dummy = "dbg2", empty, subsystems._renderer->GetWidth() - 70, 20, FontStyleEnum::Medium, Atlas::TextAlignmentEnum::Left, Atlas::TextAlignmentEnum::Top, true);
	_debugEntitiesTextID = AddText(dummy = "dbg3", empty, 15, 40, FontStyleEnum::Medium, Atlas::TextAlignmentEnum::Left, Atlas::TextAlignmentEnum::Top, true);

	return true;
}

///
int GetInt(std::stringstream& ss)
{
	char curLine[256];

	ss.getline(curLine, 256, ' ');
	return atoi(curLine);
}

///
float GetFloat(std::stringstream& ss)
{
	char curLine[256];

	ss.getline(curLine, 256, ' ');
	return atof(curLine);
}

///
bool Scene::AddBackgroundMusic(std::string fileName)
{
	SoundInfo info;
	if (!_subsystems._audio->LoadSound(fileName, &info)) {
		return false;
	}
	_bgMusicId = info.soundId;
	_playMusic = true;
	return true;
}

/// <summary>
/// Add a new sound object to the scene
/// </summary>
bool Scene::AddSound(std::string fileName)
{
	SoundInfo* info = new SoundInfo();
	if (!_subsystems._audio->LoadSound(fileName, info)) {
		return false;
	}

	_loadedSounds.push_back(info);

	return true;
}

///
void Scene::SetCamera(glm::vec3 pos, glm::vec3 target)
{
	_cam.SetPosition(pos.x, pos.y, pos.z);
	_cam.SetLookAt(target.x, target.y, target.z);
}

/// <summary>
/// Add an entity (holder) object to the scene
/// </summary>
void Scene::AddEntity(EntityInstance* entity)
{
	_entities.push_back(entity);
}

/// <summary>
/// Add a light object to the scene
/// </summary>
void Scene::AddLight(Light* light)
{
	_lights.push_back(light);
}

/// <summary>
/// Add a text object to the scene
/// </summary>
/// <param name="text">Text string to display</param>
/// <param name="x">x position (screen coordinates) of the text. If x is negative, text will be horizontally centred</param>
/// <param name="y">y position (screen coordinates) of the text. If y is negative, text will be vertically centred</param>
/// <param name="style">style of the text</param>
/// <returns>Returns the numeric index of the added text</returns>
int Scene::AddText(std::string& id, std::string& text, int x, int y, FontStyleEnum style, TextAlignmentEnum horizontalAlignment = TextAlignmentEnum::Left, TextAlignmentEnum verticalAlignment = TextAlignmentEnum::Top, bool visible = true)
{
	Text* newText = new Text(text, x, y, _subsystems._fonts->GetFont(style), _subsystems._shaderManager->GetShaderByName("text"), glm::vec3(1.0f, 1.0f, 1.0f), horizontalAlignment, verticalAlignment);
	newText->SetID(id);

	newText->SetVisibility(visible);

	_spriteEntities.push_back(newText);

	return _spriteEntities.size()-1;
}

///
///
void Scene::Start()
{
	if (_playMusic) {
		PlaySound(_bgMusicId);
	}

	_sceneClock.Start();

	srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

	for (auto t : _spriteEntities) {
		t->AdjustAlignment(_subsystems._renderer->GetWidth(), _subsystems._renderer->GetHeight());
	}

	_textClock.Start();
}

void Scene::PlaySound(unsigned int soundID)
{
	_subsystems._audio->queueSoundForNextFrame(soundID, _zeroVec, _zeroVec);
}


///
///
void Scene::AddMesh(std::string& meshName, EntityCreateInfo& info)
{
	Mesh* mesh = _subsystems._geometry->GetMesh(meshName);
	Material mat;
	mat.diffuseColour = info.colour;

	if (mesh != nullptr) {
		auto ei = new EntityInstance();
		ei->Initialise(info.id, mesh);
		ei->SetPosition(info.pos);
		ei->SetUniformScale(info.uniformScale);
		ei->SetMaterial(mat);

		_entities.push_back(ei);
		return;
	}

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> norms;
	std::vector<unsigned short> indices;
	std::vector<unsigned short> normalIndices;
	
	IO::ParseObjFile(IO::GetModelDirectory() + meshName, &verts, &norms, &indices, &normalIndices);
	mesh = new Mesh(meshName, &verts, &norms, &indices, &normalIndices, info.colour, _subsystems._shaderManager->GetShaderByName("lighting"));
	_subsystems._geometry->AddMesh(mesh);
	
	auto ei = new EntityInstance();
	ei->Initialise(info.id, mesh);
	ei->SetUniformScale(info.uniformScale);
	ei->SetPosition(info.pos);
	ei->SetMaterial(mat);

	_entities.push_back(ei);
}

///
///
void Scene::AddSprite(Sprite* sprite)
{
	_spriteEntities.push_back(sprite);
}

///

void Scene::Stop()
{
	_subsystems._audio->UnloadSound(_bgMusicId);
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
	SceneUnloading();

	Stop();

	for (auto i : _loadedSounds) {
		_subsystems._audio->UnloadSound(i->soundId);
		delete i;
	}
	_loadedSounds.clear();

	for (auto i : _spriteEntities)
	{
		delete i;
	}
	_spriteEntities.clear();

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
void Scene::UpdateScene(double frameDelta)
{
	static int _textClock = 0;

	if (GetRuntimeMs() - _textClock > 500 || _textClock == 0) {
		// Debug text
		std::string newText;
		Text *debugText = (Text*)_spriteEntities[_debugSceneNameTextID];
		if (debugText != nullptr) {
			newText = "Scene: " + _name;
			debugText->SetText(newText);
		}
		debugText = (Text*)_spriteEntities[_debugFPSTextID];
		if (debugText != nullptr) {
			newText = "FPS: " + std::to_string( 1.0f / frameDelta );
			debugText->SetText(newText);
		}
		debugText = (Text*)_spriteEntities[_debugEntitiesTextID];
		if (debugText != nullptr) {
			newText = "Total Entities : " + std::to_string(_entities.size()) + " - Sprites : " + std::to_string(_spriteEntities.size());
			debugText->SetText(newText);
		}
		_textClock = GetRuntimeMs();
	}

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
				tmp->RemoveFromSimulation(_subsystems._phys);
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
}

///
///
///
void Scene::DrawScene(glm::mat4 proj, glm::mat4 proj2D)
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

		if (i->IsVisible()) {
			i->PrepareEntity();
			
			if (tmp != nullptr && tmp->IsPhysicsEnabled()) {
				tmp->UpdateFromPhysics(_subsystems._phys);
			}
			i->Update();
			entity->Render(view, proj, _cam.GetPosition(), _lights);
		}
	}

	// Sprites should be rendered farthest to nearest in order to ensure correct blending
	for (auto i : _spriteEntities) {
		if (i == nullptr) {
			continue;
		}

		if (i->IsVisible()) {
			i->Render(_identity, proj2D, glm::vec3(0, 0, 0), _lights);
		}
	}
}

Text* Scene::GetTextById(const std::string& id)
{
	for (auto i : _spriteEntities) {
		if (i == nullptr) {
			continue;
		}

		if (i->GetID() == id) {
			// Ensure we don't return non-text entities
			auto textSprite = dynamic_cast<Text*>(i);
			return textSprite;
		}
	}

	return nullptr;
}

Sprite* Scene::GetSpriteById(const std::string& id)
{
	for (auto i : _spriteEntities) {
		if (i == nullptr) {
			continue;
		}

		if (i->GetID() == id) {
			return i;
		}
	}

	return nullptr;
}

EntityInstance* Scene::GetEntityById(const std::string& id)
{
	for (auto i : _entities)
	{
		if (i == nullptr) {
			continue;
		}

		if (i->GetID() == id) {
			return i;
		}
	}
}


SoundInfo* Scene::GetSoundByName(const std::string& soundName)
{

	for (auto s : _loadedSounds) {
		if (s == nullptr) {
			continue;
		}

		if (s->soundName == soundName) {
			return s;
		}
	}
	return nullptr;
}

void Scene::SceneLoaded()
{
	_isLoaded = true;

}

void Scene::SceneUnloading()
{

}

void Scene::InputProcessing(Input* input)
{

}