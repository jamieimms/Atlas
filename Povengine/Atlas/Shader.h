#pragma once
#include <string>

namespace Atlas
{
	class Shader
	{
	public:
		unsigned int atlasID;
		std::string name;

		unsigned int glProgramID;

		// Common Shader variables
		int texLoc;
		int viewLoc;
		int projLoc;
		int modelLoc;
		
		// Lighting shader variables
		//int _ambientLightColour;
		int objectColour;
		int positionalLightColour;
		int positionalLightPos;
		int viewerPos;
		int ambientLightColour;

	};

}