#pragma once
#include "Particles.h"
#include <vector>
#include <string>
#include <windows.h>
#include <map>
// NPC�ṹ��
class NPC
{
public:
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

	int size_x;
	int size_y;

	std::vector<std::vector<const wchar_t*>> conversations;

	std::vector<const wchar_t*> conversations_before;	//�������ǰNPC��̨��
	std::vector<const wchar_t*> conversations_after;		//������ɺ�NPC��̨��
	int next_conversation_id;				//NPC��һ��Ҫ˵�ڼ���̨��
	bool is_finished = false;

	std::vector<FigParticle*> fig_particles;

	NPC(int x, int y, int npc_id);
	void AddFigParticle(int particle_id);
	void RemoveFigParticle(int particle_id);
	void ToConversation(int conversation_id);
};

void InitNPCs();

extern std::vector<NPC*> npcs_main;
extern std::vector<NPC*> npcs_house_1;
extern std::vector<NPC*> npcs_meadow;
extern std::vector<NPC*> npcs_house_2;
#pragma once
