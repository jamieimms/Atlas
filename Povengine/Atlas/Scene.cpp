#include "Scene.h"
#include "glew.h"
#include "FileManager.h"
#include "EntityFactory.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include <sstream>

using namespace Atlas;


Scene::Scene(TextureManager* texManager, PhysicsManager* physManager, ShaderManager* shaderManager)
	: _texManager(texManager), _physicsManager(physManager), _shaderManager(shaderManager)
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

void ParseEntity(EntityTypeEnum type, std::stringstream& ss, EntityCreateInfo& eci)
{
	char curLine[256];

	eci.type = type;

	// All types specify a shader (for now)
	eci.shader = GetInt(ss);

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
	std::string texDir = FileManager::GetTextureDirectory();
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
		if (line[0] == '#') {
			continue;
		}
		else if (line[0] == 'a') {
			_ambientLight.r = GetFloat(ln);
			_ambientLight.g = GetFloat(ln);
			_ambientLight.b = GetFloat(ln);			
		}
		else {
			EntityCreateInfo eci;
			ParseEntity((EntityTypeEnum)atoi(line), ln, eci);
			
			eci.shader = _shaderManager->GetShaderAtIndex(eci.shader);

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
			AddEntity(EntityFactory::CreateEntity(eci, _physicsManager));
		}
	}

	_cam.SetPosition(0, 3.0f, 5.0f);
	_cam.SetLookAt(0, 0, 0);
}

///
///
///
IRenderable* Scene::AddEntity(IRenderable* entity)
{
	_entities.push_back(entity);

	return entity;
}

///
void Scene::UnloadScene()
{
	for (auto i : _entities)
	{
		delete i;
	}
}

///
void Scene::DrawScene(glm::mat4 proj)
{
	auto view = _cam.GetViewMatrix();

	for (auto i : _entities)
	{
		PhysicsEntity* tmp = dynamic_cast<PhysicsEntity*>(i);
		if (tmp != nullptr) {
			tmp->UpdateFromPhysics(_physicsManager);
		}

		i->Render(view, proj, _cam.GetPosition());
	}
}