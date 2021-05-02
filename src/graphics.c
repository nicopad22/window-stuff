#include <windows.h>
#include <stdint.h>					
#include "main.h"

/* GRAPHICS FUNCTIONS, RECT, SPRITE, ETC */

void drawRectangle(window_info info, int x, int y, int width, int height, uint32_t color) {
	uint32_t *pixel = (uint32_t *)info.memory;
	
	// get starting pixel point
	pixel += y * info.client_width + x;

	// uint32_t *rect_start = pixel;
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			*pixel = color;
			
			pixel++;
		}
		pixel += info.client_width - width;
	}
}
