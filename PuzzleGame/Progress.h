#pragma once
#include <string>
#include <vector>
#include <list>
#include "Windows.h"
#include "Player.h"
#include "Items.h"
#include "Monsters.h"
#include "NPCs.h"
#include "Buttons.h"
#include "Maps.h"

#define PRO_INIT 100000
#define PRO_CHICKEN_UNHOMED 100001
#define PRO_CHICKEN_HOMED 100002
#define PRO_GET_CERTIFICATE 100003
#define PRO_CHICKEN_UNHOMED_AGAIN 100004
#define PRO_GET_KEY 100005
#define PRO_PEOPLE_KNOWN 110001 //大家知道了
#define PRO_GET_BOW		120000
#define PRO_DUCK_UNHOMED 120001
#define PRO_DUCK_HOMED 120002

struct Stage
{
	int stageID;		//场景编号
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）
};

void UpdateProgress();
void InitProgress();
extern std::list<int> progress_list;
extern std::map<int, bool> progress_record;