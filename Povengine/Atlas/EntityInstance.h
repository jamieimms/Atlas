#pragma once

#include "BaseEntity.h"

namespace Atlas
{
	class EntityInstance : public Transformable
	{
	public:
		EntityInstance();
		virtual ~EntityInstance() {}

		virtual void Update();

		BaseEntity* GetEntity() { return _internalEntity; }

		bool Initialise(std::string& id, BaseEntity* entity);

		bool IsInitialised() { return _initialised; }

		void SetMaterial(Material& mat);

		void PrepareEntity();

		virtual void SetVisibility(bool isVisible) { _visible = isVisible; }
		bool IsVisible() { return _visible; }

	protected:
		BaseEntity* _internalEntity;

		Material _material;


	private:
		bool _initialised;

		bool _visible;
	};
}