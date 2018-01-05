#pragma once
#include <string>

namespace Atlas
{
	class AtlasObject
	{
	public:

		std::string GetID() { return _id; }
		void SetID(std::string& id) { _id = id; }

	protected:


		std::string _id;
	};
}