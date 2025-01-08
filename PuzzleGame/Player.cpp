#include "Player.h"
#include "IDs.h"
#include "Resource.h"

int PLAYER_FRAMES_HOLD[] = { 0 };
int PLAYER_FRAMES_HOLD_COUNT = sizeof(PLAYER_FRAMES_HOLD) / sizeof(int);

HBITMAP bmp_player = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_PLAYER));

Player* CreatePlayer(int x, int y)
{
	Player* player = new Player();
	player->img = bmp_player;
	player->x = x;
	player->y = y;
	player->direction = UNIT_DIRECT_RIGHT;
	player->vx = 5;
	player->vy = 5;

	player->state = UNIT_STATE_HOLD;
	player->frame_row = player->direction;
	player->frame_column = 0;
	player->frame_sequence = PLAYER_FRAMES_HOLD;
	player->frame_count = PLAYER_FRAMES_HOLD_COUNT;
	player->frame_id = 0;

	return player;
}