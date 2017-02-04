#include "Scene.h"
#include "glew.h"
#include "FileManager.h"
#include "EntityFactory.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include <sstream>

using namespace Atlas;


Scene::Scene(TextureManager* texManager, PhysicsManager* physManager)
	: _texManager(texManager), _physicsManager(physManager)
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
	}
}

void Scene::LoadFromFile(std::string& path, unsigned int shader1, unsigned int shader2)
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
		else {
			EntityCreateInfo eci;
			ParseEntity((EntityTypeEnum)atoi(line), ln, eci);
			if (eci.shader == 0) {
				eci.shader = shader1;
			}
			else {
				eci.shader = shader2;
			}

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
//
/////
//void Scene::LoadScene(unsigned int shader1, unsigned int shader2)
//{
//	std::string texDir = FileManager::GetTextureDirectory();
//	auto dirt = _texManager->LoadTexture(texDir + "Dirt.png");
//	auto grassBoundary = _texManager->LoadTexture(texDir + "DirtGrassBorder01.png");
//	auto patchyGrass = _texManager->LoadTexture(texDir + "PatchyDirt.png");
//	auto crate = _texManager->LoadTexture(texDir + "crate.jpg");
//
//	EntityCreateInfo curInfo;
//
//	curInfo.type = ET_Origin;
//	curInfo.size = 1.0f;
//	curInfo.shader = shader1;
//	AddEntity(EntityFactory::CreateEntity(curInfo, _physicsManager));
//
//	//
//	//IRenderable* c;
//	//float x = 0;
//	//for (float y = 10.0f; y < 30.0f; y += 2.0f) {
//	//	c = new Cube(0.5f, x, y, 0.0f, shader2);
//	//	AddEntity(c);
//	//	dynamic_cast<PhysicsEntity*>(c)->SetPhysicsProperties(_physicsManager, true, 1.0f, 0.5f, 0.5f, 0.5f);
//	//	dynamic_cast<BaseEntity*>(c)->SetTexture(crate);
//	//	x += 0.2f;
//	//}
//
//	auto p = new Plane(5.0f, 0, -0.01f, 0, shader2);
//	//AddEntity(p);
//	//p->SetTexture(dirt);
//	//p->SetPhysicsProperties(_physicsManager, true, 0.0f, 5.0f, 0.1f, 5.0f);
//
//	//auto l = new Light(0.9f, 0.5f, 0.0f, 0.5f, shader1);
//	//AddEntity(l);
//	//l->SetPhysicsProperties(_physicsManager, false, 0, 0, 0, 0);
//
//	_cam.SetPosition(0, 3.0f, 5.0f);
//	_cam.SetLookAt(0, 0, 0);
//}


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

		i->Render(view, proj);
	}
}