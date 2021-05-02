#include <windows.h>
#include <windowsx.h>
#include <stdint.h>
#include <stdio.h>
#include "main.h"

int globalrunning = 1;

int client_height, client_width;

BITMAPINFO bitmap_info;

window_info info;

POINT lastClicked = {0, 0};

struct player playerInstance;
	
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
	LRESULT result;
	
	switch(message) {
    case WM_CLOSE:
		globalrunning = 0;
		break;
		
    case WM_KEYDOWN:
		playerInstance.KeyStrokeCallBack(&playerInstance, w_param);
		break;
		
	case WM_LBUTTONDOWN:
		lastClicked.x = GET_X_LPARAM(l_param);
		lastClicked.y = info.client_height - GET_Y_LPARAM(l_param);
		break;
		
    default:
		result = DefWindowProc(window, message, w_param, l_param);
		break;
	}
  
	return result;
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prev_instance, PWSTR cmd_line, int cmd_show) {
	WNDCLASS window_class = {0};

	wchar_t class_name[] = L"GameWindowClass";

	// Set up window class: all window configs go here apparently
	window_class.lpfnWndProc = WindowProc;
	window_class.hInstance = instance;
	window_class.lpszClassName = class_name;
	window_class.hCursor = LoadCursor(0, IDC_CROSS /* cross cursor */);

	// tell windows this is in fact the class for this window, and idk use the settings or smthng
	RegisterClass(&window_class);

	// Fucking windows forces you to use their wierd each-argument-in-its-line syntax... NOOOO IM NOT GOING TO >:(
	HWND window = CreateWindowEx(0, class_name, L"Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instance, 0);

	// the window is a rect :o
	RECT rect;
	GetClientRect(window, &rect);
	info.client_width = rect.right - rect.left;
	info.client_height = rect.bottom - rect.top;

	// allocate framebuffer
	info.memory = VirtualAlloc(0, info.client_height * info.client_width * 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	// initialize bitmap info header
	bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
	bitmap_info.bmiHeader.biWidth = info.client_width;
	bitmap_info.bmiHeader.biHeight = info.client_height;
	bitmap_info.bmiHeader.biPlanes = 1;
	bitmap_info.bmiHeader.biBitCount = 32;
	bitmap_info.bmiHeader.biCompression = BI_RGB;

	HDC hdc = GetDC(window);

	// intialize player
	playerInstance.KeyStrokeCallBack = OnKeyStroke;
	playerInstance.speed = 10;
	
	while (globalrunning) {
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);

			//clear screen before drawing anything
			uint32_t *pixel = (uint32_t *)info.memory;
			for (int pixel_index = 0; pixel_index < info.client_width * info.client_height; pixel_index++) {
				pixel[pixel_index] = 0x111111;
			}
			
			drawRectangle(info, playerInstance.x, playerInstance.y, 100, 100, 0xFF0000);
			drawRectangle(info, lastClicked.x, lastClicked.y, 20, 20, 0x222222);
		}
		StretchDIBits(hdc, 0, 0, info.client_width, info.client_height, 0, 0, info.client_width, info.client_height, info.memory, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}

	return 0;
}
