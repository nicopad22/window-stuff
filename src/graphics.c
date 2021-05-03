#include <windows.h>
#include <stdint.h>					
#include "main.h"

/* GRAPHICS FUNCTIONS, RECT, SPRITE, ETC */

void drawRectangle(window_info info, int x, int y, int width, int height, uint32_t color) {
	uint32_t *pixel = (uint32_t *)info.memory;
	
	// get starting pixel point
	pixel += y * info.clientWidth + x;

	// uint32_t *rect_start = pixel;
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (y + i < info.clientHeight && y + i > 0 && x + j < info.clientWidth && x + j > 0)
				*pixel = color;
			
			pixel++;
		}
		pixel += info.clientWidth - width;
	}
}
