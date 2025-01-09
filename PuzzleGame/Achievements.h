#pragma once
#include "Progress.h"
#include "Monsters.h"
#include "IDs.h"


extern int ACHIEVE_WIDTH;
extern int ACHIEVE_HEIGHT;

class Achievement {
public:
	int achieve_id;
	HBITMAP img;

	int size_x = 64;
	int size_y = 64;

	int bitmap_size_x = 16;
	int bitmap_size_y = 16;

	std::wstring title;
	std::wstring description;

	Achievement(int achieve_id);
};

extern std::map<int, bool> achievement_record;
extern std::list<Achievement*> achievement_list;
extern std::map<int, bool> global_achievement_record;
extern std::vector<Achievement*> global_achievements;
extern bool achievement_hurt_flag;

void InitAchievements();
void SummarizeAchievements();