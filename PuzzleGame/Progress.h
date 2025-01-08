#pragma once
#include <string>
#include <vector>
#include "Windows.h"
#include "Player.h"
#include "Items.h"
#include "Monsters.h"
#include "NPCs.h"
#include "Buttons.h"
#include "Maps.h"


// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）
};


void UpdateTasks();

extern std::wstring failed_message;
extern Stage* currentStage; //当前场景状态
extern std::vector<NewMonster*>* current_new_monsters;
extern std::vector<Button*>* current_buttons;
extern std::vector<Button*>* buttons_before;
extern std::vector<Item*> items;		//物品列表
extern Item* current_item;	//当前物品
extern Item* show_name_item;
extern int item_name_fading_time;
extern Player* player;		//玩家
extern int current_reachable[20][28];
extern int current_bg[20][28];
extern int current_obj[20][28];
extern std::vector<NPC*>* current_npcs;