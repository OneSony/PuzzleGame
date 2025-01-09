#pragma once

#pragma region ͷ�ļ�����
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <string>
#include <random>
#include <unordered_set>
#include "resource.h"
#include "IDs.h"
#include "Buttons.h"
#include "Monsters.h"
#include "Items.h"
#include "NPCs.h"
#include "Maps.h"
#include "Player.h"
#include "Progress.h"
#include "Achievements.h"
#pragma comment(lib, "Msimg32.lib")			//ͼ����ĺ����ӿڣ����磺͸��ɫ��λͼ�Ļ���TransparentBlt����
using namespace std;
#pragma endregion

#pragma region �궨��

const double PI = 3.14159265358979323846;


#pragma endregion


#pragma region �ṹ������

struct Drawable {
	bool visible = true;
	HBITMAP img;      // ͼ����
	int x, y;       // ͼ��������Ͻ�
	int size_x, size_y; // ���Ƴߴ�
	int bmp_x, bmp_y; // λͼ����ʼ���Ƶ�
	int bmp_size_x, bmp_size_y; // λͼ����ʼ���Ƶ�
	int weight_x, weight_y; // �Ƚ�ʱ��
	COLORREF transparentColor; // ͸��ɫ
	vector<Drawable*> subdrawables; // ��һ��ͼ��
};

#pragma endregion


#pragma region �¼�����������


// ��ʼ����Ϸ���庯��
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ���̰����¼�������
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �����ɿ��¼�������
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ����ƶ��¼�������
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �����������¼�������
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �������ɿ��¼�������
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ��ʱ���¼�������
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region ������Ϸ״̬����������


// ��ʼ����������
void InitStage(HWND hWnd, int stageID);
void InitCurrent();
void AllInit();


//��Ϊ�ͽ���������update***�ڶ�ʱ���¼����Թ̶�Ƶ�ʵ��ã�handle***�ڷ�������/����¼�ʱ����
void UpdatePlayer(HWND hWnd);
void UpdateNPCs(HWND hWnd);
void UpdateMonsters(HWND hWnd);
void UpdateMaps(HWND hWnd);
void UpdateHolding(HWND hWnd);
void ScanTasks(HWND hWnd);

void HandleConversationEvents(HWND hWnd);
void HandleStopEvents(HWND hWnd);
void HandleHelpEvents(HWND hWnd);
void HandleFailedEvents(HWND hWnd, std::wstring str);
void HandleBedEvents(HWND hWnd);
void HandleGlobalAchievementEvents(HWND hWnd);


#pragma endregion 


#pragma region ��ͼ��������

// ��ͼ����
void Paint(HWND hWnd);

#pragma endregion

#pragma region ʵʱ״̬����
extern std::wstring failed_message;
extern Stage* currentStage; //��ǰ����״̬
extern std::vector<NewMonster*>* current_new_monsters;
extern std::vector<Button*>* current_buttons;
extern std::list<std::vector<Button*>*> buttons_before;
extern std::vector<Item*> items;		//��Ʒ�б�
extern Item* current_item;	//��ǰ��Ʒ
extern Item* show_name_item;
extern int item_name_fading_time;
extern Player* player;		//���
extern int (*current_reachable)[20][28];
extern int (*current_bg)[20][28];
extern int (*current_obj)[20][28];
extern std::vector<NPC*>* current_npcs;
#pragma endregion