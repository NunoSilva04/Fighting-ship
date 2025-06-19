#include "initD3D.h"

void D3D::initFireBillBoardSheet() {
	int numRows = 5;
	int numCollumns = 5;

	float currRow = 0.2f, prevRow = 0.0f;
	float currCollumn = 0.2f, prevCollumn = 0.0f;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCollumns; j++) {
			fireBillBoardVertices[numFireBillBoardVertices].texCoord = XMFLOAT2(prevRow, prevCollumn);
			numFireBillBoardVertices++;
			fireBillBoardVertices[numFireBillBoardVertices].texCoord = XMFLOAT2(currRow, prevCollumn);
			numFireBillBoardVertices++;
			fireBillBoardVertices[numFireBillBoardVertices].texCoord = XMFLOAT2(prevRow, currCollumn);
			numFireBillBoardVertices++;
			fireBillBoardVertices[numFireBillBoardVertices].texCoord = XMFLOAT2(currRow, currCollumn);
			numFireBillBoardVertices++;
			prevRow = currRow;
			currRow += 0.2f;
		}
		currRow = 0.2f;
		prevRow = 0.0f;
		prevCollumn = currCollumn;
		currCollumn += 0.2f;
	}
}

void D3D::animateFire() {
	HRESULT hr;

	D3D11_MAPPED_SUBRESOURCE fireMapSubResource;
	hr = devCon->Map(fireVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &fireMapSubResource);
	if (SUCCEEDED(hr)) {
		fireVertices[0].texCoord = fireBillBoardVertices[runThroughFireBillBoardVertices].texCoord;
		runThroughFireBillBoardVertices++;
		fireVertices[1].texCoord = fireBillBoardVertices[runThroughFireBillBoardVertices].texCoord;
		runThroughFireBillBoardVertices++;
		fireVertices[2].texCoord = fireBillBoardVertices[runThroughFireBillBoardVertices].texCoord;
		runThroughFireBillBoardVertices++;
		fireVertices[3].texCoord = fireBillBoardVertices[runThroughFireBillBoardVertices].texCoord;
		runThroughFireBillBoardVertices++;
		memcpy(fireMapSubResource.pData, fireVertices, sizeof(fireVertices));
		devCon->Unmap(fireVertexBuffer, 0);
	}
	else {
		MessageBox(nullptr, L"Couldn't map fire", L"Error", MB_OK);
		exit(-1);
	}
	if (runThroughFireBillBoardVertices == numFireBillBoardVertices) {
		runThroughFireBillBoardVertices = 0;
	}
}