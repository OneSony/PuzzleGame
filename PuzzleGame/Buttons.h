#pragma once Buttons
#include "PuzzleGame.h"

extern vector<Button*> menu_buttons;
extern vector<Button*> stop_buttons;
extern vector<Button*> failed_buttons;
extern vector<Button*> void_buttons;

void InitButtons();

Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y, wstring text);