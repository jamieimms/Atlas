#include "FileManager.h"

#include <sstream>

using namespace Atlas;

/// <summary>
/// Get the directory where all user data should be stored
/// </summary>
/// <returns>a platform specific window based on the Window class</returns>
std::string FileManager::GetUserDataDirectory()
{	
	return AtlasAPI::AtlasAPIHelper::GetUserDataPath() + AtlasAPI::AtlasAPIHelper::GetPathSeparator() + "Atlas";
}

/// <summary>
/// Get the directory where all textures should be stored
/// </summary>
/// <returns>a platform specific window based on the Window class</returns>
std::string FileManager::GetTextureDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Textures" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}

/// <summary>
/// Get the directory where all sounds should be stored
/// </summary>
/// <returns>a platform specific window based on the Window class</returns>
std::string FileManager::GetSoundDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Sound" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}