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
#define PRO_PEOPLE_KNOWN 110001 //���֪����
#define PRO_GET_BOW		120000
#define PRO_DUCK_UNHOMED 120001
#define PRO_DUCK_HOMED 120002

struct Stage
{
	int stageID;		//�������
	int timeCountDown;	//��Ϸʱ�䵹��ʱ
	bool timerOn;		//��ʱ���Ƿ����У���Ϸ�Ƿ���ͣ��
};

void UpdateProgress();
void InitProgress();
extern std::list<int> progress_list;
extern std::map<int, bool> progress_record;