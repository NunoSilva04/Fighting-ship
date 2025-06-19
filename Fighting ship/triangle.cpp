#include "initD3D.h"

void D3D::initTriangleShaders() {
	HRESULT hr;

	//Triangle Vertex Shader
	ID3D10Blob* pTriangleVertexShader = nullptr;
	hr = D3DX10CompileFromFile(L"TriangleVertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, 0, &pTriangleVertexShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile triangle vertex shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateVertexShader(pTriangleVertexShader->GetBufferPointer(), pTriangleVertexShader->GetBufferSize(),
		nullptr, &triangleVertexShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create triangle vertex Shader", L"Error", MB_OK);
		exit(-1);
	}

	//Triangle Pixel Shader
	ID3D10Blob* pTrianglePixelShader = nullptr;
	hr = D3DX10CompileFromFile(L"TrianglePixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, 0, &pTrianglePixelShader, 0, 0);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't compile triangle pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreatePixelShader(pTrianglePixelShader->GetBufferPointer(), pTrianglePixelShader->GetBufferSize(),
		nullptr, &trianglePixelShader);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create triangle pixel shader", L"Error", MB_OK);
		exit(-1);
	}

	//Triangle input Layout
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size = ARRAYSIZE(inputLayoutDesc);

	hr = dev->CreateInputLayout(inputLayoutDesc, size, pTriangleVertexShader->GetBufferPointer(), pTriangleVertexShader->GetBufferSize(),
		&triangleInputLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Coudln't create triangle input Layout", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initTriangleVertexBuffer() {
	HRESULT hr;

	triangle triangleVertices[] = {
		{XMFLOAT3(-0.5f, -0.5f, 0.5f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(0.0f, 0.5f, 0.5f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3(0.5f, -0.5f, 0.5f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
	};

	D3D11_BUFFER_DESC triangleVerticesDesc;
	ZeroMemory(&triangleVerticesDesc, sizeof(D3D11_BUFFER_DESC));
	triangleVerticesDesc.ByteWidth = 3 * sizeof(triangle);
	triangleVerticesDesc.Usage = D3D11_USAGE_DYNAMIC;
	triangleVerticesDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	triangleVerticesDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA triangleVerticesSubData;
	ZeroMemory(&triangleVerticesSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	triangleVerticesSubData.pSysMem = triangleVertices;

	hr = dev->CreateBuffer(&triangleVerticesDesc, &triangleVerticesSubData, &triangleVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create triangle vertex Buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::initTriangleIndicesBuffer() {
	HRESULT hr;

	DWORD indices[] = {
		0, 1, 2,
	};

	D3D11_BUFFER_DESC triangleIndicesDesc;
	ZeroMemory(&triangleIndicesDesc, sizeof(D3D11_BUFFER_DESC));
	triangleIndicesDesc.ByteWidth = 3 * sizeof(DWORD);
	triangleIndicesDesc.Usage = D3D11_USAGE_DYNAMIC;
	triangleIndicesDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	triangleIndicesDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA triangleIndicesSubData;
	ZeroMemory(&triangleIndicesSubData, sizeof(D3D11_SUBRESOURCE_DATA));
	triangleIndicesSubData.pSysMem = indices;

	hr = dev->CreateBuffer(&triangleIndicesDesc, &triangleIndicesSubData, &triangleIndicesBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create triangle indices buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::updateTriangle() {
	if (movePosTriangle < 1.5f) {
		movePosTriangle += 0.0001f;
	}
	triangleTranslation = XMMatrixTranslation(movePosTriangle, 0.0f, 0.0f);

	WVP = triangleTranslation * camView * camProjection;
	cbInformation.cbObject = XMMatrixTranspose(WVP);
	devCon->UpdateSubresource(worldCb, 0, NULL, &cbInformation, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &worldCb);
}

void D3D::renderTriangle() {
	devCon->VSSetShader(triangleVertexShader, 0, 0);
	devCon->PSSetShader(trianglePixelShader, 0, 0);
	devCon->IASetInputLayout(triangleInputLayout);

	UINT size = sizeof(triangle);
	UINT offset = 0;
	devCon->IASetVertexBuffers(0, 1, &triangleVertexBuffer, &size, &offset);
	devCon->IASetIndexBuffer(triangleIndicesBuffer, DXGI_FORMAT_R32_UINT, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	updateTriangle();
	devCon->DrawIndexed(3, 0, 0);
}