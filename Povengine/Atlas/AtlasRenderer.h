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
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void SetShader(unsigned int programID) = 0;

		virtual void beginRender() = 0;
		virtual void endRender() = 0;
	
		// Getters
		bool IsInitialised() { return _initialised; }
		AtlasRendererEnum GetType() { return _rendererType; }

		void ToggleWireframe(bool newValue) { _wireframe = newValue; }

	protected:

		virtual void Destroy() = 0;

		unsigned int _width;
		unsigned int _height;

		AtlasRendererEnum _rendererType;

		bool _wireframe;

		bool _initialised;
	};
}