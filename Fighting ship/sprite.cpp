#include "initD3D.h"

void D3D::initSpriteShaders() {
	HRESULT hr;

	//Sprite Vertex Shader
	ID3D10Blob* pSpriteVertexShader = nullptr;
	hr = D3DX10CompileFromFile(L"SpriteVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pSpriteVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile spirte vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateVertexShader(pSpriteVertexShader->GetBufferPointer(), pSpriteVertexShader->GetBufferSize(),
		0, &spriteVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	//Sprite pixel shader
	ID3D10Blob* pSpritePixelShader = nullptr;
	hr = D3DX10CompileFromFile(L"SpritePixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pSpritePixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile spirte pixel shader", L"Erro", MB_OK);
		exit(-1);
	}

	hr = dev->CreatePixelShader(pSpritePixelShader->GetBufferPointer(), pSpritePixelShader->GetBufferSize(),
		0, &spritePixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create sprite pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	//Sprite input layout
	D3D11_INPUT_ELEMENT_DESC spriteInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(spriteInputLayoutDesc);

	hr = dev->CreateInputLayout(spriteInputLayoutDesc, size, pSpriteVertexShader->GetBufferPointer(),
		pSpriteVertexShader->GetBufferSize(), &spriteInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create sprite input layout", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initSpriteVertexBuffer() {
	HRESULT hr;

	//Sprite vertex Buffer
	spriteVertices[0].position = XMFLOAT3(-1.3f, -0.4f, -0.5f);
	spriteVertices[0].texCoord = XMFLOAT2(0.01f, 0.7f);
	spriteVertices[1].position = XMFLOAT3(-0.7f, -0.4f, -0.5f);
	spriteVertices[1].texCoord = XMFLOAT2(0.14f, 0.7f);
	spriteVertices[2].position = XMFLOAT3(-1.3f, -1.0f, -0.5f);
	spriteVertices[2].texCoord = XMFLOAT2(0.01f, 1.0f);
	spriteVertices[3].position = XMFLOAT3(-0.7f, -1.0f, -0.5f);
	spriteVertices[3].texCoord = XMFLOAT2(0.14f, 1.0f);

	D3D11_BUFFER_DESC spriteVertexBufferDesc;
	ZeroMemory(&spriteVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	spriteVertexBufferDesc.ByteWidth = 4 * sizeof(sprite);
	spriteVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	spriteVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	spriteVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA spriteVertexBufferSubData;
	ZeroMemory(&spriteVertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	spriteVertexBufferSubData.pSysMem = spriteVertices;

	hr = dev->CreateBuffer(&spriteVertexBufferDesc, &spriteVertexBufferSubData, &spriteVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create sprite vertex buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initSpriteIndicesBuffer() {
	HRESULT hr;

	//Sprite indices buffer
	DWORD indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	D3D11_BUFFER_DESC spriteIndexBufferDesc;
	ZeroMemory(&spriteIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	spriteIndexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	spriteIndexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	spriteIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	spriteIndexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA spriteIndexBufferSubData;
	ZeroMemory(&spriteIndexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	spriteIndexBufferSubData.pSysMem = indices;

	hr = dev->CreateBuffer(&spriteIndexBufferDesc, &spriteIndexBufferSubData, &spriteIndicesBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create sprite indices buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initSpriteSampler() {
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"pngwing.png",
		NULL, NULL, &spriteShaderResourceView, NULL);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create sprite shader resource view from file", L"Error", MB_OK);
		exit(-1);
	}

	D3D11_SAMPLER_DESC spriteSamplerStateDesc;
	ZeroMemory(&spriteSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	spriteSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	spriteSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	spriteSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	spriteSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	spriteSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	spriteSamplerStateDesc.MinLOD = 0;
	spriteSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = dev->CreateSamplerState(&spriteSamplerStateDesc, &spriteSamplerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create sprite sampler state", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::updateSprite() {
	XMMATRIX spriteWorld = XMMatrixIdentity();
	WVP = spriteWorld * camView * camProjection;
	cbInformation.cbObject = XMMatrixTranspose(WVP);
	devCon->UpdateSubresource(worldCb, 0, NULL, &cbInformation, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &worldCb);
}

void D3D::renderSprite() {
	devCon->VSSetShader(spriteVertexShader, 0, 0);
	devCon->PSSetShader(spritePixelShader, 0, 0);
	devCon->IASetInputLayout(spriteInputLayout);

	UINT stride = sizeof(sprite);
	UINT offset = 0;
	devCon->IASetVertexBuffers(0, 1, &spriteVertexBuffer, &stride, &offset);
	devCon->IASetIndexBuffer(spriteIndicesBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	devCon->PSSetShaderResources(1, 1, &spriteShaderResourceView);
	devCon->PSSetSamplers(1, 1, &spriteSamplerState);
	
	//Animate sprite sheet
	if (currTime - lastTime > 0.50f) {
		animateSpriteSheet();
		lastTime = currTime;
	}
	
	updateSprite();

	devCon->DrawIndexed(6, 0, 0);
}