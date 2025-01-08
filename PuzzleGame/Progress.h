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


// �����ṹ��
struct Stage
{
	int stageID;		//�������
	int timeCountDown;	//��Ϸʱ�䵹��ʱ
	bool timerOn;		//��ʱ���Ƿ����У���Ϸ�Ƿ���ͣ��
};


void UpdateTasks();

extern std::wstring failed_message;
extern Stage* currentStage; //��ǰ����״̬
extern std::vector<NewMonster*>* current_new_monsters;
extern std::vector<Button*>* current_buttons;
extern std::vector<Button*>* buttons_before;
extern std::vector<Item*> items;		//��Ʒ�б�
extern Item* current_item;	//��ǰ��Ʒ
extern Item* show_name_item;
extern int item_name_fading_time;
extern Player* player;		//���
extern int current_reachable[20][28];
extern int current_bg[20][28];
extern int current_obj[20][28];
extern std::vector<NPC*>* current_npcs;