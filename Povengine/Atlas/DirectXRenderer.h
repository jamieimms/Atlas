#pragma once
#include "AtlasRenderer.h"
#include <d3d10.h>

namespace Atlas
{
	class DirectXRenderer : public AtlasRenderer
	{
	public:
		DirectXRenderer();
		~DirectXRenderer();

		bool Initialise(unsigned int width, unsigned int height, HWND hwnd);
		void Resize(unsigned int width, unsigned int height);

		void beginRender();
		void endRender();

	private:

		void Destroy();


		D3D10_DRIVER_TYPE       _driverType;
		ID3D10Device*           _d3dDevice;
		IDXGISwapChain*         _swapChain;
		ID3D10RenderTargetView* _renderTargetView;

	};
}