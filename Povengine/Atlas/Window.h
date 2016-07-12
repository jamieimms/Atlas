#pragma once
#include "..\AtlasUtil\AtlasString.h"

namespace Atlas
{
	class AtlasManager;


	class Window
	{
	public:
		Window(AtlasManager* parent)
			: _parent(parent)
		{}

		virtual ~Window() {}

		virtual bool createWindow(AtlasUtil::AtlasString title, unsigned int width, unsigned int height) = 0;

	private:

		AtlasManager* _parent;
	};

}