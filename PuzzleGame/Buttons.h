#pragma once
#include <vector>
#include <string>
#include <windows.h>

struct Button
{
	int buttonID;	//��ť���
	bool visible;	//��ť�Ƿ�ɼ�
	HBITMAP img;	//ͼƬ
	int x;			//����x
	int y;			//����y
	int width;		//���
	int height;		//�߶�
	std::wstring text;          // ������ʾ��ť�ϵ�����
};

extern std::vector<Button*> menu_buttons;
extern std::vector<Button*> stop_buttons;
extern std::vector<Button*> failed_buttons;
extern std::vector<Button*> void_buttons;

void InitButtons();

Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y, std::wstring text);