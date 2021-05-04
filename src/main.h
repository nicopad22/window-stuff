#include <windows.h>
#include <stdint.h>

#define PIXELWIDTH 190
#define PIXELHEIGHT 120

typedef struct window_info {
	void *memory;
	uint32_t bgColor;
	int clientHeight;
	int clientWidth;
} window_info;

typedef struct player {
	int x;
	int y;

	int speed;
	
	void (*KeyStrokeCallBack)(struct player * p, WPARAM w);
} player_t;

void OnKeyStroke(player_t *player, WPARAM key);
void drawRectangle(window_info info, int x, int y, int width, int height, uint32_t color);
