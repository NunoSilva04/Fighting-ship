#include "initD3D.h"

void D3D::keyboardInputs(WPARAM wParam) {
	float cameraSpeed = 0.0002f;
	moveBackForward += cameraSpeed;
	updateCamera();
	moveBackForward = 0.0f;
}