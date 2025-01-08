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
#include "IDs.h"
#include "Buttons.h"
#include "Monsters.h"
#include "Items.h"
#include "NPCs.h"
#include "Maps.h"
#include "Player.h"
#include "Progress.h"
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数
using namespace std;
#pragma endregion

#pragma region 宏定义

const double PI = 3.14159265358979323846;


#pragma endregion


#pragma region 结构体声明

struct Drawable {
	bool visible = true;
	HBITMAP img;      // 图像句柄
	int x, y;       // 图像绘制左上角
	int size_x, size_y; // 绘制尺寸
	int bmp_x, bmp_y; // 位图上起始绘制点
	int bmp_size_x, bmp_size_y; // 位图上起始绘制点
	int weight_x, weight_y; // 比较时用
	COLORREF transparentColor; // 透明色
	vector<Drawable*> subdrawables; // 下一个图像
};

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

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region 其它游戏状态处理函数声明


// 初始化场景函数
void InitStage(HWND hWnd, int stageID);
void InitCurrent();
void AllInit();


//行为和交互函数：update***在定时器事件中以固定频率调用；handle***在发生键盘/鼠标事件时触发
void UpdatePlayer(HWND hWnd);
void UpdateNPCs(HWND hWnd);
void UpdateMonsters(HWND hWnd);
void UpdateMaps(HWND hWnd);
void UpdateFailed(HWND hWnd);

void HandleConversationEvents(HWND hWnd);
void HandleStopEvents(HWND hWnd);
void HandleHelpEvents(HWND hWnd);
void HandleFailedEvents(HWND hWnd, std::wstring str);

//TODO: 添加游戏需要的更多函数


#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

#pragma endregion
