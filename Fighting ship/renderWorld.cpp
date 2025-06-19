#include "initD3D.h"

void D3D::initWorldcb() {
	HRESULT hr;

	D3D11_BUFFER_DESC worldCbDesc;
	ZeroMemory(&worldCbDesc, sizeof(D3D11_BUFFER_DESC));
	worldCbDesc.ByteWidth = sizeof(cbStructure);
	worldCbDesc.Usage = D3D11_USAGE_DEFAULT;
	worldCbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	worldCbDesc.CPUAccessFlags = 0;
	worldCbDesc.MiscFlags = 0;

	hr = dev->CreateBuffer(&worldCbDesc, nullptr, &worldCb);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create world cosntant buffer", L"Error", MB_OK);
		exit(-1);
	}
}

void D3D::renderWorldcb() {
	World = XMMatrixIdentity();
	WVP = World * camView * camProjection;
	cbInformation.cbObject = XMMatrixTranspose(WVP);

	devCon->UpdateSubresource(worldCb, 0, NULL, &cbInformation, 0, 0);
	devCon->VSSetConstantBuffers(0, 1, &worldCb);
}