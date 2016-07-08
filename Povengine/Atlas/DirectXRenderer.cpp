#include "DirectXRenderer.h"

using namespace Atlas;

DirectXRenderer::DirectXRenderer()
	: _driverType(D3D10_DRIVER_TYPE_NULL), _d3dDevice(nullptr), _swapChain(nullptr), _renderTargetView(nullptr)
{

}

DirectXRenderer::~DirectXRenderer()
{
	if (_d3dDevice) _d3dDevice->ClearState();

	if (_renderTargetView) _renderTargetView->Release();
	if (_swapChain) _swapChain->Release();
	if (_d3dDevice) _d3dDevice->Release();
}

bool DirectXRenderer::Initialise(unsigned int width, unsigned int height, HWND hwnd)
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
//#ifdef _DEBUG
//	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
//#endif

	D3D10_DRIVER_TYPE driverTypes[] =
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		_driverType = driverTypes[driverTypeIndex];
		hr = D3D10CreateDeviceAndSwapChain(NULL, _driverType, NULL, createDeviceFlags,
			D3D10_SDK_VERSION, &sd, &_swapChain, &_d3dDevice);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return false;

	// Create a render target view
	ID3D10Texture2D* pBackBuffer;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return false;

	hr = _d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &_renderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return false;

	_d3dDevice->OMSetRenderTargets(1, &_renderTargetView, NULL);

	// Setup the viewport
	D3D10_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_d3dDevice->RSSetViewports(1, &vp);

	return true;
}


void DirectXRenderer::beginRender()
{
	// Just clear the backbuffer
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
	_d3dDevice->ClearRenderTargetView(_renderTargetView, ClearColor);
	_swapChain->Present(0, 0);

}

void DirectXRenderer::endRender()
{

}