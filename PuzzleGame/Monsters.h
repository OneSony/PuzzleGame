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