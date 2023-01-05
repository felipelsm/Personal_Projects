// In�cio: 16/08/2021	Fim: 00/00/0000

#include <windows.h>
#include "utils.h"
#include "input.h"
#include "renderer.h"
#include "engine.h"
#include "win32_platform.h"




internal bool running = true;

Render_State render_state;




LRESULT CALLBACK window_callback(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
		} break;

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			render_state.width = rect.right - rect.left;
			render_state.height = rect.bottom - rect.top;

			int size = render_state.width * render_state.height * sizeof(u32);

			if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
			render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
			render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
			render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
			render_state.bitmap_info.bmiHeader.biPlanes = 1;
			render_state.bitmap_info.bmiHeader.biBitCount = 32;
			render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
		} break;

		default: {
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	return result;
}





int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	// Create Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = window_callback;

	// Register Class
	RegisterClass(&window_class);

	// Create Window			//lpClassName			lpWindowName				dwStyle					x				y	  nWidth	nHeight	hWndParent	hMenu	hInstance	lpParam
	HWND window = CreateWindow(window_class.lpszClassName, "Pong", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);

	HDC hdc = GetDC(window);
	Input input = {};


	/***** Beginning of frame *****/
	float delta_time = 0.016666f;
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);
	float performace_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performace_frequency = (float)perf.QuadPart;
	}


	while (running) {
		// Input
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
if(is_down != input.buttons[b].is_down) input.buttons[b].changed = is_down;\
input.buttons[b].is_down = is_down;\
} break;

				switch (vk_code) {
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_DOWN, VK_DOWN);
					process_button(BUTTON_W, 'W');
					process_button(BUTTON_S, 'S');
					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);
					process_button(BUTTON_ENTER, VK_RETURN);
				}
			} break;

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}

		// Simulate
		//simulate_game(&input, delta_time);

		// Render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		/***** End of frame *****/
		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performace_frequency;
		frame_begin_time = frame_end_time;
	}
}