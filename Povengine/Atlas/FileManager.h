#pragma once
#include "BaseManager.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"

namespace Atlas
{
	class FileManager : protected BaseManager
	{ 
	public:

		static std::string GetUserDataDirectory();
		static std::string GetTextureDirectory();
		static std::string GetSoundDirectory();
		static std::string GetSceneDirectory();
	};
}