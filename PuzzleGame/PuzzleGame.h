#pragma once

#pragma region 头文件引用

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
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数
using namespace std;
#pragma endregion

#pragma region 宏定义

const double PI = 3.14159265358979323846;

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			896+16		//游戏窗口宽度
#define WINDOW_HEIGHT			640+32		//游戏窗口高度

#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的ID
#define STAGE_HOUSE_1			2
#define STAGE_MEADOW			3


//尺寸
#define BG_BITMAP_WIDTH			240		//背景图片的位图宽度
#define BG_BITMAP_HEIGHT		160		//背景图片的位图高度
#define BG_COLUMNS				28		//背景列数
#define BG_ROWS					20		//背景行数
#define HUMAN_SIZE_X			38		//人物在屏幕上的宽度
#define HUMAN_SIZE_Y			52		
#define HUMAN_BITMAP_SIZE_X		19		//人物在位图上的宽度
#define HUMAN_BITMAP_SIZE_Y		26		
#define BLOCK_SIZE_X			32		//背景单格在屏幕上的宽度
#define BLOCK_SIZE_Y			32		//背景单格在屏幕上的高度
#define BLOCK_BITMAP_SIZE_X		16		//地图块在位图上的宽度
#define BLOCK_BITMAP_SIZE_Y		16
#define DIALOG_SIZE_X			896		//对话框背景
#define DIALOG_SIZE_Y			120
#define DIALOG_BITMAP_SIZE_X	250
#define DIALOG_BITMAP_SIZE_Y	44
#define MOSTER_SIZE_X			28		//怪物
#define MOSTER_SIZE_Y			30
#define MOSTER_BITMAP_SIZE_X	14
#define MOSTER_BITMAP_SIZE_Y	15
#define NEW_MOSTER_BITMAP_SIZE_X	64
#define NEW_MOSTER_BITMAP_SIZE_Y	64
#define NEW_MOSTER_SIZE_X			30		//怪物
#define NEW_MOSTER_SIZE_Y			30
#define HP_WIDTH					30		//背景行数
#define HP_HEIGHT					5		//背景行数


//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_WALK			1		//行走
#define UNIT_STATE_ATTACK		2		//攻击

//单位方向定义
#define UNIT_DIRECT_RIGHT		1		//向右
#define UNIT_DIRECT_LEFT		3		//向左
#define UNIT_DIRECT_UP			2		//向上
#define UNIT_DIRECT_DOWN		0		//向下

//其它定义
#define BUTTON_STARTGAME			1001	//开始游戏按钮ID
#define BUTTON_WIDTH		212		//开始游戏按钮宽度
#define BUTTON_HEIGHT		76		//开始游戏按钮高度


#define BUTTON_HELP			1002	//开始游戏按钮ID
#define BUTTON_STOP_CONTINUE 1003
#define BUTTON_STOP_HELP	1004
#define BUTTON_STOP_HOME	1005

#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		30		//默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					3.0		//单位行走速度

#define NPC_MAN1_ID				2001		//每个NPC的ID号
#define NPC_WOMAN1_ID			2002
#define NPC_MAN2_ID				2003
#define NPC_WEADOW_MAN_ID			2004

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
#define MONSTER_STATE_HOME		10003

#define OBJ_TREE 20001
#define OBJ_HOUSE_1 20002
#define OBJ_HOUSE_2 20003
#define OBJ_HOUSE_3 20004
#define OBJ_BAR_H_LEFT 20005
#define OBJ_BAR_H_MID 20006
#define OBJ_BAR_H_RIGHT 20007
#define OBJ_BAR_V_HEAD 20008
#define OBJ_BAR_V_TAIL 20009
#define OBJ_WALL_1 20010
#define OBJ_TABLE_1 20011
#define OBJ_CHAIR_1 20012
#define OBJ_SOFA_1 20013
#define OBJ_TV 20014
#define OBJ_CARPET_1 20015


#define MAP_MAIN 30001

#define BG_BLACK 40000
#define BG_GRASS 40001
#define BG_SAND 40002
#define BG_FLOOR_1 40003
#define BG_BARRIER_LEFT 40004
#define BG_BARRIER_RIGHT 40005
#define BG_BARRIER_TOP 40006
#define BG_BARRIER_BOTTOM 40007
#define BG_BARRIER_LEFT_TOP 40008
#define BG_BARRIER_LEFT_BOTTOM 40009
#define BG_BARRIER_RIGHT_TOP 40010	
#define BG_BARRIER_RIGHT_BOTTOM 40011
#define BG_BARRIER_LEFT_TOP_R 40012
#define BG_BARRIER_LEFT_BOTTOM_R 40013
#define BG_BARRIER_RIGHT_TOP_R 40014
#define BG_BARRIER_RIGHT_BOTTOM_R 40015


//帧
extern int PLAYER_FRAMES_HOLD[];
extern int PLAYER_FRAMES_HOLD_COUNT;
extern int NPC_FRAMES_HOLD[];
extern int NPC_FRAMES_HOLD_COUNT;
extern int FRAMES_WALK[];
extern int FRAMES_HOLD[];
extern int FRAMES_HOLD_COUNT;
extern int FRAMES_HOME[];
extern int FRAMES_HOME_COUNT;
extern int FRAMES_WALK_COUNT;
extern int MONSTER_FRAMES[];
extern int MONSTER_FRAMES_COUNT;


///

#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）

};


// 按钮结构体
struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
	wstring text;          // 用于显示按钮上的文字
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
	int weaponID;	//武器编号
	HBITMAP img;	//图片
	bool move;

	int bmp_size_x;
	int bmp_size_y;

	int size_x;
	int size_y;

	int bmp_row;
	int bmp_col;

	int damage;		//伤害值
};

// 玩家结构体
struct Player
{
	HBITMAP img;	//图片

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

	Weapon* weapon;	//武器
};
// 怪物结构体
struct Monster
{
	int monsterID;			//怪物编号
	HBITMAP img;			//图片
	bool visible;			//是否可见
	bool task_complete;		//任务是否完成
	bool move;				//是否可以移动

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


	vector<const wchar_t*> conversations_before;	//任务完成前的台词
	vector<const wchar_t*> conversations_after;		//任务完成后的台词
	int next_conversation_id;						//下一次要说第几句台词
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


struct Drawable {
	HBITMAP img;      // 图像句柄
	int x, y;       // 图像绘制左上角
	int size_x, size_y; // 绘制尺寸
	int bmp_x, bmp_y; // 位图上起始绘制点
	int bmp_size_x, bmp_size_y; // 位图上起始绘制点
	int weight_x, weight_y; // 比较时用
	COLORREF transparentColor; // 透明色
	vector<Drawable*> subdrawables; // 下一个图像
};



//TODO: 添加游戏需要的更多种数据（地物、砖块等）


#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

void AddEffect(NewMonster* monster, int effect_id);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y, wstring text);

Particle* CreateParticle(wstring text);

Effect* CreateEffect(int effect_id);

// 添加单位函数
Player* CreatePlayer(int x, int y);
Weapon* CreateWeapon(int weapon_id);
Monster* CreateMonster(int x, int y, int monster_id);

Land* CreateLand(int land_id);


// 初始化场景函数
void InitStage(HWND hWnd, int stageID);


//行为和交互函数：update***在定时器事件中以固定频率调用；handle***在发生键盘/鼠标事件时触发
void UpdatePlayer(HWND hWnd);
void UpdateNPCs(HWND hWnd);
void UpdateMonsters(HWND hWnd);
void UpdateMaps(HWND hWnd);
void UpdateTasks(HWND hWnd);

void HandleConversationEvents(HWND hWnd);
void HandleStopEvents(HWND hWnd);

void HandleHelpEvents(HWND hWnd);

//TODO: 添加游戏需要的更多函数


#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

#pragma endregion
