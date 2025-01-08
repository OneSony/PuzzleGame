#define _CRT_SECURE_NO_WARNINGS
#include "Progress.h"
#include "IDs.h"
#include <map>
#include "PuzzleGame.h"


std::map<int, bool> progress_record;
std::list<int> progress_list;

void InitProgress() {
	progress_list.clear();
	progress_list.push_back(PRO_INIT);

	std::map<int, bool> help_progress_record = {
		{PRO_INIT, false},
		{PRO_CHICKEN_UNHOMED, false},
		{PRO_CHICKEN_HOMED, false},
		{PRO_PEOPLE_KNOWN, false},
		{PRO_DUCK_UNHOMED, false},
		{PRO_DUCK_HOMED, false},
		{PRO_GET_CERTIFICATE, false},
		{PRO_GET_BOW, false},
		{PRO_CHICKEN_UNHOMED_AGAIN,false},
	};

	progress_record = help_progress_record;
}

void UpdateProgress() {

	while(!progress_list.empty()){

		int current_progress = progress_list.back();  // 获取最后一个元素
		progress_list.pop_back();  // 删除最后一个元素

		char buff[256];
		sprintf(buff, "in progress %d\n", current_progress);
		OutputDebugStringA(buff);

		if (current_progress == PRO_INIT) {
			if (progress_record[PRO_INIT] == false) {
				progress_record[PRO_INIT] = true;
				npcs_main.at(0)->ToConversation(0);
			}
			else {

			}
		}
		else if (current_progress == PRO_CHICKEN_UNHOMED) {
			if (progress_record[PRO_CHICKEN_UNHOMED] == false) {
				progress_record[PRO_CHICKEN_UNHOMED] = true;
				npcs_house_1.at(0)->ToConversation(0);
			}
			else {
				if (progress_record[PRO_GET_CERTIFICATE] == true) {
					//拿到了证书之后鸡在外面
					npcs_house_1.at(0)->ToConversation(2);
					progress_record[PRO_CHICKEN_UNHOMED_AGAIN] = true;
				}
			}
		}
		else if (current_progress == PRO_CHICKEN_HOMED) {
			//第一次进入这个状态
			if (progress_record[PRO_CHICKEN_HOMED] == false) {
				progress_record[PRO_CHICKEN_HOMED] = true;

				//更新所有的对话
				npcs_house_1.at(0)->ToConversation(1);

			}
			else {
				//第二次进入
				if (progress_record[PRO_CHICKEN_UNHOMED_AGAIN] == true) {
					//如果鸡出走过又回来进入这里
					npcs_house_1.at(0)->ToConversation(3);
				}
			}
		}
		else if (current_progress == PRO_GET_CERTIFICATE) {

			if (progress_record[PRO_GET_CERTIFICATE] == false) {
				progress_record[PRO_GET_CERTIFICATE] = true;
				//添加物品
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
			}
			else {


			}
		}
		else if (current_progress == PRO_PEOPLE_KNOWN) {

			if (progress_record[PRO_PEOPLE_KNOWN] == false) {
				progress_record[PRO_PEOPLE_KNOWN] = true;

				//更新地图
				reachable_main[16][27] = 3;
				reachable_main[15][27] = 3;
				reachable_main[14][27] = 3;

				npcs_main.at(1)->x = BLOCK_SIZE_X * 26;
				npcs_main.at(1)->y = BLOCK_SIZE_Y * 13;

				//TODO 判断一下玩家位置


				//更新npc对话
				npcs_meadow.at(0)->ToConversation(0);

			}
			else {

			}

		}
		else if (current_progress == PRO_GET_BOW) {

			if (progress_record[PRO_GET_BOW] == false) {
				progress_record[PRO_GET_BOW] = true;
				//给弓箭
				bool has_bow = false;
				for (const auto& item : items) {
					if (item->item_id == ITEM_BOW) {
						has_bow = true;
						break;
					}
				}
				if (!has_bow) {
					items.push_back(new Item(ITEM_BOW));
					show_name_item = items.back();
					item_name_fading_time = ITEM_NAME_FADING;
				}
			}
			else {

			}

		}
		else if (current_progress == PRO_DUCK_UNHOMED) {

			if (progress_record[PRO_DUCK_UNHOMED] == false) {
				progress_record[PRO_DUCK_UNHOMED] = true;

			}
			else {

			}
		}
		else if (current_progress == PRO_DUCK_HOMED) {

			if (progress_record[PRO_DUCK_HOMED] == false) {
				progress_record[PRO_DUCK_HOMED] = true;

				npcs_meadow.at(0)->ToConversation(1);
				npcs_main.at(1)->ToConversation(2);
			}
			else {

			}
		}

	}

}