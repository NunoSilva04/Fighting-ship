#include "initD3D.h"

void D3D::spriteSheetBillBoard() {
	int numRows = 3;
	int numCollumns = 7;
	int billBoardArraySize = 0;

	float rowOffset = 0.001f, prevRow = 0.0f;
	float collumnOffset = 0.3f, prevCollumn = 0.02f;
	
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCollumns; j++) {
			billBoardVertices[billBoardArraySize].texCoord = XMFLOAT2(rowOffset, prevCollumn);
			billBoardArraySize++;
			prevRow = rowOffset;
			rowOffset += 0.14f;
			if (rowOffset >= 0.98f) {
				rowOffset = 0.973f;
			}
			billBoardVertices[billBoardArraySize].texCoord = XMFLOAT2(rowOffset, prevCollumn);
			billBoardArraySize++;
			billBoardVertices[billBoardArraySize].texCoord = XMFLOAT2(prevRow, collumnOffset);
			billBoardArraySize++;
			if (rowOffset >= 0.98f) {
				rowOffset = 0.973f;
			}
			billBoardVertices[billBoardArraySize].texCoord = XMFLOAT2(rowOffset, collumnOffset);
			billBoardArraySize++;
		}
		prevCollumn = collumnOffset + 0.05f;
		collumnOffset += 0.4f;
		if (i == 1) {
			prevCollumn = 0.7f;
			collumnOffset = 1.0f;
		}
		rowOffset = 0.01f;
	}
	totalBillBoardArray = billBoardArraySize;
}

void D3D::animateSpriteSheet() {
	HRESULT hr;
	
	D3D11_MAPPED_SUBRESOURCE mappedSubResoruce;
	hr = devCon->Map(spriteVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedSubResoruce);
	if (SUCCEEDED(hr)) {
		spriteVertices[0].texCoord = billBoardVertices[runThroughBillBoard].texCoord;
		runThroughBillBoard++;
		spriteVertices[1].texCoord = billBoardVertices[runThroughBillBoard].texCoord;
		runThroughBillBoard++;
		spriteVertices[2].texCoord = billBoardVertices[runThroughBillBoard].texCoord;
		runThroughBillBoard++;
		spriteVertices[3].texCoord = billBoardVertices[runThroughBillBoard].texCoord;
		runThroughBillBoard++;
		memcpy(mappedSubResoruce.pData, spriteVertices, sizeof(spriteVertices));
		devCon->Unmap(spriteVertexBuffer, 0);
	}
	else {
		MessageBox(nullptr, L"Coulnd't map subresource", L"Error", MB_OK);
	}
	if (runThroughBillBoard == totalBillBoardArray) {
		runThroughBillBoard = 0;
	}
}