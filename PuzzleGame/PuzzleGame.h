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
#pragma comment(lib, "Msimg32.lib")			//ͼ����ĺ����ӿڣ����磺͸��ɫ��λͼ�Ļ���TransparentBlt����
using namespace std;
#pragma endregion

#pragma region �궨��

const double PI = 3.14159265358979323846;

#define WINDOW_TITLEBARHEIGHT	32			//�������߶�
#define WINDOW_WIDTH			896+16		//��Ϸ���ڿ��
#define WINDOW_HEIGHT			640+32		//��Ϸ���ڸ߶�

#define STAGE_STARTMENU			0		//��ʼ�����ID
#define STAGE_1					1		//��һ����Ϸ������ID
#define STAGE_2					2


//�ߴ�
#define BG_BITMAP_WIDTH			240		//����ͼƬ��λͼ���
#define BG_BITMAP_HEIGHT		160		//����ͼƬ��λͼ�߶�
#define BG_COLUMNS				28		//��������
#define BG_ROWS					20		//��������
#define HUMAN_SIZE_X			38		//��������Ļ�ϵĿ��
#define HUMAN_SIZE_Y			52		
#define HUMAN_BITMAP_SIZE_X		19		//������λͼ�ϵĿ��
#define HUMAN_BITMAP_SIZE_Y		26		
#define BLOCK_SIZE_X			32		//������������Ļ�ϵĿ��
#define BLOCK_SIZE_Y			32		//������������Ļ�ϵĸ߶�
#define BLOCK_BITMAP_SIZE_X		16		//��ͼ����λͼ�ϵĿ��
#define BLOCK_BITMAP_SIZE_Y		16
#define DIALOG_SIZE_X			896		//�Ի��򱳾�
#define DIALOG_SIZE_Y			120
#define DIALOG_BITMAP_SIZE_X	250
#define DIALOG_BITMAP_SIZE_Y	44
#define MOSTER_SIZE_X			28		//����
#define MOSTER_SIZE_Y			30
#define MOSTER_BITMAP_SIZE_X	14
#define MOSTER_BITMAP_SIZE_Y	15
#define NEW_MOSTER_BITMAP_SIZE_X	64
#define NEW_MOSTER_BITMAP_SIZE_Y	64
#define NEW_MOSTER_SIZE_X			30		//����
#define NEW_MOSTER_SIZE_Y			30
#define HP_WIDTH					30		//��������
#define HP_HEIGHT					5		//��������


//��λ״̬����
#define UNIT_STATE_HOLD			0		//��ֹ
#define UNIT_STATE_WALK			1		//����
#define UNIT_STATE_ATTACK		2		//����

//��λ������
#define UNIT_DIRECT_RIGHT		1		//����
#define UNIT_DIRECT_LEFT		3		//����
#define UNIT_DIRECT_UP			2		//����
#define UNIT_DIRECT_DOWN		0		//����

//��������
#define BUTTON_STARTGAME			1001	//��ʼ��Ϸ��ťID
#define BUTTON_WIDTH		212		//��ʼ��Ϸ��ť���
#define BUTTON_HEIGHT		76		//��ʼ��Ϸ��ť�߶�


#define BUTTON_HELP			1002	//��ʼ��Ϸ��ťID
#define BUTTON_STOP_CONTINUE 1003
#define BUTTON_STOP_HELP	1004
#define BUTTON_STOP_HOME	1005

#define TIMER_GAMETIMER				1		//��Ϸ��Ĭ�ϼ�ʱ��ID
#define TIMER_GAMETIMER_ELAPSE		30		//Ĭ�ϼ�ʱ��ˢ�¼���ĺ�����
#define UNIT_SPEED					3.0		//��λ�����ٶ�

#define NPC_MAN1_ID				2001		//ÿ��NPC��ID��
#define NPC_WOMAN1_ID			2002

#define MONSTER_CAT_ID			3001
#define MONSTER_CROW_ID			3002
#define MONSTER_DUCK_ID			3003
#define MONSTER_CHIKEN_ID			3004


#define WEAPON_SWORD_ID			4001


#define LAND_GRASS_ID				5001	
#define LAND_DIRT_ID			5002

#define EFFECT_SPEED_UP_ID		6001

#define MONSTER_STATE_MOVE		10001
#define MONSTER_STATE_STOP		10002

///

#pragma endregion


#pragma region �ṹ������

// �����ṹ��
struct Stage
{
	int stageID;		//�������
	HBITMAP bg;			//����ͼƬ
	int timeCountDown;	//��Ϸʱ�䵹��ʱ
	bool timerOn;		//��ʱ���Ƿ����У���Ϸ�Ƿ���ͣ��

};


// ��ť�ṹ��
struct Button
{
	int buttonID;	//��ť���
	bool visible;	//��ť�Ƿ�ɼ�
	HBITMAP img;	//ͼƬ
	int x;			//����x
	int y;			//����y
	int width;		//���
	int height;		//�߶�
	wstring text;          // ������ʾ��ť�ϵ�����
};

struct Land
{
	bool passable;

	int landID;

	int x;
	int y;

	int size_x;
	int size_y;

	int bmp_size_x;
	int bmp_size_y;

	int bmp_row;
	int bmp_col;

	bool animated;
	int* frame_sequence;
	int frame_count;
	int frame_id;
};

struct Particle
{

	int offset_x;
	int offset_y;
	int vx;
	int vy;
	int life_max;
	int life_count;

	wstring text;
};

struct Effect {
	int effectID;
	int life_count;
	int life_max;
};

struct Weapon
{
	int weaponID;	//�������
	HBITMAP img;	//ͼƬ
	bool move;

	int bmp_size_x;
	int bmp_size_y;

	int size_x;
	int size_y;

	int bmp_row;
	int bmp_col;

	int damage;		//�˺�ֵ
};

// NPC�ṹ��
struct NPC
{
	int npcID;				//NPC���
	HBITMAP img;			//ͼƬ
	bool visible;			//��NPC�Ƿ�ɼ�
	bool task_complete;		//��npc�������Ƿ���ɡ���������npc�Ի�ʱ����˵ʲô���Լ�������Ϊ

	int frame_row;			//��ǰ��ʾ����ͼ��ĵڼ���
	int frame_column;		//��ǰ��ʾ����ͼ��ĵڼ���

	int* frame_sequence;	//��ǰ��֡����
	int frame_count;		//֡���еĳ���
	int frame_id;			//��ǰ��ʾ����֡���еĵڼ�֡

	int state;		//��λ״̬
	int direction;	//��λ����

	int x;			//����x
	int y;			//����y
	double vx;		//�ٶ�x
	double vy;		//�ٶ�y
	int health;		//����ֵ

	vector<const wchar_t*> conversations_before;	//�������ǰNPC��̨��
	vector<const wchar_t*> conversations_after;		//������ɺ�NPC��̨��
	int next_conversation_id;				//NPC��һ��Ҫ˵�ڼ���̨��
};

// ��ҽṹ��
struct Player
{
	HBITMAP img;	//ͼƬ

	int frame_row;			//��ǰ��ʾ����ͼ��ĵڼ���
	int frame_column;		//��ǰ��ʾ����ͼ��ĵڼ���

	int* frame_sequence;	//��ǰ��֡����
	int frame_count;		//֡���еĳ���
	int frame_id;			//��ǰ��ʾ����֡���еĵڼ�֡

	int state;		//��λ״̬
	int direction;	//��λ����

	int x;			//����x
	int y;			//����y
	double vx;		//�ٶ�x
	double vy;		//�ٶ�y
	int health;		//����ֵ

	Weapon* weapon;	//����
};
// ����ṹ��
struct Monster
{
	int monsterID;			//������
	HBITMAP img;			//ͼƬ
	bool visible;			//�Ƿ�ɼ�
	bool task_complete;		//�����Ƿ����
	bool move;				//�Ƿ�����ƶ�

	int frame_row;			//��ǰ��ʾ����ͼ��ĵڼ���
	int frame_column;		//��ǰ��ʾ����ͼ��ĵڼ���

	int* frame_sequence;	//��ǰ��֡����
	int frame_count;		//֡���еĳ���
	int frame_id;			//��ǰ��ʾ����֡���еĵڼ�֡

	int state;		//��λ״̬
	int direction;	//��λ����

	int x;			//����x
	int y;			//����y
	double vx;		//�ٶ�x
	double vy;		//�ٶ�y
	int health;		//����ֵ


	vector<const wchar_t*> conversations_before;	//�������ǰ��̨��
	vector<const wchar_t*> conversations_after;		//������ɺ��̨��
	int next_conversation_id;						//��һ��Ҫ˵�ڼ���̨��
};


// ����ṹ��
struct NewMonster
{
	int monsterID;			//������
	HBITMAP img;			//ͼƬ
	bool visible;			//�Ƿ�ɼ�
	bool move;				//�Ƿ�����ƶ�
	bool hurt;

	int frame_row;			//��ǰ��ʾ����ͼ��ĵڼ���
	int frame_column;		//��ǰ��ʾ����ͼ��ĵڼ���

	int* frame_sequence;	//��ǰ��֡����
	int frame_count;		//֡���еĳ���
	int frame_id;			//��ǰ��ʾ����֡���еĵڼ�֡

	double hp;
	double hp_max;
	bool hp_visible;

	int state;		//��λ״̬
	int direction;	//��λ����

	int x;			//����x
	int y;			//����y
	double vx;		//�ٶ�x
	double vy;		//�ٶ�y
	int health;		//����ֵ

	int bmp_size_x;
	int bmp_size_y;

	int size_x;
	int size_y;

	//�������
	int time_count;
	int time_stop;
	int time_max;

	vector<Particle*> particles;

	vector<Effect*> effects;

};


struct Drawable {
	HBITMAP img;      // ͼ����
	int x, y;       // ͼ��������Ͻ�
	int size_x, size_y; // ���Ƴߴ�
	int bmp_x, bmp_y; // λͼ����ʼ���Ƶ�
	int bmp_size_x, bmp_size_y; // λͼ����ʼ���Ƶ�
	COLORREF transparentColor; // ͸��ɫ
	vector<Drawable*> subdrawables; // ��һ��ͼ��
};



//TODO: �����Ϸ��Ҫ�ĸ��������ݣ����ש��ȣ�


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

void AddEffect(NewMonster* monster, int effect_id);

// �������ɿ��¼�������
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ��ʱ���¼�������
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region ������Ϸ״̬����������

// ��Ӱ�ť����
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y, wstring text);

Particle* CreateParticle(wstring text);

Effect* CreateEffect(int effect_id);

// ��ӵ�λ����
Player* CreatePlayer(int x, int y);
Weapon* CreateWeapon(int weapon_id);
NPC* CreateNPC(int x, int y, int npc_id);
Monster* CreateMonster(int x, int y, int monster_id);

Land* CreateLand(int land_id);


// ��ʼ����������
void InitStage(HWND hWnd, int stageID);


//��Ϊ�ͽ���������update***�ڶ�ʱ���¼����Թ̶�Ƶ�ʵ��ã�handle***�ڷ�������/����¼�ʱ����
void UpdatePlayer(HWND hWnd);
void UpdateNPCs(HWND hWnd);
void UpdateMonsters(HWND hWnd);
void UpdateMaps(HWND hWnd);

void HandleConversationEvents(HWND hWnd);
void HandleStopEvents(HWND hWnd);

void HandleHelpEvents(HWND hWnd);

//TODO: �����Ϸ��Ҫ�ĸ��ຯ��


#pragma endregion 


#pragma region ��ͼ��������

// ��ͼ����
void Paint(HWND hWnd);

#pragma endregion
