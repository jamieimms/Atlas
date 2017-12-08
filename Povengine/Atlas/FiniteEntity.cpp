#include "FiniteEntity.h"

using namespace Atlas;

FiniteEntity::FiniteEntity(unsigned int lifeSeconds)
	:EntityHolder()
{
	_lifeSeconds = lifeSeconds;

	_lifeTimer.Start();
}

FiniteEntity::~FiniteEntity()
{

}


void FiniteEntity::Update()
{
	if (_internalEntity == nullptr) {
		return;
	}

	if (_lifeTimer.GetElapsedSec() > _lifeSeconds)
	{
		_internalEntity->Kill();
	}
	else {
		_internalEntity->Update();
	}
}