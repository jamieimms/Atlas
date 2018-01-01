#pragma once
#include "AtlasRenderer.h"

namespace Atlas
{
	class OpenGLRenderer : public AtlasRenderer
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		bool Initialise(unsigned int width, unsigned int height, void* context);
		void Resize(unsigned int width, unsigned int height);

		void beginRender();
		void endRender();


	private:

		void Destroy();
		void Compute2DMatrix(unsigned int width, unsigned int height);

		bool _useVer45;

#ifdef _WIN32

		void*		_deviceContext;
		HGLRC		_renderContext;
#endif
	};
}