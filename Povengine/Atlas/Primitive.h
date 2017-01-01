#pragma once
#include "../AtlasUtil/IRenderable.h"

namespace Atlas
{
	class Primitive : public IRenderable
	{
	public:
		Primitive(float size, float x, float y, float z);

		void Render();
	private:
		unsigned int _vbaID;
		unsigned int _vbID;
	};
}