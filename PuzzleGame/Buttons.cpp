#include "Buttons.h"
#include "IDs.h"
#include "Resource.h"
#include <map>

std::vector<Button*> menu_buttons;
std::vector<Button*> stop_buttons;
std::vector<Button*> failed_buttons;
std::vector<Button*> bed_buttons;
std::vector<Button*> end_buttons;
std::vector<Button*> void_buttons;

HBITMAP bmp_button = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BTN_BG));

Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y, std::wstring text)
{
	Button* button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;
	button->text = text;

	button->visible = true;
	return button;
}


void InitButtons() {


	for (int i = 0; i < menu_buttons.size(); i++) {
		delete menu_buttons[i];
	}
	menu_buttons.clear();

	for (int i = 0; i < stop_buttons.size(); i++) {
		delete stop_buttons[i];
	}
	stop_buttons.clear();

	for (int i = 0; i < failed_buttons.size(); i++) {
		delete failed_buttons[i];
	}
	failed_buttons.clear();

	for (int i = 0; i < void_buttons.size(); i++) {
		delete void_buttons[i];
	}
	void_buttons.clear();

	for (int i = 0; i < bed_buttons.size(); i++) {
		delete bed_buttons[i];
	}
	bed_buttons.clear();

	for (int i = 0; i < end_buttons.size(); i++) {
		delete end_buttons[i];
	}
	end_buttons.clear();



	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 2 / 4, L"START");
	menu_buttons.push_back(startButton);

	Button* helpButton = CreateButton(BUTTON_HELP, bmp_button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 3 / 4, L"HELP");
	menu_buttons.push_back(helpButton);


	Button* continueButton_stop = CreateButton(BUTTON_STOP_CONTINUE, bmp_button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1 / 4, L"CONTINUE");
	stop_buttons.push_back(continueButton_stop);
	Button* helpButton_stop = CreateButton(BUTTON_STOP_HELP, bmp_button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 2 / 4, L"HELP");
	stop_buttons.push_back(helpButton_stop);
	Button* homeButton_stop = CreateButton(BUTTON_STOP_HOME, bmp_button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 3 / 4, L"HOME");
	stop_buttons.push_back(homeButton_stop);

	Button* restartButton = CreateButton(BUTTON_FAILED_RESTART, bmp_button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 3 / 4, L"RESTART");
	failed_buttons.push_back(restartButton);

	bed_buttons.push_back(CreateButton(BUTTON_BED_END, bmp_button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 2 / 4, L"YES"));

	bed_buttons.push_back(CreateButton(BUTTON_BED_CONTINUE, bmp_button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 3 / 4, L"NO"));

	end_buttons.push_back(CreateButton(BUTTON_END_BACK, bmp_button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 3.5 / 4, L"BACK"));

}