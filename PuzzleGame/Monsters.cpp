#include "Monsters.h"
#include "IDs.h"
#include "Resource.h"
#include "Windows.h"
#include <map>


int FRAMES_WALK[] = { 0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3, };
int FRAMES_WALK_COUNT = sizeof(FRAMES_WALK) / sizeof(int);

int FRAMES_HOLD[] = { 0,0,0,0,0, };
int FRAMES_HOLD_COUNT = sizeof(FRAMES_HOLD) / sizeof(int);

int FRAMES_HOME[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
int FRAMES_HOME_COUNT = sizeof(FRAMES_HOME) / sizeof(int);


std::map<int, HBITMAP> monster_hitmap = {
	{ MONSTER_DUCK_ID, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_DUCK))},
	{ MONSTER_CROW_ID, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_CROW))},
	{ MONSTER_CHIKEN_ID, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_CHIKEN))},
};

NewMonster* NewCreateMonster(int x, int y, int monster_id)
{
	NewMonster* monster = new NewMonster();
	monster->monsterID = monster_id;
	monster->visible = true;
	monster->move = true;
	monster->x = x;
	monster->y = y;
	monster->direction = UNIT_DIRECT_DOWN;
	monster->vx = 1;
	monster->vy = 1;
	monster->state = MONSTER_STATE_MOVE;
	monster->frame_row = monster->direction;
	monster->frame_column = 0;
	monster->frame_sequence = FRAMES_WALK;
	monster->frame_count = FRAMES_WALK_COUNT;
	monster->frame_id = 0;
	monster->time_count = -1;
	monster->time_max = 10; //强制初始化
	monster->hp_visible = false;

	switch (monster_id)
	{
	case MONSTER_CROW_ID:
	{
		monster->img = monster_hitmap[MONSTER_CROW_ID];
		monster->bmp_size_x = 64;
		monster->bmp_size_y = 64;
		monster->size_x = 30;
		monster->size_y = 30;
		monster->time_stop = 50;
		monster->time_max = 100;
		monster->hp_max = 2;
		monster->hp = monster->hp_max;
		break;
	}
	case MONSTER_DUCK_ID:
	{
		monster->img = monster_hitmap[MONSTER_DUCK_ID];
		monster->bmp_size_x = 16;
		monster->bmp_size_y = 16;
		monster->size_x = 30;
		monster->size_y = 30;
		monster->time_stop = 50;
		monster->time_max = 100;
		monster->hp_max = 5;
		monster->hp = monster->hp_max;
		break;
	}
	case MONSTER_CHIKEN_ID:
	{
		monster->img = monster_hitmap[MONSTER_CHIKEN_ID];
		monster->bmp_size_x = 16;
		monster->bmp_size_y = 16;
		monster->size_x = 30;
		monster->size_y = 30;
		monster->time_stop = 50;
		monster->time_max = 100;
		monster->hp_max = 5;
		monster->hp = monster->hp_max;
		break;
	}
	default:
		break;
	}


	return monster;
}

Effect* CreateEffect(int effect_id) {
	Effect* effect = new Effect();
	effect->effectID = effect_id;
	effect->life_count = 0;

	switch (effect_id)
	{
	case EFFECT_SPEED_UP_ID:
	{
		effect->life_max = 100;
		break;
	}
	default:
		break;
	}

	return effect;
}

void AddEffect(NewMonster* monster, int effect_id) {
	for (auto it = monster->effects.begin(); it != monster->effects.end(); it++) {
		if ((*it)->effectID == effect_id) {
			(*it)->life_count = 0;
			return;
		}
	}

	monster->effects.push_back(CreateEffect(EFFECT_SPEED_UP_ID));
}


std::vector<NewMonster*> new_monsters_main;
std::vector<NewMonster*> new_monsters_house_1;
std::vector<NewMonster*> new_monsters_meadow;
std::vector<NewMonster*> new_monsters_house_2;

void InitMonsters() {

	for (int i = 0; i < new_monsters_main.size(); i++) {
		delete new_monsters_main[i];
	}
	new_monsters_main.clear();

	for (int i = 0; i < new_monsters_house_1.size(); i++) {
		delete new_monsters_house_1[i];
	}
	new_monsters_house_1.clear();

	for (int i = 0; i < new_monsters_meadow.size(); i++) {
		delete new_monsters_meadow[i];
	}
	new_monsters_meadow.clear();

	for (int i = 0; i < new_monsters_house_2.size(); i++) {
		delete new_monsters_house_2[i];
	}
	new_monsters_house_2.clear();


	new_monsters_main.push_back(NewCreateMonster(505, 205, MONSTER_CROW_ID));
	new_monsters_main.push_back(NewCreateMonster(205, 405, MONSTER_CROW_ID));

	new_monsters_house_1.push_back(NewCreateMonster(300, 300, MONSTER_CHIKEN_ID));
	new_monsters_house_1.push_back(NewCreateMonster(350, 350, MONSTER_CHIKEN_ID));

	new_monsters_meadow.push_back(NewCreateMonster(405, 205, MONSTER_CROW_ID));
	new_monsters_meadow.push_back(NewCreateMonster(405, 305, MONSTER_CROW_ID));
	new_monsters_meadow.push_back(NewCreateMonster(505, 205, MONSTER_CROW_ID));
	new_monsters_meadow.push_back(NewCreateMonster(290, 290, MONSTER_DUCK_ID));
	new_monsters_meadow.push_back(NewCreateMonster(300, 300, MONSTER_DUCK_ID));
	new_monsters_meadow.push_back(NewCreateMonster(200, 200, MONSTER_DUCK_ID));
	new_monsters_meadow.push_back(NewCreateMonster(250, 250, MONSTER_DUCK_ID));

}