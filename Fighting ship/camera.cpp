#include "initD3D.h"

void D3D::initCamera() {
	camPosition = XMVectorSet(0.0f, 0.0f, -4.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	camProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), (float)800 / 600, 0.1f, 1000.0f);
}
