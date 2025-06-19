#include "initD3D.h"

void D3D::initLaserSpeedMatrixArray() {
	for (int i = 0; i < 20; i++) {
		laserSpeedArray[i].laserSpeedvar = 0.0f;
		eachLaserSpeedMatrix[i].speed = XMMatrixIdentity();
		moveLaserPositionArray[i].laserStartPosX = 0.0f;
		moveLaserPositionArray[i].laserStartPosY = 0.0f;
	}
}

void D3D::shootLaserFunc() {
	HRESULT hr;

	D3D11_MAPPED_SUBRESOURCE mappedSubResoure;
	hr = devCon->Map(laserVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedSubResoure);
	if (SUCCEEDED(hr)) {
		laserVertices[runThroughLaserArray].position = XMFLOAT3(-0.1f, -0.45f, -1.0f);
		runThroughLaserArray++;
		laserVertices[runThroughLaserArray].position = XMFLOAT3(0.1f, -0.45f, -1.0f);
		runThroughLaserArray++;
		laserVertices[runThroughLaserArray].position = XMFLOAT3(-0.1f, -0.65f, -1.0f);
		runThroughLaserArray++;
		laserVertices[runThroughLaserArray].position = XMFLOAT3(0.1f, -0.65f, -1.0f);
		runThroughLaserArray++;
		memcpy(mappedSubResoure.pData, laserVertices, sizeof(laserVertices));
		devCon->Unmap(laserVertexBuffer, 0);
		moveLaserPositionArray[numLasersDisplayed].laserStartPosX = moveLeftRight;
		moveLaserPositionArray[numLasersDisplayed].laserStartPosY = moveUpDown;
		numLasersDisplayed++;
	}
	else {
		MessageBox(nullptr, L"Couldn't map laser sub resource", L"Error", MB_OK);
		exit(-1);
	}
	if (runThroughLaserArray == 80) {
		initLaserSpeedMatrixArray();
		runThroughLaserArray = 0;
	}
	if (numLasersDisplayed == 20) {
		numLasersDisplayed = 0;
	}
	playerShootLaser = false;
}

void D3D::checkPlayerShootLaser() {
	if (GetAsyncKeyState('L') & 0x8000) {
		if (shootLaser == true) {
			shootLaser = false;
			startDelay = true;
			playerShootLaser = true;
		}
	}
	if (startDelay == true) {
		delay += 0.005f;
	}
	if (delay >= 3.0f) {
		shootLaser = true;
		startDelay = false;
		delay = 0.0f;
	}
}
