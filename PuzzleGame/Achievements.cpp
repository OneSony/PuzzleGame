#include <map>
#include <string>
#include "Achievements.h"
#include "Resource.h"
#include <iostream>
#include <fstream>

int ACHIEVE_WIDTH = 500;
int ACHIEVE_HEIGHT = 128;

std::map<int, HBITMAP> achievement_hitmap = {
	{ ACHIEVE_QUICK_SLEEP, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ACHIEVE_QUICK_SLEEP))},
	{ ACHIEVE_FRIENDLY, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ACHIEVE_FRIENDLY))},
	{ ACHIEVE_CROW_HUNTER, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ACHIEVE_CROW_HUNTER))},
	{ ACHIEVE_HELPFUL, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ACHIEVE_HELPFUL))},
};

Achievement::Achievement(int achieve_id) {
	this->achieve_id = achieve_id;

	switch (achieve_id)
	{
	case ACHIEVE_QUICK_SLEEP:
	{
		this->img = achievement_hitmap[ACHIEVE_QUICK_SLEEP];
		this->title = L"��������";
		this->description = L"�õ�Կ�����̾�ȥ˯��";
		break;
	}
	case ACHIEVE_CROW_HUNTER:
	{
		this->img = achievement_hitmap[ACHIEVE_CROW_HUNTER];
		this->title = L"��ѻ����";
		this->description = L"ɱ�����е���ѻ";
		break;
	}
	case ACHIEVE_FRIENDLY:
	{
		this->img = achievement_hitmap[ACHIEVE_FRIENDLY];
		this->title = L"��������";
		this->description = L"���˺��κ�һֻ����";
		break;
	}
	case ACHIEVE_HELPFUL:
	{
		this->img = achievement_hitmap[ACHIEVE_HELPFUL];
		this->title = L"��������";
		this->description = L"������������";
		break;
	}
	}
}

// ����ɾ�����
void saveAchievements(const std::map<int, bool>& achievements, const std::string& filename) {
	std::ofstream outFile(filename, std::ios::binary);
	if (!outFile) {
		std::cerr << "Error opening file for saving achievements!" << std::endl;
	}

	size_t size = achievements.size();
	outFile.write(reinterpret_cast<char*>(&size), sizeof(size)); // ����map�Ĵ�С

	// ����map��ÿһ��
	for (const auto& entry : achievements) {
		outFile.write(reinterpret_cast<const char*>(&entry.first), sizeof(entry.first)); // key
		outFile.write(reinterpret_cast<const char*>(&entry.second), sizeof(entry.second)); // value
	}

	outFile.close();
}

// ���سɾ�����
std::map<int, bool> loadAchievements(const std::string& filename) {
	std::map<int, bool> achievements;
	std::ifstream inFile(filename, std::ios::binary);

	if (!inFile) {
		std::cerr << "Error opening file for loading achievements!" << std::endl;
		return achievements;
	}

	size_t size;
	inFile.read(reinterpret_cast<char*>(&size), sizeof(size)); // ��ȡmap�Ĵ�С

	// ��ȡmap��ÿһ��
	for (size_t i = 0; i < size; ++i) {
		int key;
		bool value;
		inFile.read(reinterpret_cast<char*>(&key), sizeof(key));   // key
		inFile.read(reinterpret_cast<char*>(&value), sizeof(value)); // value
		achievements[key] = value;
	}

	inFile.close();
	return achievements;
}


std::map<int, bool> achievement_record;
std::map<int, bool> global_achievement_record;
std::list<Achievement*> achievement_list;
std::vector<Achievement*> global_achievements;

bool achievement_hurt_flag = false;


void InitAchievements() {

	std::map<int, bool> help_achievement_record = {
		{ACHIEVE_QUICK_SLEEP, false},
		{ACHIEVE_FRIENDLY, false},
		{ACHIEVE_CROW_HUNTER, false},
		{ACHIEVE_HELPFUL, false},
	};

	achievement_record = help_achievement_record;

	achievement_hurt_flag = false;

	while (!achievement_list.empty()) {
		delete achievement_list.front();
		achievement_list.pop_front();
	}
	achievement_list.clear();

	for (int i = 0; i < global_achievements.size(); i++) {
		delete global_achievements[i];
	}
	global_achievements.clear();

	global_achievements.push_back(new Achievement(ACHIEVE_QUICK_SLEEP));
	global_achievements.push_back(new Achievement(ACHIEVE_FRIENDLY));
	global_achievements.push_back(new Achievement(ACHIEVE_CROW_HUNTER));
	global_achievements.push_back(new Achievement(ACHIEVE_HELPFUL));


	global_achievement_record = loadAchievements(".achievements.dat");
}

void SummarizeAchievements() {


	if (progress_record[PRO_PEOPLE_KNOWN] == false) {
		achievement_record[ACHIEVE_QUICK_SLEEP] = true;
		global_achievement_record[ACHIEVE_QUICK_SLEEP] = true;
		achievement_list.push_back(new Achievement(ACHIEVE_QUICK_SLEEP));
	}

	if (achievement_hurt_flag == false) {
		achievement_record[ACHIEVE_FRIENDLY] = true;
		global_achievement_record[ACHIEVE_FRIENDLY] = true;
		achievement_list.push_back(new Achievement(ACHIEVE_FRIENDLY));
	}

	//ѭ������npcs������ѻ�ǲ��Ƕ�����
	std::vector<std::vector<NewMonster*>*> all_monsters;
	all_monsters.push_back(&new_monsters_main);
	all_monsters.push_back(&new_monsters_house_1);
	all_monsters.push_back(&new_monsters_meadow);
	all_monsters.push_back(&new_monsters_house_2);

	bool has_crow = false;
	for (int i = 0; i < all_monsters.size(); i++) {
		for (int j = 0; j < all_monsters[i]->size(); j++) {
			if ((*all_monsters[i])[j]->visible == true && (*all_monsters[i])[j]->monsterID == MONSTER_CROW_ID) {
				has_crow = true;
				break;
			}
		}
	}
	if (has_crow == false) {
		achievement_record[ACHIEVE_CROW_HUNTER] = true;
		global_achievement_record[ACHIEVE_CROW_HUNTER] = true;
		achievement_list.push_back(new Achievement(ACHIEVE_CROW_HUNTER));
	}


	if (progress_record[PRO_DUCK_HOMED] == true) {
		achievement_record[ACHIEVE_HELPFUL] = true;
		global_achievement_record[ACHIEVE_HELPFUL] = true;
		achievement_list.push_back(new Achievement(ACHIEVE_HELPFUL));
	}

	saveAchievements(global_achievement_record, ".achievements.dat");
}
