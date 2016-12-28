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
		void Resize(unsigned int width, unsigned int height);
		void SetShader(unsigned int shaderProgramID);

		void beginRender();
		void endRender();

	private:

		void Destroy();

		bool _useVer45;

#ifdef WIN32

		HDC			_deviceContext;
		HGLRC		_renderContext;



#endif
	};
}