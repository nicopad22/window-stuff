#include <stdio.h>
#include "main.h"

void OnKeyStroke(player_t *player, WPARAM key) {
	switch (key) {
	case VK_RIGHT:
		player->x += player->speed;
		break;
	case VK_LEFT:
		player->x -= player->speed;
		break;
	case VK_UP:
		player->y += player->speed;
		break;
	case VK_DOWN:
		player->y -= player->speed;
		break;
	}

	printf("player: {%i, %i}", player->x, player->y);
}
