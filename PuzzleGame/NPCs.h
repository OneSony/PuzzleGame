#include "PuzzleGame.h"

// NPC结构体
struct NPC
{
	int npcID;				//NPC编号
	HBITMAP img;			//图片
	bool visible;			//该NPC是否可见

	int task_state;

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;	//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几帧

	int state;		//单位状态
	int direction;	//单位方向

	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	int health;		//生命值

	vector<vector<const wchar_t*>> conversations;

	vector<const wchar_t*> conversations_before;	//任务完成前NPC的台词
	vector<const wchar_t*> conversations_after;		//任务完成后NPC的台词
	int next_conversation_id;				//NPC下一次要说第几句台词
};

// 创建NPC
NPC* CreateNPC(int x, int y, int npc_id);
void InitNPCs();

extern std::vector<NPC*> npcs_main;
extern std::vector<NPC*> npcs_house_1;
extern std::vector<NPC*> npcs_meadow;
#pragma once
