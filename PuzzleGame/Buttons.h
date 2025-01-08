#pragma once
#include <vector>
#include <string>
#include <windows.h>

struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
	std::wstring text;          // 用于显示按钮上的文字
};

extern std::vector<Button*> menu_buttons;
extern std::vector<Button*> stop_buttons;
extern std::vector<Button*> failed_buttons;
extern std::vector<Button*> void_buttons;

void InitButtons();

Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y, std::wstring text);