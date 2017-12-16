#pragma once

#include <string>
#include "tinyxml2.h"
#include "Scene.h"

#include "Input.h"
#include "Audio.h"
#include "Physics.h"
#include "TextureManager.h"

namespace Atlas
{
	class SceneParser
	{
	public:
		static Scene* ParseSceneFile(std::string& path, TextureManager* texManager, Physics* physics, ShaderManager* shaderManager, Audio* audio);

	private:
		static bool ParseElement(Scene* scene, tinyxml2::XMLElement* element, TextureManager* texManager, Physics* physics, ShaderManager* shaderManager, Audio* audio);

		static bool ParseLight(Scene* scene, tinyxml2::XMLElement* element);
		static bool ParseEntity(Scene* scene, tinyxml2::XMLElement* element, TextureManager* texManager, Physics* physics, ShaderManager* shaderManager, Audio* audio);
	};
}