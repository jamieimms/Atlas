#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class EntityHolder
	{
	public:
		EntityHolder();
		virtual ~EntityHolder() {}

		virtual void Update();

		BaseEntity* GetEntity() { return _internalEntity; }
		
		bool Initialise(BaseEntity* entity);

		bool IsInitialised() { return _initialised; }

	protected:
		BaseEntity* _internalEntity;

	private:
		bool _initialised;
	};

}