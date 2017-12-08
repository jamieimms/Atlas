#include "IO.h"

#include <sstream>

using namespace Atlas;

/// <summary>
/// Get the directory where all user data should be stored
/// </summary>
/// <returns>base path for user data (e.g. saves etc.)</returns>
std::string IO::GetUserDataDirectory()
{	
	return AtlasAPI::AtlasAPIHelper::GetUserDataPath() + AtlasAPI::AtlasAPIHelper::GetPathSeparator() + "Atlas";
}

/// <summary>
/// Get the directory where all textures should be stored
/// </summary>
/// <returns>base path for textures</returns>
std::string IO::GetTextureDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Textures" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}

/// <summary>
/// Get the directory where all sounds should be stored
/// </summary>
/// <returns>base path for sounds</returns>
std::string IO::GetSoundDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Sound" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}

/// <summary>
/// Get the directory where all scenes should be stored
/// </summary>
/// <returns>base path for scenes</returns>
std::string IO::GetSceneDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Scenes" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}

/// <summary>
/// Get the directory where all shader files should be stored
/// </summary>
/// <returns>base path for shaders</returns>
std::string IO::GetShaderDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Shaders" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}
