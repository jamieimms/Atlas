#pragma once
#include <Windows.h>

namespace Atlas
{
	enum AtlasRendererEnum
	{
		Unknown,
		DirectX,
		OpenGL
	};


	class AtlasRenderer
	{
	public:
		AtlasRenderer();
		virtual ~AtlasRenderer();

		virtual bool Initialise(unsigned int width, unsigned int height, HWND hWnd) = 0;

		virtual void beginRender() = 0;
		virtual void endRender() = 0;
	
		// Getters
		bool IsInitialised() { return _initialised; }
		AtlasRendererEnum GetType() { return _rendererType; }

	private:
		AtlasRendererEnum _rendererType;

		bool _initialised;

	};
}