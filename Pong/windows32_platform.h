#pragma once

#include <windows.h>



struct Render_State {
	int width, height;
	void* memory;

	BITMAPINFO bitmap_info;
};

extern Render_State render_state;