#pragma once
#include <string>

namespace Atlas
{
	class Window
	{
	public:
		Window() {}
		virtual ~Window() {}

		virtual bool createWindow(std::wstring title) = 0;
	};

}