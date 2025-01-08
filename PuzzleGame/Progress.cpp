#include "Progress.h"
#include "IDs.h"

std::wstring failed_message;
Stage* currentStage; //当前场景状态
std::vector<NewMonster*>* current_new_monsters;
std::vector<Button*>* current_buttons;
std::vector<Button*>* buttons_before;
std::vector<Item*> items;		//物品列表
Item* current_item;	//当前物品
Item* show_name_item;
int item_name_fading_time;
Player* player;		//玩家
int current_reachable[20][28] = { 0 };
int current_bg[20][28] = { 0 };
int current_obj[20][28] = { 0 };
std::vector<NPC*>* current_npcs;

void UpdateTasks() {//顺便判断胜利和结束

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
		//完成任务

		if (npcs_house_1.at(0)->task_state == 0) {
			npcs_house_1.at(0)->ToConversation(1);
		}
		else if (npcs_house_1.at(0)->task_state == 2) {
			npcs_house_1.at(0)->ToConversation(3);
		}


		//如果没有item certificate再添加
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
				//没完成任务
				return;
			}
		}

		if (npcs_main.at(1)->task_state != 2) {
			npcs_main.at(1)->task_state = 2;
			npcs_main.at(1)->next_conversation_id = 0;
		}
	}

};