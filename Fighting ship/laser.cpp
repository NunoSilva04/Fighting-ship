#include "initD3D.h"

void D3D::initLaserShaders() {
	HRESULT hr;

	//Laser Vertex shader
	ID3D10Blob* pLaserVertexShader = nullptr;
	hr = D3DX10CompileFromFile(L"LaserVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pLaserVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile laser vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateVertexShader(pLaserVertexShader->GetBufferPointer(), pLaserVertexShader->GetBufferSize(), 0, 
		&laserVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create laser vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	//Laser Pixel shader
	ID3D10Blob* pLaserPixelShader = nullptr;
	hr = D3DX11CompileFromFile(L"LaserPixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pLaserPixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile laser pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreatePixelShader(pLaserPixelShader->GetBufferPointer(), pLaserPixelShader->GetBufferSize(), 0, 
		&laserPixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create laser pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	//Laser input layout
	D3D11_INPUT_ELEMENT_DESC laserInputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(laserInputLayoutDesc);
	dev->CreateInputLayout(laserInputLayoutDesc, size, pLaserVertexShader->GetBufferPointer(), pLaserVertexShader->GetBufferSize(),
		&laserInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create laser input layout", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initLaserVertexBuffer() {
	HRESULT hr;

	//Laser vertex buffer
	for (int i = 0; i < 80; i++) {
		laserVertices[i].position = XMFLOAT3(0.0f, 0.0f, -1.0f);
		laserVertices[i].texCoord = XMFLOAT2(0.0f, 0.0f);
		i++;
		laserVertices[i].position = XMFLOAT3(0.0f, 0.0f, -1.0f);
		laserVertices[i].texCoord = XMFLOAT2(1.0f, 0.0f);
		i++;
		laserVertices[i].position = XMFLOAT3(0.0f, 0.0f, -1.0f);
		laserVertices[i].texCoord = XMFLOAT2(0.0f, 1.0f);
		i++;
		laserVertices[i].position = XMFLOAT3(0.0f, 0.0f, -1.0f);
		laserVertices[i].texCoord = XMFLOAT2(1.0f, 1.0f);
	}

	D3D11_BUFFER_DESC laserVertexBufferDesc;
	ZeroMemory(&laserVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	laserVertexBufferDesc.ByteWidth = 80 * sizeof(laserStruct);
	laserVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	laserVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	laserVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA laserVertexBufferSubData;
	ZeroMemory(&laserVertexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	laserVertexBufferSubData.pSysMem = laserVertices;

	hr = dev->CreateBuffer(&laserVertexBufferDesc, &laserVertexBufferSubData, &laserVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create laser vertex buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initLaserIndexBuffer() {
	HRESULT hr;

	//Laser index buffer
	DWORD indices[120];
	int numIndices = 0, indiceValue = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 6; j++) {
			if (j < 3) {
				indices[numIndices] = indiceValue;
				indiceValue++;
				numIndices++;
			}
			else if (j == 3) {
				indices[numIndices] = indiceValue - 1;
				numIndices++;
				indices[numIndices] = indiceValue - 2;
				numIndices++;
				indices[numIndices] = indiceValue;
				numIndices++;
				indiceValue++;
				j += 3;
			}
		}
	}

	D3D11_BUFFER_DESC laserIndexBufferDec;
	ZeroMemory(&laserIndexBufferDec, sizeof(D3D11_BUFFER_DESC));
	laserIndexBufferDec.ByteWidth = 120 * sizeof(DWORD);
	laserIndexBufferDec.Usage = D3D11_USAGE_DYNAMIC;
	laserIndexBufferDec.BindFlags = D3D11_BIND_INDEX_BUFFER;
	laserIndexBufferDec.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA laserIndexBufferSubData;
	ZeroMemory(&laserIndexBufferSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	laserIndexBufferSubData.pSysMem = indices;

	hr = dev->CreateBuffer(&laserIndexBufferDec, &laserIndexBufferSubData, &laserIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create laser index buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initLaserSamplerState() {
	HRESULT hr;

	//laser shader resource view
	hr = D3DX11CreateShaderResourceViewFromFile(dev, L"Laser.png",
		NULL, NULL, &laserShaderResourceView, NULL);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create laser shader resource view", L"Error", MB_OK);
		exit(-1);
	}

	//Laser sampler state
	D3D11_SAMPLER_DESC laserSamplerStateDesc;
	ZeroMemory(&laserSamplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	laserSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	laserSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	laserSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	laserSamplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	laserSamplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	laserSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
	laserSamplerStateDesc.MinLOD = 0;

	hr = dev->CreateSamplerState(&laserSamplerStateDesc, &laserSamplerState);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create laser sampler state", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::updateLaserWorld() {
	for (int i = 0; i < numLasersDisplayed; i++) {
		laserSpeedArray[i].laserSpeedvar += 0.0005f;
		eachLaserSpeedMatrix[i].speed = XMMatrixTranslation(moveLaserPositionArray[i].laserStartPosX,
			moveLaserPositionArray[i].laserStartPosY + laserSpeedArray[i].laserSpeedvar, 0.0f);
		
		laserWorld = eachLaserSpeedMatrix[i].speed;

		WVP = laserWorld * camView * camProjection;
		cbInformation.cbObject = XMMatrixTranspose(WVP);
		devCon->UpdateSubresource(worldCb, 0, NULL, &cbInformation, 0, 0);
		devCon->VSSetConstantBuffers(0, 1, &worldCb);

		devCon->DrawIndexed(120, 0, 0);
	}
}

void D3D::renderLaser() {
	devCon->VSSetShader(laserVertexShader, 0, 0);
	devCon->PSSetShader(laserPixelShader, 0, 0);
	devCon->IASetInputLayout(laserInputLayout);

	UINT stride = sizeof(laserStuct);
	UINT offset = 0;
	devCon->IASetVertexBuffers(0, 1, &laserVertexBuffer, &stride, &offset);
	devCon->IASetIndexBuffer(laserIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devCon->PSSetShaderResources(4, 1, &laserShaderResourceView);
	devCon->PSSetSamplers(4, 1, &laserSamplerState);
	
	if (playerShootLaser == true) {
		shootLaserFunc();
	}
	updateLaserWorld();
}