#include <Windows.h>
#include "initD3D.h"

#define MAX_WIDTH 800
#define MAX_HEIGHT 600

D3D demo;

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int CmdShow) {
	HWND hWnd;

	//Window Class 
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.hInstance = hInstance;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpszClassName = L"Main Window";
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpfnWndProc = WindowProcedure;

	if (RegisterClassEx(&windowClass) == NULL) {
		MessageBox(nullptr, L"Couldn't Create window class", L"Error", MB_OK);
		exit(-1);
	}

	hWnd = CreateWindowEx(NULL, L"Main Window", L"FightingShip", WS_OVERLAPPEDWINDOW, 100, 100, MAX_WIDTH, MAX_HEIGHT, NULL, NULL,
		hInstance, NULL);
	ShowWindow(hWnd, CmdShow);
	demo.initD3D(hWnd);

	MSG msg = { 0 };
	while (TRUE) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			demo.renderFrame();
			demo.checkPlayerShootLaser();
		}
	}

	demo.cleanD3D();
	return msg.wParam;
}