#pragma once
#include <string>

namespace Atlas
{
	class AtlasManager;


	class Window
	{
	public:
		Window(AtlasManager* parent);

		virtual ~Window();

		virtual bool createWindow(std::string title, unsigned int width, unsigned int height) = 0;

		virtual void setCaptureMouse(bool enable);

	protected:

		AtlasManager* _parent;
		bool _mouseCaptured;
	};

}