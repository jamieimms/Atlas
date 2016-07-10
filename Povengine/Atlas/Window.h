#pragma once
#include "..\AtlasUtil\AtlasString.h"

namespace Atlas
{
	class Window
	{
	public:
		Window() {}
		virtual ~Window() {}

		virtual bool createWindow(AtlasUtil::AtlasString title, unsigned int width, unsigned int height) = 0;
	};

}