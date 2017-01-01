#pragma once
#include <string>

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

		virtual bool createWindow(std::string title, unsigned int width, unsigned int height) = 0;

	protected:

		AtlasManager* _parent;
	};

}