#include "SceneParser.h"
#include "IO.h"

using namespace Atlas;
using namespace tinyxml2;

//
//
Scene* SceneParser::ParseSceneFile(std::string& path, TextureManager* texManager, Physics* physics, ShaderManager* shaderManager, Audio* audio)
{
	XMLError returnCode;

	XMLDocument doc;
	returnCode = doc.LoadFile(path.c_str());

	if (returnCode != XMLError::XML_SUCCESS) {
		return nullptr;
	}

	auto root = doc.FirstChildElement("atlasscene");

	if (root == nullptr) {
		// Doesn't seem to be an atlas scene file. Bail.
		return nullptr;
	}

	Scene* newScene = new Scene(root->FirstAttribute()->Value(), texManager, physics, shaderManager, audio);
	
	auto sceneElement = root->FirstChildElement();

	while (sceneElement != nullptr) {
		if (!ParseElement(newScene, sceneElement, texManager, physics, shaderManager, audio)) {
			// There was an error parsing the scene file. Bail.
			return nullptr;
		}
		sceneElement = sceneElement->NextSiblingElement();
	}

	return newScene;
}

//
//
bool SceneParser::ParseElement(Scene* scene, XMLElement* element, TextureManager* texManager, Physics* physics, ShaderManager* shaderManager, Audio* audio)
{
	// Determine the element and parse it accordingly

	if (strcmp(element->Name(),"bgmusic") == 0) {
		auto sound = element->FirstChildElement("sound");
		scene->AddBackgroundMusic(sound->FirstAttribute()->Value());
	}
	else if (strcmp(element->Name(), "entities") == 0) {
		auto child = element->FirstChildElement();
		while (child != nullptr) {
			ParseEntity(scene, child, texManager, physics, shaderManager, audio);
			child = child->NextSiblingElement();
		}
	}
	else if (strcmp(element->Name(), "camera") == 0) {
		auto child = element->FirstChildElement("position");
		glm::vec3 pos(child->FloatAttribute("x"), child->FloatAttribute("y"), child->FloatAttribute("z"));

		child = element->FirstChildElement("target");
		glm::vec3 target(child->FloatAttribute("x"), child->FloatAttribute("y"), child->FloatAttribute("z"));

		scene->SetCamera(pos, target);
	}
	else if (strcmp(element->Name(), "sky") == 0) {
		ParseEntity(scene, element, texManager, physics, shaderManager, audio);
	}
	else if (strcmp(element->Name(), "lights") == 0) {
		auto child = element->FirstChildElement();
		while (child != nullptr) {
			ParseLight(scene, child);
			child = child->NextSiblingElement();
		}
	}

	return true;
}

//
//
bool SceneParser::ParseLight(Scene* scene, XMLElement* element)
{
	if (strcmp(element->Name(), "ambient") == 0) {
		auto child = element->FirstChildElement("colour");
		scene->AddLight(new Light(LightTypeEnum::LT_Ambient, child->FloatAttribute("r", 1.0f), child->FloatAttribute("g", 1.0f), child->FloatAttribute("b", 1.0f)));
	}
	else if (strcmp(element->Name(), "point") == 0) {
		auto posElement = element->FirstChildElement("position");
		auto colourElement = element->FirstChildElement("colour");

		Light* light = new Light(LightTypeEnum::LT_Point, colourElement->FloatAttribute("r", 1.0f), colourElement->FloatAttribute("g", 1.0f), colourElement->FloatAttribute("b", 1.0f),
			posElement->FloatAttribute("x", 0.0f), posElement->FloatAttribute("y", 0.0f), posElement->FloatAttribute("z", 0.0f));
		scene->AddLight(light);
	}
	else {
		return false;
	}
	return true;
}

//
//
bool SceneParser::ParseEntity(Scene* scene, XMLElement* element, TextureManager* texManager, Physics* physics, ShaderManager* shaderManager, Audio* audio)
{
	EntityCreateInfo entityInfo;

	// Get the type
	if (strcmp(element->Name(), "origin") == 0) {
		entityInfo.type = EntityTypeEnum::ET_Origin;
	}
	else if (strcmp(element->Name(), "plane") == 0) {
		entityInfo.type = EntityTypeEnum::ET_Plane;
	}
	else if (strcmp(element->Name(), "cone") == 0) {
		entityInfo.type = EntityTypeEnum::ET_Cone;
	}
	else if (strcmp(element->Name(), "sky") == 0) {
		entityInfo.type = EntityTypeEnum::ET_Skybox;

		std::string name = element->FirstAttribute()->Value();
		std::string texDir = IO::GetTextureDirectory();
		auto skyTex = texManager->LoadTexture(texDir + name + "\\bk.jpg");
		entityInfo.texCount = 6;
		entityInfo.textureID[0] = skyTex;
		skyTex = texManager->LoadTexture(texDir + name + "\\ft.jpg");
		entityInfo.textureID[1] = skyTex;
		skyTex = texManager->LoadTexture(texDir + name + "\\lt.jpg");
		entityInfo.textureID[2] = skyTex;
		skyTex = texManager->LoadTexture(texDir + name + "\\rt.jpg");
		entityInfo.textureID[3] = skyTex;
		skyTex = texManager->LoadTexture(texDir + name + "\\up.jpg");
		entityInfo.textureID[4] = skyTex;
		skyTex = texManager->LoadTexture(texDir + name + "\\dn.jpg");
		entityInfo.textureID[5] = skyTex;
		entityInfo.shader = shaderManager->GetShaderByName("texture");
		entityInfo.uniformScale = 55;
		entityInfo.pos = glm::vec3(0, 0, 0);
		scene->AddEntity(EntityFactory::CreateEntity(entityInfo, physics));
		return true;
	}
	else if (strcmp(element->Name(), "cube") == 0) {
		entityInfo.type = EntityTypeEnum::ET_Cube;
	}
	else {
		return false;
	}

	auto child = element->FirstChildElement("shader");
	if (child == nullptr) {
		entityInfo.shader = shaderManager->GetShaderByName("colour");
	}
	else {
		entityInfo.shader = shaderManager->GetShaderByName(child->Attribute("name"));
	}

	child = element->FirstChildElement("position");
	if (child == nullptr) {
		entityInfo.pos = glm::vec3(0, 0, 0);
	}
	else {
		entityInfo.pos = glm::vec3(child->FloatAttribute("x"), child->FloatAttribute("y"), child->FloatAttribute("z"));
	}

	child = element->FirstChildElement("uniformscale");
	if (child == nullptr) {
		entityInfo.uniformScale = 1.0f;
	}
	else {
		entityInfo.uniformScale = child->FloatAttribute("value");
	}

	// Textures
	child = element->FirstChildElement("texture");
	if (child == nullptr) {
		entityInfo.texCount = 0;
	}
	else {
		std::string texDir = IO::GetTextureDirectory();
		auto tex = texManager->LoadTexture(texDir + child->Attribute("name"));
		entityInfo.textureID[entityInfo.texCount++] = tex;
	}

	scene->AddEntity(EntityFactory::CreateEntity(entityInfo, physics));

	//			auto sky1 = _texManager->LoadTexture(texDir + "muddysky\\bk.jpg");		//bk ft dn lt rt up
	//			//auto sky2 = _texManager->LoadTexture(texDir + "muddysky\\ft.jpg");	//bk ft dn lt rt up
	//			//auto sky3 = _texManager->LoadTexture(texDir + "muddysky\\dn.jpg");	//bk ft dn lt rt up
	//			//auto sky4 = _texManager->LoadTexture(texDir + "muddysky\\lt.jpg");	//bk ft dn lt rt up
	//			//auto sky5 = _texManager->LoadTexture(texDir + "muddysky\\rt.jpg");	//bk ft dn lt rt up
	//			//auto sky6 = _texManager->LoadTexture(texDir + "muddysky\\up.jpg");	//bk ft dn lt rt up

	return true;
}