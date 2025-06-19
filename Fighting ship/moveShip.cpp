#include "initD3D.h"

void D3D::moveFightingShip() {
	if (GetAsyncKeyState('W') & 0x8000) {
		moveUpDown += 0.0004f;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		moveUpDown -= 0.0004f;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		moveLeftRight += 0.0004f;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		moveLeftRight -= 0.0004f;
	}
}