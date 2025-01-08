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

		int current_progress = progress_list.back();  // ��ȡ���һ��Ԫ��
		progress_list.pop_back();  // ɾ�����һ��Ԫ��

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
					//�õ���֤��֮��������
					npcs_house_1.at(0)->ToConversation(2);
					progress_record[PRO_CHICKEN_UNHOMED_AGAIN] = true;
				}
			}
		}
		else if (current_progress == PRO_CHICKEN_HOMED) {
			//��һ�ν������״̬
			if (progress_record[PRO_CHICKEN_HOMED] == false) {
				progress_record[PRO_CHICKEN_HOMED] = true;

				//�������еĶԻ�
				npcs_house_1.at(0)->ToConversation(1);

			}
			else {
				//�ڶ��ν���
				if (progress_record[PRO_CHICKEN_UNHOMED_AGAIN] == true) {
					//��������߹��ֻ�����������
					npcs_house_1.at(0)->ToConversation(3);
				}
			}
		}
		else if (current_progress == PRO_GET_CERTIFICATE) {

			if (progress_record[PRO_GET_CERTIFICATE] == false) {
				progress_record[PRO_GET_CERTIFICATE] = true;
				//�����Ʒ
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

				//���µ�ͼ
				reachable_main[16][27] = 3;
				reachable_main[15][27] = 3;
				reachable_main[14][27] = 3;

				npcs_main.at(1)->x = BLOCK_SIZE_X * 26;
				npcs_main.at(1)->y = BLOCK_SIZE_Y * 13;

				//TODO �ж�һ�����λ��


				//����npc�Ի�
				npcs_meadow.at(0)->ToConversation(0);

			}
			else {

			}

		}
		else if (current_progress == PRO_GET_BOW) {

			if (progress_record[PRO_GET_BOW] == false) {
				progress_record[PRO_GET_BOW] = true;
				//������
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