#include "initD3D.h"

void D3D::initTextureShaders() {
	HRESULT hr;

	//Initalize texture Vertex Shader
	ID3D10Blob* pTextureVertexShader = nullptr;
	hr = D3DX10CompileFromFile(L"TextureVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pTextureVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile tetxure vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateVertexShader(pTextureVertexShader->GetBufferPointer(), pTextureVertexShader->GetBufferSize(),
		nullptr, &textureVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create texture vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	//Initalize texture Pixel Shader
	ID3D10Blob* pTexturePixelShader = nullptr;
	hr = D3DX10CompileFromFile(L"TexturePixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pTexturePixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile texture pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreatePixelShader(pTexturePixelShader->GetBufferPointer(), pTexturePixelShader->GetBufferSize(),
		nullptr, &texturePixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create texture pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	//Initalize texture input layout
	D3D11_INPUT_ELEMENT_DESC textureInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(textureInputLayoutDesc);

	hr = dev->CreateInputLayout(textureInputLayoutDesc, size, pTextureVertexShader->GetBufferPointer(),
		pTextureVertexShader->GetBufferSize(), &textureInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create texture input layout", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initTextureVertexBuffer() {
	HRESULT hr;

	texture textureVertices[] = {
		{XMFLOAT3(-0.4f, 0.4f, 0.0f), XMFLOAT2(0.0f, 0.0f)},
		{XMFLOAT3(0.4f, 0.4f, 0.0f), XMFLOAT2(1.0f, 0.0f)},
		{XMFLOAT3(-0.4f, -0.4f, 0.0f), XMFLOAT2(0.0f, 1.0f)},
		{XMFLOAT3(0.4f, -0.4f, 0.0f), XMFLOAT2(1.0f, 1.0f)},
	};

	D3D11_BUFFER_DESC textureVerticesDesc;
	ZeroMemory(&textureVerticesDesc, sizeof(D3D11_BUFFER_DESC));
	textureVerticesDesc.ByteWidth = 4 * sizeof(texture);
	textureVerticesDesc.Usage = D3D11_USAGE_DYNAMIC;
	textureVerticesDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	textureVerticesDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA textureVerticesSubData;
	ZeroMemory(&textureVerticesSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	textureVerticesSubData.pSysMem = textureVertices;

	hr = dev->CreateBuffer(&textureVerticesDesc, &textureVerticesSubData, &textureVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create texture vertex buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initTextureIndicesBuffer() {
	HRESULT hr;

	DWORD indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	D3D11_BUFFER_DESC textureIndicesDesc;
	ZeroMemory(&textureIndicesDesc, sizeof(D3D11_BUFFER_DESC));
	textureIndicesDesc.ByteWidth = 6 * sizeof(DWORD);
	textureIndicesDesc.Usage = D3D11_USAGE_DYNAMIC;
	textureIndicesDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	textureIndicesDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA textureIndicesSubData;
	ZeroMemory(&textureIndicesSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	textureIndicesSubData.pSysMem = indices;

	hr = dev->CreateBuffer(&textureIndicesDesc, &textureIndicesSubData, &textureIndicesBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create texture index Buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initTextureSampler() {
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"X.png", NULL, NULL,
		&textureShaderResourceView, NULL);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create shader resource view from file", L"Error", MB_OK);
		exit(-1);
	}

	D3D11_SAMPLER_DESC textureSamplerStateDesc;
	ZeroMemory(&textureSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	textureSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	textureSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	textureSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	textureSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	textureSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	textureSamplerStateDesc.MinLOD = 0;
	textureSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = dev->CreateSamplerState(&textureSamplerStateDesc, &textureSamplerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create texture Sampler state", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::updateTexture() {
	if (movePosTexture > -1.5f) {
		movePosTexture -= 0.0001f;
	}

	textureTranslation = XMMatrixTranslation(movePosTexture, 0.0f, 0.0f);

	WVP = textureTranslation * camView * camProjection;
	cbInformation.cbObject = XMMatrixTranspose(WVP);
	devCon->UpdateSubresource(worldCb, 0, NULL, &cbInformation, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &worldCb);
}

void D3D::renderTexture() {
	devCon->VSSetShader(textureVertexShader, 0, 0);
	devCon->PSSetShader(texturePixelShader, 0, 0);
	devCon->IASetInputLayout(textureInputLayout);

	UINT stride = sizeof(texture);
	UINT offset = 0;
	devCon->IASetVertexBuffers(0, 1, &textureVertexBuffer, &stride, &offset);
	devCon->IASetIndexBuffer(textureIndicesBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetSamplers(0, 1, &textureSamplerState);
	devCon->PSSetShaderResources(0, 1, &textureShaderResourceView);

	updateTexture();

	devCon->DrawIndexed(6, 0, 0);
}