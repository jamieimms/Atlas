#include "EntityCreateInfo.h"

using namespace Atlas;

EntityCreateInfo::EntityCreateInfo()
{
	texCount = 0;
	for (int i = 0; i < 6; i++) {
		textureID[i] = 0;
	}
}

