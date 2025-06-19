#include "initD3D.h"

void D3D::initD3D(HWND hWnd) {
	HRESULT hr;

	//initalize D3D
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = 800;
	swapChainDesc.BufferDesc.Height = 600;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;

	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION,
		&swapChainDesc, &swapChain, &dev, NULL, &devCon);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create device and swap chain", L"Error", MB_OK);
		exit(-1);
	}

	ID3D11Texture2D *pSwapChain;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pSwapChain);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't get Buffer", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateRenderTargetView(pSwapChain, NULL, &renderTargetView);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create render target view", L"Error", MB_OK);
		exit(-1);
	}
	devCon->OMSetRenderTargets(1, &renderTargetView, nullptr);

	D3D11_VIEWPORT viewPortDesc;
	viewPortDesc.TopLeftX = 0.0f;
	viewPortDesc.TopLeftY = 0.0f;
	viewPortDesc.Width = 800;
	viewPortDesc.Height = 600;
	viewPortDesc.MinDepth = 0.0f;
	viewPortDesc.MaxDepth = 1.0f;

	devCon->RSSetViewports(1, &viewPortDesc);

	//Initalize depth
	D3D11_TEXTURE2D_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilViewDesc.Width = 800;
	depthStencilViewDesc.Height = 600;
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.MipLevels = 1;
	depthStencilViewDesc.ArraySize = 1;
	depthStencilViewDesc.SampleDesc.Count = 1;
	depthStencilViewDesc.SampleDesc.Quality = 0;
	depthStencilViewDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilViewDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilViewDesc.CPUAccessFlags = 0;
	depthStencilViewDesc.MiscFlags = 0;

	hr = dev->CreateTexture2D(&depthStencilViewDesc, nullptr, &depthStencilBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create depth stencil buffer", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateDepthStencilView(depthStencilBuffer, nullptr, &depthStencilView);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create depth stencil View", L"Error", MB_OK);
		exit(-1);
	}

	devCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	//Initalize Worldcb and Camera
	initWorldcb();
	initCamera();

	//Initialize Triangle
	initTriangleShaders();
	initTriangleVertexBuffer();
	initTriangleIndicesBuffer();

	//Iinitalize Texture
	initTextureShaders();
	initTextureVertexBuffer();
	initTextureIndicesBuffer();
	initTextureSampler();

	//Initialize sprite rasterizer and blend state
	//initSpriteRasterizerState();
	//initSpriteBlendState();

	//Initialize Sprite
	initSpriteShaders();
	initSpriteVertexBuffer();
	initSpriteIndicesBuffer();
	initSpriteSampler();
	//initalize billboard of sprite sheet
	spriteSheetBillBoard();

	//initialize Fighting ship
	initFightingShipShaders();
	initFightingShipVertexBuffer();
	initFightingShipIndexBuffer();
	initFightingShipSamplerState();

	//Initalize fire fighting ship
	initFireShaders();
	initFireVertexBuffer();
	initFireIndexBuffer();
	initFireSamplerState();
	//intialize fire bill board
	initFireBillBoardSheet();

	//Initialize laser
	initLaserShaders();
	initLaserVertexBuffer();
	initLaserIndexBuffer();
	initLaserSamplerState();
	//initalize laser speed
	initLaserSpeedMatrixArray();

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	dev->CreateBlendState(&blendDesc, &noBlendState);
}

void D3D::renderFrame() {
	currTime += 0.01f;
	currFireTime += 0.01f;
	devCon->ClearRenderTargetView(renderTargetView, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	UINT simpleMask = 0xffffffff;
	devCon->OMSetBlendState(noBlendState, blendFactor, simpleMask);
	
	//Render triangle
	renderTriangle();

	//Render texture
	renderTexture();

	//Render sprite
	renderSprite();

	//Render fighting ship
	renderFightingShip();

	//render Fire fighting shipx
	renderFire();

	//render laser of fighting ship
	renderLaser();

	swapChain->Present(0, 0);
}

void D3D::cleanD3D() {
	dev->Release();
	devCon->Release();
	swapChain->Release();
	renderTargetView->Release();

	depthStencilView->Release();
	depthStencilBuffer->Release();

	triangleVertexShader->Release();
	trianglePixelShader->Release();
	triangleInputLayout->Release();
	triangleVertexBuffer->Release();
	triangleIndicesBuffer->Release();

	textureVertexShader->Release();
	texturePixelShader->Release();
	textureInputLayout->Release();
	textureVertexBuffer->Release();
	textureIndicesBuffer->Release();
	textureSamplerState->Release();
	textureShaderResourceView->Release();

	worldCb->Release();

	spriteVertexShader->Release();
	spritePixelShader->Release();
	spriteInputLayout->Release();
	spriteVertexBuffer->Release();
	spriteIndicesBuffer->Release();
	spriteSamplerState->Release();
	spriteShaderResourceView->Release();

	//spriteBlendState->Release();
	//spriteRasterizerState->Release();

	fightingShipVertexShader->Release();
	fightingShipPixelShader->Release();
	fightingShipInputLayout->Release();
	fightingShipVertexBuffer->Release();
	fightingShipIndexBuffer->Release();
	fightingShipSamplerState->Release();
	fightingShipShaderResourceView->Release();

	fireVertexShader->Release();
	firePixelShader->Release();
	fireInputLayout->Release();
	fireVertexBuffer->Release();
	fireIndexBuffer->Release();
	fireSamplerState->Release();
	fireShaderResourceView->Release();

	laserVertexShader->Release();
	laserPixelShader->Release();
	laserInputLayout->Release();
	laserVertexBuffer->Release();
	laserIndexBuffer->Release();
	laserShaderResourceView->Release();
	laserSamplerState->Release();
}