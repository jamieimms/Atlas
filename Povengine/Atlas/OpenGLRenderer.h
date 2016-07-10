#pragma once
#include "AtlasRenderer.h"

namespace Atlas
{
	class OpenGLRenderer : public AtlasRenderer
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		bool Initialise(unsigned int width, unsigned int height, HWND hwnd);

		void beginRender();
		void endRender();

	private:
#ifdef WIN32

		HDC			_deviceContext;
		HGLRC		_renderContext;



#endif
	};
}