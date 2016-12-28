#pragma once
#include "AtlasRenderer.h"
#include <d3d11.h>

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

		ID3D11Device* GetDevice() { return _d3dDevice; }
		ID3D11DeviceContext* GetContext() { return _immediateContext; }

	private:

		void Destroy();

		D3D_FEATURE_LEVEL		_featureLevel;


		D3D_DRIVER_TYPE       _driverType;
		ID3D11Device*           _d3dDevice;
		IDXGISwapChain*         _swapChain;
		ID3D11RenderTargetView* _renderTargetView;
		ID3D11DeviceContext*	_immediateContext;


	};
}