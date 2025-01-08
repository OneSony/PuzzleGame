#include "Progress.h"
#include "IDs.h"

std::wstring failed_message;
Stage* currentStage; //��ǰ����״̬
std::vector<NewMonster*>* current_new_monsters;
std::vector<Button*>* current_buttons;
std::vector<Button*>* buttons_before;
std::vector<Item*> items;		//��Ʒ�б�
Item* current_item;	//��ǰ��Ʒ
Item* show_name_item;
int item_name_fading_time;
Player* player;		//���
int current_reachable[20][28] = { 0 };
int current_bg[20][28] = { 0 };
int current_obj[20][28] = { 0 };
std::vector<NPC*>* current_npcs;

void UpdateTasks() {//˳���ж�ʤ���ͽ���

	if (currentStage->stageID == STAGE_1) {

	}
	else if (currentStage->stageID == STAGE_HOUSE_1) {
		for (int i = 0; i < current_new_monsters->size(); i++) {
			if ((*current_new_monsters)[i]->visible == false) {
				continue;
			}

			if ((*current_new_monsters)[i]->state != MONSTER_STATE_HOME) {
				if (npcs_house_1.at(0)->task_state == 1 || npcs_house_1.at(0)->task_state == 3) {
					npcs_house_1.at(0)->ToConversation(2);
				}
				return;
			}
		}
		//�������

		if (npcs_house_1.at(0)->task_state == 0) {
			npcs_house_1.at(0)->ToConversation(1);
		}
		else if (npcs_house_1.at(0)->task_state == 2) {
			npcs_house_1.at(0)->ToConversation(3);
		}


		//���û��item certificate�����
		bool has_certificate = false;
		for (const auto& item : items) {
			if (item->item_id == ITEM_CERTIFICATE) {
				has_certificate = true;
				break;
			}
		}
		if (!has_certificate) {
			items.push_back(new Item(ITEM_CERTIFICATE));
			show_name_item = items.back();
			item_name_fading_time = ITEM_NAME_FADING;
		}


		reachable_main[16][27] = 3;
		reachable_main[15][27] = 3;
		reachable_main[14][27] = 3;
	}
	else if (currentStage->stageID == STAGE_MEADOW) {
		for (int i = 0; i < current_new_monsters->size(); i++) {
			if ((*current_new_monsters)[i]->visible == false) {
				continue;
			}
			if (((*current_new_monsters)[i]->monsterID == MONSTER_DUCK_ID && (*current_new_monsters)[i]->state != MONSTER_STATE_HOME) || ((*current_new_monsters)[i]->monsterID == MONSTER_CROW_ID && (*current_new_monsters)[i]->state == MONSTER_STATE_HOME)) {
				//û�������
				return;
			}
		}

		if (npcs_main.at(1)->task_state != 2) {
			npcs_main.at(1)->task_state = 2;
			npcs_main.at(1)->next_conversation_id = 0;
		}
	}

};