#include "initD3D.h"

void D3D::initFireShaders() {
	HRESULT hr;

	//Fire Vertex shader
	ID3D10Blob* pFireVertexShader = nullptr;
	hr = D3DX11CompileFromFile(L"FireVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pFireVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile fire vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateVertexShader(pFireVertexShader->GetBufferPointer(), pFireVertexShader->GetBufferSize(),
		0, &fireVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	//Fire pixel shader
	ID3D10Blob* pFirePixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"FirePixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pFirePixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile fire pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreatePixelShader(pFirePixelShader->GetBufferPointer(), pFirePixelShader->GetBufferSize(), 0,
		&firePixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create fire pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	//Fire input Layout
	D3D11_INPUT_ELEMENT_DESC fireInputLayoutDesc[] = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(fireInputLayoutDesc);

	hr = dev->CreateInputLayout(fireInputLayoutDesc, size, pFireVertexShader->GetBufferPointer(), pFireVertexShader->GetBufferSize(),
		&fireInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create input layout", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initFireVertexBuffer() {
	HRESULT hr;

	//Fire vertex Buffer
	fireVertices[0].position = XMFLOAT3(0.4f, -0.7f, -1.0f);
	fireVertices[0].texCoord = XMFLOAT2(0.0f, 0.0f);
	fireVertices[1].position = XMFLOAT3(0.6f, -0.7f, -1.0f);
	fireVertices[1].texCoord = XMFLOAT2(0.2f, 0.0f);
	fireVertices[2].position = XMFLOAT3(0.4f, -1.0f, -1.0f);
	fireVertices[2].texCoord = XMFLOAT2(0.0f, 0.2f);
	fireVertices[3].position = XMFLOAT3(0.6f, -1.0f, -1.0f);
	fireVertices[3].texCoord = XMFLOAT2(0.2f, 0.2f);

	D3D11_BUFFER_DESC fireVertexBufferDesc;
	ZeroMemory(&fireVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	fireVertexBufferDesc.ByteWidth = 4 * sizeof(fireStruct);
	fireVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	fireVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	fireVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA fireVertexBufferSubData;
	ZeroMemory(&fireVertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	fireVertexBufferSubData.pSysMem = fireVertices;

	hr = dev->CreateBuffer(&fireVertexBufferDesc, &fireVertexBufferSubData, &fireVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create fire vertex buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initFireIndexBuffer() {
	HRESULT hr;

	DWORD indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	D3D11_BUFFER_DESC fireIndexBufferDesc;
	ZeroMemory(&fireIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	fireIndexBufferDesc.ByteWidth = 6 * sizeof(DWORD);
	fireIndexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	fireIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	fireIndexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA fireIndexBufferSubData;
	ZeroMemory(&fireIndexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	fireIndexBufferSubData.pSysMem = indices;

	hr = dev->CreateBuffer(&fireIndexBufferDesc, &fireIndexBufferSubData, &fireIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create fire index buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initFireSamplerState() {
	HRESULT hr;

	//Fire shader resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"firesheet5x5noBackground.png",
		NULL, NULL, &fireShaderResourceView, NULL);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Could't create fire shader resource view", L"Error", MB_OK);
		exit(-1);
	}

	//Fire sampler state
	D3D11_SAMPLER_DESC fireSamplerStateDesc;
	ZeroMemory(&fireSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	fireSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	fireSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	fireSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	fireSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	fireSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	fireSamplerStateDesc.MinLOD = 0;
	fireSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = dev->CreateSamplerState(&fireSamplerStateDesc, &fireSamplerState);
}

void D3D::updateFire() {
	XMMATRIX rotation = XMMatrixRotationZ(XMConvertToRadians(180.0f));
	XMMATRIX translation = XMMatrixTranslation(0.5f + moveLeftRight, -1.9f + moveUpDown, 0.0f);
	fireWorld = rotation * translation;

	WVP = fireWorld * camView * camProjection;
	cbInformation.cbObject = XMMatrixTranspose(WVP);
	devCon->UpdateSubresource(worldCb, 0, NULL, &cbInformation, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &worldCb);
}

void D3D::renderFire() {
	devCon->VSSetShader(fireVertexShader, 0, 0);
	devCon->PSSetShader(firePixelShader, 0, 0);
	devCon->IASetInputLayout(fireInputLayout);

	UINT stride = sizeof(fireStruct);
	UINT offset = 0;
	devCon->IASetVertexBuffers(0, 1, &fireVertexBuffer, &stride, &offset);
	devCon->IASetIndexBuffer(fireIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetShaderResources(3, 1, &fireShaderResourceView);
	devCon->PSSetSamplers(3, 1, &fireSamplerState);
	if (currFireTime - prevFireTime >= 0.30f) {
		animateFire();
		prevFireTime = currFireTime;
	}
	updateFire();

	devCon->DrawIndexed(6, 0, 0);
}