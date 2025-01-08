#pragma once
#include "PuzzleGame.h"
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

// 怪物结构体
struct NewMonster
{
	int monsterID;			//怪物编号
	HBITMAP img;			//图片
	bool visible;			//是否可见
	bool move;				//是否可以移动
	bool hurt;

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;	//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几帧

	double hp;
	double hp_max;
	bool hp_visible;

	int state;		//单位状态
	int direction;	//单位方向

	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	int health;		//生命值

	int bmp_size_x;
	int bmp_size_y;

	int size_x;
	int size_y;

	//动画相关
	int time_count;
	int time_stop;
	int time_max;

	vector<Particle*> particles;

	vector<Effect*> effects;

};



extern vector<NewMonster*> new_monsters_main;
extern vector<NewMonster*> new_monsters_house_1;
extern vector<NewMonster*> new_monsters_meadow;


Particle* CreateParticle(wstring text);
Effect* CreateEffect(int effect_id);
NewMonster* NewCreateMonster(int x, int y, int monster_id);

void AddEffect(NewMonster* monster, int effect_id);
void InitMonsters();