#pragma once
#include <string>
#include "AtlasMessageBoxEnums.h"

namespace Atlas
{
	class AtlasManager;

	class Window
	{
	public:
		Window(AtlasManager* parent);

		virtual ~Window();

		virtual bool createWindow(std::string& title, unsigned int width, unsigned int height) = 0;

		virtual void setCaptureMouse(bool enable);

		virtual bool showMessageBox(AtlasMessageTypeEnum type, std::string title, std::string message, AtlasMessageButtonsEnum buttons) = 0;

		unsigned int GetWidth() { return _width; }
		unsigned int GetHeight() { return _height; }

	protected:

		AtlasManager* _parent;
		bool _mouseCaptured;

		unsigned int _width;
		unsigned int _height;
	};

}