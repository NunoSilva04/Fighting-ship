#include "initD3D.h"

void D3D::initFightingShipShaders() {
	HRESULT hr;

	//FightingShip Vertex Shader
	ID3D10Blob* pFightingShipVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"FightingShipVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pFightingShipVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile FightingShip vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateVertexShader(pFightingShipVertexShader->GetBufferPointer(), pFightingShipVertexShader->GetBufferSize(),
		0, &fightingShipVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create FightingShip vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	//FightingShip Pixel shader
	ID3D10Blob* pFightingShipPixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"FightingShipPixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pFightingShipPixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile FightingShip pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreatePixelShader(pFightingShipPixelShader->GetBufferPointer(), pFightingShipPixelShader->GetBufferSize(), 0,
		&fightingShipPixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create FightingShip pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	//FightingShip input layout
	D3D11_INPUT_ELEMENT_DESC fightingShipInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT size = ARRAYSIZE(fightingShipInputLayoutDesc);
	hr = dev->CreateInputLayout(fightingShipInputLayoutDesc, size, pFightingShipVertexShader->GetBufferPointer(),
		pFightingShipVertexShader->GetBufferSize(), &fightingShipInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create fighting ship input layout", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initFightingShipVertexBuffer() {
	HRESULT hr;

	fightingShipVertices[0].position = XMFLOAT3(-0.2f, -0.6f, -1.0f);
	fightingShipVertices[0].texCoord = XMFLOAT2(0.0f, 0.0f);
	fightingShipVertices[1].position = XMFLOAT3(0.2f, -0.6f, -1.0f);
	fightingShipVertices[1].texCoord = XMFLOAT2(1.0f, 0.0f);
	fightingShipVertices[2].position = XMFLOAT3(-0.2f, -1.0f, -1.0f);
	fightingShipVertices[2].texCoord = XMFLOAT2(0.0f, 1.0f);
	fightingShipVertices[3].position = XMFLOAT3(0.2f, -1.0f, -1.0f);
	fightingShipVertices[3].texCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC fightingShipVertexBufferDesc;
	ZeroMemory(&fightingShipVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	fightingShipVertexBufferDesc.ByteWidth = 4 * sizeof(fightingShipStruc);
	fightingShipVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	fightingShipVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	fightingShipVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA fightingShipVertexSubData;
	ZeroMemory(&fightingShipVertexSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	fightingShipVertexSubData.pSysMem = fightingShipVertices;

	hr = dev->CreateBuffer(&fightingShipVertexBufferDesc, &fightingShipVertexSubData, &fightingShipVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create fighting ship vertex buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initFightingShipIndexBuffer() {
	HRESULT hr;

	//Fighting ship index buffer
	DWORD indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	D3D11_BUFFER_DESC fightingShipIndexBufferDesc;
	ZeroMemory(&fightingShipIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	fightingShipIndexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	fightingShipIndexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	fightingShipIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	fightingShipIndexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA fightingShipIndexSubData;
	ZeroMemory(&fightingShipIndexSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	fightingShipIndexSubData.pSysMem = indices;

	hr = dev->CreateBuffer(&fightingShipIndexBufferDesc, &fightingShipIndexSubData, &fightingShipIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create fighting ship index buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initFightingShipSamplerState() {
	HRESULT hr;

	//fighting ship shader resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev,
		L"fightingship1.png", NULL, NULL,
		&fightingShipShaderResourceView, NULL);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create fighting ship resource view", L"Error", MB_OK);
		exit(-1);
	}

	//fighting ship sampler state
	D3D11_SAMPLER_DESC fightingShipSamplerStateDesc;
	ZeroMemory(&fightingShipSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	fightingShipSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	fightingShipSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	fightingShipSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	fightingShipSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	fightingShipSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	fightingShipSamplerStateDesc.MinLOD = 0;
	fightingShipSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = dev->CreateSamplerState(&fightingShipSamplerStateDesc, &fightingShipSamplerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create fighting ship sampler state", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::updateFightingShip() {
	fightingShipWorld = XMMatrixTranslation(moveLeftRight, moveUpDown, 0.0f);
	WVP = fightingShipWorld * camView * camProjection;
	cbInformation.cbObject = XMMatrixTranspose(WVP);

	devCon->UpdateSubresource(worldCb, 0, NULL, &cbInformation, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &worldCb);
}

void D3D::renderFightingShip() {
	devCon->VSSetShader(fightingShipVertexShader, 0, 0);
	devCon->PSSetShader(fightingShipPixelShader, 0, 0);
	devCon->IASetInputLayout(fightingShipInputLayout);

	UINT stride = sizeof(fightingShipStruc);
	UINT offset = 0;
	devCon->IASetVertexBuffers(0, 1, &fightingShipVertexBuffer, &stride, &offset);
	devCon->IASetIndexBuffer(fightingShipIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetShaderResources(2, 1, &fightingShipShaderResourceView);
	devCon->PSSetSamplers(2, 1, &fightingShipSamplerState);

	//move Ship
	moveFightingShip();

	//Update fighting ship
	updateFightingShip();

	devCon->DrawIndexed(6, 0, 0);
}