#include "EntityHolder.h"

using namespace Atlas;

EntityHolder::EntityHolder()
	:_initialised(false), _internalEntity(nullptr)
{
}

bool EntityHolder::Initialise(BaseEntity* entity)
{
	if (_initialised) {
		return false;
	}

	_internalEntity = entity;
	_initialised = true;
}

void EntityHolder::Update()
{
	if (_internalEntity != nullptr) {
		_internalEntity->Update();
	}
}
