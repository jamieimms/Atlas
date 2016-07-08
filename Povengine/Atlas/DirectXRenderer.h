#pragma once
#include "Win32Renderer.h"
#include <d3d10.h>

namespace Atlas
{
	class DirectXRenderer : public Win32Renderer
	{
	public:
		DirectXRenderer();
		~DirectXRenderer();

		bool Initialise(unsigned int width, unsigned int height, HWND hwnd);

		void beginRender();
		void endRender();

	private:

		D3D10_DRIVER_TYPE       _driverType;
		ID3D10Device*           _d3dDevice;
		IDXGISwapChain*         _swapChain;
		ID3D10RenderTargetView* _renderTargetView;

	};
}