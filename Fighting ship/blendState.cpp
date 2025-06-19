#include "initD3D.h"

void D3D::initSpriteBlendState() {
	HRESULT hr;

	D3D11_BLEND_DESC spriteBlendStateDesc;
	ZeroMemory(&spriteBlendStateDesc, sizeof(D3D11_BLEND_DESC));
	spriteBlendStateDesc.RenderTarget[0].BlendEnable = true;
	spriteBlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	spriteBlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	spriteBlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	spriteBlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	spriteBlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	spriteBlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	spriteBlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	spriteBlendStateDesc.AlphaToCoverageEnable = false;

	hr = dev->CreateBlendState(&spriteBlendStateDesc, &spriteBlendState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create sprite blend state", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initSpriteRasterizerState() {
	HRESULT hr;

	D3D11_RASTERIZER_DESC spriteRasterizerStateDesc;
	ZeroMemory(&spriteRasterizerStateDesc, sizeof(D3D11_RASTERIZER_DESC));
	spriteRasterizerStateDesc.FillMode = D3D11_FILL_SOLID;
	spriteRasterizerStateDesc.CullMode = D3D11_CULL_NONE;

	hr = dev->CreateRasterizerState(&spriteRasterizerStateDesc, &spriteRasterizerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create sprite rasterizer state", L"Error", MB_OK);
		exit(-1);
	}

	devCon->RSSetState(spriteRasterizerState);
}