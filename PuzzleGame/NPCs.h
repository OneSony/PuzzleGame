#include "PuzzleGame.h"

// NPC�ṹ��
struct NPC
{
	int npcID;				//NPC���
	HBITMAP img;			//ͼƬ
	bool visible;			//��NPC�Ƿ�ɼ�

	int task_state;

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

	vector<vector<const wchar_t*>> conversations;

	vector<const wchar_t*> conversations_before;	//�������ǰNPC��̨��
	vector<const wchar_t*> conversations_after;		//������ɺ�NPC��̨��
	int next_conversation_id;				//NPC��һ��Ҫ˵�ڼ���̨��
};

// ����NPC
NPC* CreateNPC(int x, int y, int npc_id);
void InitNPCs();

extern std::vector<NPC*> npcs_main;
extern std::vector<NPC*> npcs_house_1;
extern std::vector<NPC*> npcs_meadow;
#pragma once
