#pragma once
#include "Particles.h"
#include <vector>
#include <windows.h>

extern int FRAMES_WALK[];
extern int FRAMES_WALK_COUNT;

extern int FRAMES_HOLD[];
extern int FRAMES_HOLD_COUNT;

extern int FRAMES_HOME[];
extern int FRAMES_HOME_COUNT;


struct Effect {
	int effectID;
	int life_count;
	int life_max;
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

	std::vector<Particle*> particles;
	std::vector<FigParticle*> fig_particles;

	std::vector<Effect*> effects;

};



extern std::vector<NewMonster*> new_monsters_main;
extern std::vector<NewMonster*> new_monsters_house_1;
extern std::vector<NewMonster*> new_monsters_meadow;
extern std::vector<NewMonster*> new_monsters_house_2;

Effect* CreateEffect(int effect_id);
NewMonster* NewCreateMonster(int x, int y, int monster_id);

void AddEffect(NewMonster* monster, int effect_id);
void InitMonsters();