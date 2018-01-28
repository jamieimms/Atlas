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
		static Scene* ParseSceneFile(Scene* emptyScene, std::string& path, Subsystems& subsystems);


	private:
		/// Atlas Scene format elements
		static const char* SP_ASROOT;// "atlasscene";

		/// Atlas top-level scene elements
		static const char* SP_EL_BGMUSIC;
		static const char* SP_EL_ENTITIES;
		static const char* SP_EL_CAM;
		static const char* SP_EL_UI;
		static const char* SP_EL_LIGHTS;
		static const char* SP_EL_SNDS;

		/// Atlas scene child elements
		static const char* SP_EL_TEXT;
		static const char* SP_EL_SPRITE;
		static const char* SP_EL_SHADER;
		static const char* SP_EL_SND;

		/// Atlas scene attributes
		static const char* SP_ATTR_ID;
		static const char* SP_ATTR_POS;
		static const char* SP_ATTR_COLOUR;
		static const char* SP_ATTR_NAME;
		static const char* SP_ATTR_VAL;
		static const char* SP_ATTR_X;
		static const char* SP_ATTR_Y;
		static const char* SP_ATTR_Z;
		static const char* SP_ATTR_RPT;

		// 2D Sprite (including text) attributes
		static const char* SP_ATTR_CONTENT;
		static const char* SP_ATTR_STYLE;
		static const char* SP_ATTR_HALIGN;
		static const char* SP_ATTR_VALIGN; 
		static const char* SP_ATTR_WIDTH;
		static const char* SP_ATTR_HEIGHT;

		static bool ParseElement(Scene* scene, tinyxml2::XMLElement* element, Subsystems& subsystems);

		static bool ParseLight(Scene* scene, tinyxml2::XMLElement* element);
		static bool ParseEntity(Scene* scene, tinyxml2::XMLElement* element, Subsystems& subsystems);

		static bool ParseUI(Scene* scene, tinyxml2::XMLElement* element, Subsystems& subsystems);

		static FontStyleEnum ParseTextStyle(std::string& style);
		static TextAlignmentEnum ParseAlignment(std::string& alignment);
		
			
	};
}