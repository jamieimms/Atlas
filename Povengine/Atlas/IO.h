#pragma once
#include "BaseManager.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"

#include <vector>

#include "glm.hpp"

namespace Atlas
{
	class IO : protected BaseManager
	{ 
	public:

		static std::string GetUserDataDirectory();
		static std::string GetTextureDirectory();
		static std::string GetSoundDirectory();
		static std::string GetSceneDirectory();
		static std::string GetShaderDirectory();
		static std::string GetModelDirectory();

		static bool ParseObjFile(std::string& filePath, std::vector<glm::vec3>* outVertices, std::vector<glm::vec3>* outNormals, std::vector<unsigned short>* vertexIndices, std::vector<unsigned short>* normalIndices);
	};
}