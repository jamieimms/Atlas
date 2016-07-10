#pragma once

namespace Atlas
{
	enum AtlasEntityType
	{
		Graphical
	};

	class Entity
	{
	public:

		virtual ~Entity() {}

	private:
		unsigned int _id;
	};
}