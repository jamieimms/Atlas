#include "AtlasGame.h"

using namespace Atlas;

// 
//
//
AtlasGame::AtlasGame(std::string& baseDirectory)
{
	AtlasAPI::AtlasAPIHelper::SetBasePath(baseDirectory);
}