// PuzzleGame.cpp : 定义应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS
#include "PuzzleGame.h"
#include "Maps.h"
#include <string.h>
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

HBITMAP bmp_Button;	//按钮图像资源
HBITMAP bmp_Player;			//玩家图像
HBITMAP bmp_NPC_MAN1;		//各位NPC图像
HBITMAP bmp_Background;		//生成的背景图像
HBITMAP bmp_map;			//地图砖块图像
HBITMAP bmp_dialog;			//对话框背景图像
HBITMAP bmp_monster1;		//怪物1图像
HBITMAP bmp_crow;		//怪物1图像
HBITMAP bmp_duck;		//怪物1图像
HBITMAP bmp_chiken;		//怪物1图像
HBITMAP bmp_weapon;		//怪物1图像

Stage* currentStage = NULL; //当前场景状态
vector<NPC*> npcs;			//NPC列表
vector<Monster*> monsters;	//怪物列表
//vector<NewMonster*> new_monsters;	//怪物列表

vector<NewMonster*> new_monsters_main;
vector<NewMonster*> new_monsters_house_1;
vector<NewMonster*>* current_new_monsters;

Player* player = NULL;		//玩家
vector<Button*> game_buttons;	//按钮	
vector<Button*> menu_buttons;	//按钮	
vector<Button*> stop_buttons;	//按钮	

int mouseX = 0;
int mouseY = 0;
bool mouseDown = false;
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false;
bool in_conversation = false;	//当前游戏处在对话状态
bool in_stop = false;
bool in_help = false;
const wchar_t* converstaion_content = nullptr;	//当前对话的内容

//TODO 更多的全局变量


//帧
int PLAYER_FRAMES_HOLD[] = { 0 };
int PLAYER_FRAMES_HOLD_COUNT = sizeof(PLAYER_FRAMES_HOLD) / sizeof(int);
int NPC_FRAMES_HOLD[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
int NPC_FRAMES_HOLD_COUNT = sizeof(NPC_FRAMES_HOLD) / sizeof(int);
int FRAMES_WALK[] = {0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,};
int FRAMES_HOLD[] = { 0,0,0,0,0, };
int FRAMES_HOLD_COUNT = sizeof(FRAMES_HOLD) / sizeof(int);
int FRAMES_HOME[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
int FRAMES_HOME_COUNT = sizeof(FRAMES_HOME) / sizeof(int);
int FRAMES_WALK_COUNT = sizeof(FRAMES_WALK) / sizeof(int);
int MONSTER_FRAMES[] = {0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4};
int MONSTER_FRAMES_COUNT = sizeof(MONSTER_FRAMES) / sizeof(int);

//地图
//0空地 1草 2红花 3+7树 4/5/6/8/9/10/12/13/14土地 11蓝花 15路牌


int current_reachable[20][28] = { 0 };
int current_bg[20][28] = { 0 };
int current_obj[20][28] = { 0 };

// TODO: 在此添加其它全局变量

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PUZZLEGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PUZZLEGAME));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PUZZLEGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PUZZLEGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, 
       WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化
       CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);
   SetMenu(hWnd, NULL);     //隐藏菜单栏
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // 初始化游戏窗体
        InitGame(hWnd, wParam, lParam);
        break;
    case WM_KEYDOWN:
        // 键盘按下事件
        KeyDown(hWnd, wParam, lParam);
        break;
    case WM_KEYUP:
        // 键盘松开事件
        KeyUp(hWnd, wParam, lParam);
        break;
    case WM_MOUSEMOVE:
        // 鼠标移动事件
        MouseMove(hWnd, wParam, lParam);
        break;
    case WM_LBUTTONDOWN:
        // 鼠标左键按下事件
        LButtonDown(hWnd, wParam, lParam);
        break;
    case WM_LBUTTONUP:
        // 鼠标左键松开事件
        LButtonUp(hWnd, wParam, lParam);
        break;
    case WM_TIMER:
        // 定时器事件
        if (currentStage != NULL && currentStage->timerOn) TimerUpdate(hWnd, wParam, lParam);
        break;
    case WM_PAINT:
        // 绘图
        Paint(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载图像资源
	bmp_Background = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BACKGROUND));
	bmp_Button = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BTN_BG));
	bmp_Player = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_PLAYER));
	bmp_NPC_MAN1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_NPC_MAN1));
	bmp_map = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_MAP));
	bmp_dialog = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_DIALOG));
	bmp_monster1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_MONSTER1));
	bmp_crow = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_CROW));
	bmp_duck = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_DUCK));
	bmp_chiken = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_CHIKEN));
	bmp_weapon = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_WEAPON));
	
	//添加按钮
	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_Button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT)*2 / 4, L"START");
	menu_buttons.push_back(startButton);

	Button* helpButton = CreateButton(BUTTON_HELP, bmp_Button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT)*3 / 4, L"HELP");
	menu_buttons.push_back(helpButton);


	Button* continueButton_stop = CreateButton(BUTTON_STOP_CONTINUE, bmp_Button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1 / 4, L"CONTINUE");
	stop_buttons.push_back(continueButton_stop);
	Button* helpButton_stop = CreateButton(BUTTON_STOP_HELP, bmp_Button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 2 / 4, L"HELP");
	stop_buttons.push_back(helpButton_stop);
	Button* homeButton_stop = CreateButton(BUTTON_STOP_HOME, bmp_Button, BUTTON_WIDTH, BUTTON_HEIGHT,
		(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) * 3 / 4, L"HOME");
	stop_buttons.push_back(homeButton_stop);


	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);

	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = true;
		break;
	case VK_DOWN:
		keyDownDown = true;
		break;
	case VK_LEFT:
		keyLeftDown = true;
		break;
	case VK_RIGHT:
		keyRightDown = true;
		break;
	case VK_SPACE:
		break;
	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = false;
		break;
	case VK_DOWN:
		keyDownDown = false;
		break;
	case VK_LEFT:
		keyLeftDown = false;
		break;
	case VK_RIGHT:
		keyRightDown = false;
		break;
	case VK_SPACE:
		HandleConversationEvents(hWnd);
		break;
	case VK_ESCAPE:
		if (in_help) {
			HandleHelpEvents(hWnd);
		}
		else {
			HandleStopEvents(hWnd);
		}

		break;
	default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
}


// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;

	if(in_help){


	} else if (in_stop) {
		for (int i = 0; i < stop_buttons.size(); i++)
		{
			Button* button = stop_buttons[i];
			if (button->visible)
			{
				if (button->x <= mouseX
					&& button->x + button->width >= mouseX
					&& button->y <= mouseY
					&& button->y + button->height >= mouseY)
				{
					switch (button->buttonID) {
					case BUTTON_STOP_CONTINUE:
					{
						HandleStopEvents(hWnd);
						break;
					}
					case BUTTON_STOP_HELP:
					{
						HandleHelpEvents(hWnd);
						break;
					}
					case BUTTON_STOP_HOME:
					{	
						in_stop = false;
						InitStage(hWnd, STAGE_STARTMENU); //内部有invalidate
						break;
					}
					break;
					}
				}
			}
		}

	}else if (currentStage->stageID == STAGE_STARTMENU) {

		for (int i = 0; i < menu_buttons.size(); i++)
		{
			Button* button = menu_buttons[i];
			if (button->visible)
			{
				if (button->x <= mouseX
					&& button->x + button->width >= mouseX
					&& button->y <= mouseY
					&& button->y + button->height >= mouseY)
				{
					switch (button->buttonID) {
					case BUTTON_STARTGAME:
					{
						//TODO：判断进入哪个关卡
						InitStage(hWnd, STAGE_1);
						break;
					}
					case BUTTON_HELP:
					{
						HandleHelpEvents(hWnd);
						break;
					}
					break;
					}
				}
			}
		}
	}
	else {
		if (player->weapon != NULL) {
			player->weapon->move = true;
			char buff[256];
			sprintf(buff, "weapon move %d\n", player->weapon->move);
			OutputDebugStringA(buff);
		}

		for (int i = 0; i < current_new_monsters->size(); i++) {
			NewMonster* monster = current_new_monsters->at(i);

			if (monster->visible) {
				//TODO 碰撞了
				if (mouseX >= monster->x-monster->size_x && mouseX <= monster->x + monster->size_x &&
					mouseY >= monster->y - monster->size_y && mouseY <= monster->y + monster->size_y)
				{
					monster->hurt = true;
					monster->hp -= player->weapon->damage;
					monster->hp_visible = true;
					monster->particles.push_back(CreateParticle(L"-" + to_wstring(player->weapon->damage) + L"HP"));

					AddEffect(monster, EFFECT_SPEED_UP_ID);

					char buff[256];
					sprintf(buff, "monster hp: %d\n", monster->hp);
					OutputDebugStringA(buff);
				}
			}

		}
	}

}

void AddEffect(NewMonster* monster, int effect_id) {
	for (auto it = monster->effects.begin(); it != monster->effects.end(); it++) {
		if ((*it)->effectID == effect_id) {
			(*it)->life_count = 0;
			return;
		}
	}

	monster->effects.push_back(CreateEffect(EFFECT_SPEED_UP_ID));
}

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

	if (in_stop) {
		return;
	}

	UpdatePlayer(hWnd);
	UpdateNPCs(hWnd);
	UpdateMonsters(hWnd);
	UpdateMaps(hWnd);
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}


bool CanMove(int x_before, int y_before, int x_after, int y_after) { //player's x y


	//block
	//0空地 1草 2红花 3+7树 4/5/6/8/9/10/12/13/14土地 11蓝花 15路牌
	/*if (current_map[y_after / BLOCK_SIZE_Y][x_after / BLOCK_SIZE_X] == 3 || current_map[y_after / BLOCK_SIZE_Y][x_after / BLOCK_SIZE_X] == 7) {
		return false;
	}*/

	if (current_reachable[y_after / BLOCK_SIZE_Y][x_after / BLOCK_SIZE_X] == 1) {
		return false;
	}
	

	//移动速度考虑了吗
	/*
	//npcs
	char buff[256];
	sprintf(buff, "xy: %d %d %d %d\n", x_before, y_before, x_after, y_after);
	OutputDebugStringA(buff);

	int x_limit_left = min(x_before, x_after) - 0.5 * HUMAN_SIZE_X - 0.5 * HUMAN_SIZE_X;
	int x_limit_right = max(x_before, x_after) + 0.5 * HUMAN_SIZE_X + 0.5 * HUMAN_SIZE_X;
	int y_limit_up = min(y_before, y_after) - 0.5 * HUMAN_SIZE_Y - 0.5 * HUMAN_SIZE_Y;
	int y_limit_down = max(y_before, y_after) + 0.5 * HUMAN_SIZE_Y + 0.5 * HUMAN_SIZE_Y;

	sprintf(buff, "%d %d %d %d\n", x_limit_left, x_limit_right, y_limit_up, y_limit_down);
	OutputDebugStringA(buff);

	for (int i = 0; i < npcs.size(); i++)
	{
		sprintf(buff, "i: %d %d %d\n", i, npcs[i]->x, npcs[i]->y);
		OutputDebugStringA(buff);
		if (npcs[i]->x < x_limit_left || npcs[i]->x > x_limit_right || npcs[i]->y < y_limit_up || npcs[i]->y > y_limit_down) {
			//sprintf(buff, "%d %d\n",npcs[i]->x, npcs[i]->y);
			//OutputDebugStringA(buff);
			continue;
		}

		return false;
	}
	*/

	return true;
}

//更新玩家状态
void UpdatePlayer(HWND hWnd) {
	//如果键盘按下，设置状态为WALK
	if (keyLeftDown || keyUpDown || keyRightDown || keyDownDown) {
		player->state = UNIT_STATE_WALK;
		player->frame_sequence = FRAMES_WALK;
		player->frame_count = FRAMES_WALK_COUNT;
		if (keyLeftDown) {
			player->direction = UNIT_DIRECT_LEFT;
		}
		else if (keyUpDown) {
			player->direction = UNIT_DIRECT_UP;
		}
		else if (keyRightDown) {
			player->direction = UNIT_DIRECT_RIGHT;
		}
		else if (keyDownDown) {
			player->direction = UNIT_DIRECT_DOWN;
		}
		player->frame_row = player->direction;
	}
	else {
		player->state = UNIT_STATE_HOLD;
		player->frame_sequence = PLAYER_FRAMES_HOLD;
		player->frame_count = PLAYER_FRAMES_HOLD_COUNT;
	}
	//更新位置
	if (player->state == UNIT_STATE_WALK) {
		switch (player->direction) {
		case UNIT_DIRECT_LEFT:
			if (CanMove(player->x, player->y, player->x - player->vx, player->y)) {
				player->x -= player->vx;
			}
			break;
		case UNIT_DIRECT_UP:
			if (CanMove(player->x, player->y, player->x, player->y - player->vy)) {
				player->y -= player->vy;
			}
			break;
		case UNIT_DIRECT_RIGHT:
			if (CanMove(player->x, player->y, player->x + player->vx, player->y)) {
				player->x += player->vx;
			}
			break;
		case UNIT_DIRECT_DOWN:
			if (CanMove(player->x, player->y, player->x, player->y + player->vy)) {
				player->y += player->vy;
			}
			break;
		default:
			break;
		};
	}
	//动画运行到下一帧
	player->frame_id++;
	player->frame_id = player->frame_id % player->frame_count;
	player->frame_column = player->frame_sequence[player->frame_id];
}

int RandomInt(int min, int max) {
	static std::mt19937 gen{ std::random_device{}() }; // 静态变量，保持生成器的状态
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

//更新NPC状态
void UpdateNPCs(HWND hWnd) {

	//顺次更新每个npc
	for (int i = 0; i < npcs.size(); i++) {
		//动画运行到下一帧
		npcs[i]->frame_id++;
		npcs[i]->frame_id = npcs[i]->frame_id % npcs[i]->frame_count;
		npcs[i]->frame_column = npcs[i]->frame_sequence[npcs[i]->frame_id];
	}
}
void UpdateMonsters(HWND hWnd)
{

	//顺次更新每个怪物
	for (int i = 0; i < current_new_monsters->size(); i++) {

		if (!(*current_new_monsters)[i]->visible) {
			continue;
		}

		NewMonster* monster = (*current_new_monsters)[i];


		char buff[256];
		sprintf(buff, "i: %d, x: %d, y: %d, r: %d\n", i, monster->x / BLOCK_SIZE_X, monster->y / BLOCK_SIZE_Y, current_reachable[monster->y / BLOCK_SIZE_Y][monster->x / BLOCK_SIZE_X]);
		OutputDebugStringA(buff);

		//判断位置是否归巢
		if (current_reachable[monster->y / BLOCK_SIZE_Y][monster->x / BLOCK_SIZE_X] == 5) {
			monster->state = MONSTER_STATE_HOME;
			char buff[256];
			sprintf(buff, "homed: %d\n", i);
			OutputDebugStringA(buff);
		}else if(monster->state == MONSTER_STATE_HOME){
			monster->state = MONSTER_STATE_MOVE;
			monster->time_count = - 1; //重新加载
		}

		sprintf(buff, "here: %d state: %d\n", i, monster->state);
		OutputDebugStringA(buff);


		if (monster->state != MONSTER_STATE_HOME) {
			//更新状态
			monster->time_count++;
			monster->time_count = monster->time_count % monster->time_max;
			if (monster->time_count == 0) {
				//更新移动动画
				monster->state = MONSTER_STATE_MOVE;

				//更新方向
				monster->direction = RandomInt(0, 3);

				//更新下次时间
				monster->time_stop = RandomInt(50, 100);
				monster->time_max = RandomInt(150, 500);
				//TODO 效果可能没法用
			}
			else if (monster->time_count == monster->time_stop) {
				//更新静止动画
				monster->state = MONSTER_STATE_STOP;
			}
		}




		//更新特效
		for (auto it = monster->effects.begin(); it != monster->effects.end(); ) {

			if ((*it)->life_count == 0) { //初始化
				switch ((*it)->effectID) {
				case EFFECT_SPEED_UP_ID:
					monster->state = MONSTER_STATE_MOVE;
					monster->vx = 5;
					monster->vy = 5;
					monster->time_max = RandomInt(5,20);
					monster->time_stop = monster->time_max;
					monster->time_count = 0;
					break;
				}
			}

			if (monster->time_count == 0) { //时间周期开始
				switch ((*it)->effectID) {
				case EFFECT_SPEED_UP_ID://每次要修正时间分配
					monster->state = MONSTER_STATE_MOVE;
					monster->time_max = RandomInt(5, 20);
					monster->time_stop = monster->time_max;
					monster->time_count = 0;
					break;
				}
			}


			(*it)->life_count++;
			char buff[256];
			sprintf(buff, "effect life: %d\n", (*it)->life_count);
			OutputDebugStringA(buff);

			if ((*it)->life_count >= (*it)->life_max) {

				switch ((*it)->effectID) {
				case EFFECT_SPEED_UP_ID:
					monster->state = MONSTER_STATE_STOP;
					monster->vx = 2;
					monster->vy = 2;
					monster->time_stop = RandomInt(50, 100);
					monster->time_max = RandomInt(150, 500);
					monster->time_count = monster->time_stop - 1;
					break;
				}

				delete* it; // 释放内存
				it = monster->effects.erase(it); // 删除粒子并更新迭代器

				sprintf(buff, "delete\n");
				OutputDebugStringA(buff);
			}
			else {
				it++; // 如果没有删除，移动到下一个粒子
			}

		}




		//根据状态更新动画
		switch (monster->state) {
		case MONSTER_STATE_MOVE:
			monster->frame_sequence = FRAMES_WALK;
			monster->frame_count = FRAMES_WALK_COUNT;
			switch (monster->direction) {
			case UNIT_DIRECT_LEFT:
				monster->frame_row = UNIT_DIRECT_LEFT;
				if (CanMove(monster->x, monster->y, monster->x - monster->vx, monster->y)) {
					monster->x -= monster->vx;
				}
				else {
					monster->time_count = monster->time_stop - 1; //跳过本回合
				}
				break;
			case UNIT_DIRECT_UP:
				monster->frame_row = UNIT_DIRECT_UP;
				if (CanMove(monster->x, monster->y, monster->x, monster->y - monster->vy)) {
					monster->y -= monster->vy;
				}
				else {
					monster->time_count = monster->time_stop - 1; //跳过本回合
				}
				break;
			case UNIT_DIRECT_RIGHT:
				monster->frame_row = UNIT_DIRECT_RIGHT;
				if (CanMove(monster->x, monster->y, monster->x + monster->vx, monster->y)) {
					monster->x += monster->vx;
				}
				else {
					monster->time_count = monster->time_stop - 1; //跳过本回合
				}
				break;
			case UNIT_DIRECT_DOWN:
				monster->frame_row = UNIT_DIRECT_DOWN;
				if (CanMove(monster->x, monster->y, monster->x, monster->y + monster->vy)) {
					monster->y += monster->vy;
				}
				else {
					monster->time_count = monster->time_stop - 1; //跳过本回合
				}
				break;
			default:
				break;
			};
			break;
		case MONSTER_STATE_STOP:
			monster->frame_sequence = FRAMES_HOLD;
			monster->frame_count = FRAMES_HOLD_COUNT;
			break;
		case MONSTER_STATE_HOME:
			//TODO
			monster->frame_row = 4;
			monster->frame_sequence = FRAMES_HOME;
			monster->frame_count = FRAMES_HOME_COUNT;
			break;
		}

		
		//更新粒子动画
		for (auto it = monster->particles.begin(); it != monster->particles.end(); ) {

			(*it)->life_count++;
			(*it)->offset_y -= (*it)->vy;

			char buff[256];
			sprintf(buff, "life: %d  max: %d", (*it)->life_count, (*it)->life_max);
			OutputDebugStringA(buff);

			if ((*it)->life_count >= (*it)->life_max) {
				// 如果生命值达到最大值，则删除当前粒子
				delete* it; // 释放内存
				it = monster->particles.erase(it); // 删除粒子并更新迭代器

				sprintf(buff, "delete\n");
				OutputDebugStringA(buff);
			}
			else {
				it++; // 如果没有删除，移动到下一个粒子
			}
		}


		//检查死亡
		if (monster->hp <= 0) {
			monster->visible = false;
		}



		//如果和玩家接触
		int limit_x_left = player->x - HUMAN_SIZE_X * 0.5;
		int limit_x_right = player->x + HUMAN_SIZE_X * 0.5;
		int limit_y_up = player->y - HUMAN_SIZE_Y * 0.5;
		int limit_y_down = player->y + HUMAN_SIZE_Y * 0.5;
		if (monster->x > limit_x_left && monster->x < limit_x_right && monster->y > limit_y_up && monster->y < limit_y_down) {
			//??
			//monster->frame_sequence = FRAMES_WALK;
			//monster->frame_count = FRAMES_WALK_COUNT;

			switch (player->direction) {
			case UNIT_DIRECT_RIGHT:
				if (CanMove(player->x, player->y, player->x - player->vx, player->y)) {
					player->x -= player->vx;
				}
				if (CanMove(monster->x, monster->y, monster->x + player->vx, monster->y)) {
					monster->x += player->vx;
				}
				break;
			case UNIT_DIRECT_LEFT:
				if (CanMove(player->x, player->y, player->x + player->vx, player->y)) {
					player->x += player->vx;
				}
				if (CanMove(monster->x, monster->y, monster->x - player->vx, monster->y)) {
					monster->x -= player->vx;
				}
				break;
			case UNIT_DIRECT_DOWN:
				if (CanMove(player->x, player->y, player->x, player->y - player->vy)) {
					player->y -= player->vy;
				}
				if (CanMove(monster->x, monster->y, monster->x, monster->y + player->vy)) {
					monster->y += player->vy;
				}
				break;
			case UNIT_DIRECT_UP:
				if (CanMove(player->x, player->y, player->x, player->y + player->vy)) {
					player->y += player->vy;
				}
				if (CanMove(monster->x, monster->y, monster->x, monster->y - player->vy)) {
					monster->y -= player->vy;
				}
				break;
			}
		}


		//更新帧
		monster->frame_id++;
		monster->frame_id = monster->frame_id % monster->frame_count;
		monster->frame_column = monster->frame_sequence[monster->frame_id];


	}

}
// 地图切换逻辑
void UpdateMaps(HWND hWnd)
{
	//走到地图边界，切换到map2
	//TODO逻辑有问题，可能是负数

	if (currentStage->stageID == STAGE_1 && player->x / BLOCK_SIZE_X == 4  && player->y/BLOCK_SIZE_Y == 9)
	{	
		player->y = BLOCK_SIZE_Y * 15;
		player->x = BLOCK_SIZE_X * 7;
		InitStage(hWnd, STAGE_HOUSE_1);
	}
	else if (currentStage->stageID == STAGE_HOUSE_1 && (player->x / BLOCK_SIZE_X == 6 || player->x / BLOCK_SIZE_X == 7 ) && player->y / BLOCK_SIZE_Y == 16)
	{
		player->x = BLOCK_SIZE_X * 4;
		player->y = BLOCK_SIZE_Y * 10;
		InitStage(hWnd, STAGE_1);
	}

}

//
//处理各种交互事件
void UpdateEvents(HWND hWnd) 
{

}


//抬起空格时触发，开启对话
void HandleConversationEvents(HWND hWnd) 
{
	//当前已经开启对话，再按一次空格关闭
	if (in_conversation) {
		in_conversation = false;
		return;
	}
	//player与npc做碰撞检测，判断与哪个npc对话
	for (int i = 0; i < npcs.size(); i++) {
		NPC* npc = npcs[i];
		if (((player->x <= npc->x && npc->x <= player->x + HUMAN_SIZE_X) || (npc->x <= player->x && player->x <= npc->x + HUMAN_SIZE_X)) &&
			((player->y <= npc->y && npc->y <= player->y + HUMAN_SIZE_Y) || (npc->y <= player->y && player->y <= npc->y + HUMAN_SIZE_X))) {
			in_conversation = true;
			if (!npc->task_complete) {
				converstaion_content = npc->conversations_before[npc->next_conversation_id];
				if(npc->next_conversation_id < npc->conversations_before.size()-1)
					npc->next_conversation_id++;	//npc的这句话已经说完，下次该说下一句话了；如果已经说到最后一句话了，则一直重复
			}
			else {
				converstaion_content = npc->conversations_after[npc->next_conversation_id];
				if (npc->next_conversation_id < npc->conversations_after.size() - 1)
					npc->next_conversation_id++;	//npc的这句话已经说完，下次该说下一句话了；如果已经说到最后一句话了，则一直重复
			}
			
		}
	}
}


void HandleStopEvents(HWND hWnd)
{
	if (currentStage->stageID != STAGE_STARTMENU) {
		in_stop = !in_stop;
		char buff[256];
		sprintf(buff, "stop: %d\n", in_stop);
		OutputDebugStringA(buff);
		InvalidateRect(hWnd, NULL, FALSE);
	}

}


void HandleHelpEvents(HWND hWnd)
{
	in_help = !in_help;
	char buff[256];
	sprintf(buff, "help: %d\n", in_help);
	OutputDebugStringA(buff);
	InvalidateRect(hWnd, NULL, FALSE);
}



//TODO: 添加游戏需要的更多函数

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y, wstring text)
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

Particle* CreateParticle(wstring text) {
	Particle* particle = new Particle();
	particle->text = text;
	particle->offset_x=0;
	particle->offset_y=0;
	particle->vx=0;
	particle->vy=2;
	particle->life_max=15;
	particle->life_count=0;

	return particle;
}

Effect* CreateEffect(int effect_id) {
	Effect* effect = new Effect();
	effect->effectID = effect_id;
	effect->life_count = 0;

	switch (effect_id)
	{
	case EFFECT_SPEED_UP_ID:
	{
		effect->life_max = 100;
		break;
	}
	default:
		break;
	}

	return effect;
}


// 添加主角函数
Player* CreatePlayer(int x, int y)
{
	Player* player = new Player();
	player->img = bmp_Player;
	player->x = x;
	player->y = y;
	player->direction = UNIT_DIRECT_RIGHT;
	player->vx = 5;
	player->vy = 5;

	player->state = UNIT_STATE_HOLD;
	player->frame_row = player->direction;
	player->frame_column = 0;
	player->frame_sequence = PLAYER_FRAMES_HOLD;
	player->frame_count = PLAYER_FRAMES_HOLD_COUNT;
	player->frame_id = 0;

	player->weapon = CreateWeapon(WEAPON_SWORD_ID);

	return player;
}


Weapon* CreateWeapon(int weapon_id)
{
	Weapon* weapon = new Weapon();
	weapon->weaponID = weapon_id;
	weapon->img = bmp_weapon;
	weapon->move = false;

	switch (weapon_id)
	{
	case WEAPON_SWORD_ID:
	{
		weapon->size_x=30;
		weapon->size_y=30;
		weapon->bmp_size_x=16;
		weapon->bmp_size_y=16;
		weapon->bmp_col = 1;
		weapon->bmp_row = 0;
		weapon->damage = 10;
		break;
	}
	default:
		break;
	}

	return weapon;
}

// 添加NPC函数
NPC* CreateNPC(int x, int y, int npc_id)
{
	NPC* npc = new NPC();
	npc->npcID = npc_id;
	npc->visible = true;
	npc->task_complete = false;
	npc->x = x;
	npc->y = y;
	npc->direction = UNIT_DIRECT_DOWN;
	npc->vx = 0;
	npc->vy = 0;
	npc->state = UNIT_STATE_HOLD;
	npc->frame_row = npc->direction;
	npc->frame_column = 0;
	npc->frame_sequence = NPC_FRAMES_HOLD;
	npc->frame_count = NPC_FRAMES_HOLD_COUNT;
	npc->frame_id = 0;
	npc->next_conversation_id = 0;
	//根据不同NPC初始化不同的图像和对话
	switch (npc_id)
	{
	case NPC_MAN1_ID: {
		npc->img = bmp_NPC_MAN1;
		npc->conversations_before.push_back(L"你好！我是花花镇的居民，很高兴认识你。");
		npc->conversations_before.push_back(L"最近花花镇有些不太平，幽暗森林里时不时会传来一些声响，镇子里的人们每天都惴惴不安，可以请你帮忙调查一下吗？");
		npc->conversations_before.push_back(L"你说幽暗森林怎么走？往城镇上方直走就是啦。");
		npc->conversations_after.push_back(L"这样啊，原来是有一只猫妖跑到森林里了，谢谢你把它赶走，这下镇子里又可以太平了。");
		break;
	}
	default:
		break;
	}

	return npc;
}

Monster* CreateMonster(int x, int y, int monster_id)
{
	Monster* monster = new Monster();
	monster->monsterID = monster_id;
	monster->visible = true;
	monster->task_complete = false;
	monster->move = true;
	monster->x = x;
	monster->y = y;
	monster->direction = UNIT_DIRECT_DOWN;
	monster->vx = 10;
	monster->vy = 10;
	monster->state = UNIT_STATE_HOLD;
	monster->frame_row = monster->direction;
	monster->frame_column = 0;
	monster->frame_sequence = NPC_FRAMES_HOLD;
	monster->frame_count = NPC_FRAMES_HOLD_COUNT;
	monster->frame_id = 0;
	monster->next_conversation_id = 0;
	//根据不同ID初始化不同的图像和对话
	switch (monster_id)
	{
	case MONSTER_CAT_ID:
	{
		monster->img = bmp_monster1;
		monster->conversations_before.push_back(L"喵喵喵。");
		break;
	}
	default:
		break;
	}

	return monster;
}

NewMonster* NewCreateMonster(int x, int y, int monster_id)
{
	NewMonster* monster = new NewMonster();
	monster->monsterID = monster_id;
	monster->visible = true;
	monster->move = true;
	monster->x = x;
	monster->y = y;
	monster->direction = UNIT_DIRECT_DOWN;
	monster->vx = 1;
	monster->vy = 1;
	monster->state = MONSTER_STATE_MOVE;
	monster->frame_row = monster->direction;
	monster->frame_column = 0;
	monster->frame_sequence = FRAMES_WALK;
	monster->frame_count = FRAMES_WALK_COUNT;
	monster->frame_id = 0;
	monster->time_count = -1;
	monster->time_max = 10; //强制初始化
	monster->hp_visible = false;

	switch (monster_id)
	{
	case MONSTER_CAT_ID:
	{
		monster->img = bmp_monster1;
		break;
	}
	case MONSTER_CROW_ID:
	{
		monster->img = bmp_crow;
		monster->bmp_size_x = 64;
		monster->bmp_size_y = 64;
		monster->size_x = 30;
		monster->size_y = 30;
		monster->time_stop = 50;
		monster->time_max = 100;
		monster->hp_max = 200;
		monster->hp = monster->hp_max;
		break;
	}
	case MONSTER_DUCK_ID:
	{
		monster->img = bmp_duck;
		monster->bmp_size_x = 16;
		monster->bmp_size_y = 16;
		monster->size_x = 30;
		monster->size_y = 30;
		monster->time_stop = 50;
		monster->time_max = 100;
		monster->hp_max = 200;
		monster->hp = monster->hp_max;
		break;
	}
	case MONSTER_CHIKEN_ID:
	{
		monster->img = bmp_chiken;
		monster->bmp_size_x = 16;
		monster->bmp_size_y = 16;
		monster->size_x = 30;
		monster->size_y = 30;
		monster->time_stop = 50;
		monster->time_max = 100;
		monster->hp_max = 50;
		monster->hp = monster->hp_max;
		break;
	}
	default:
		break;
	}


	return monster;
}


// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{
	// 初始化场景实例

	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;

	if (stageID == STAGE_STARTMENU) {
		currentStage->bg = bmp_Background;
		currentStage->timerOn = false;
		//显示开始界面的按钮
		for (int i = 0; i < menu_buttons.size(); i++)
		{
			Button* button = menu_buttons[i];
			if (button->buttonID == BUTTON_STARTGAME || button->buttonID == BUTTON_HELP)
				button->visible = true;
			else
				button->visible = false;
		}
	}
	//TODO：添加多个游戏场景
	else if (stageID == STAGE_1)
	{
		memcpy(current_bg, bg_main, sizeof(current_bg));
		memcpy(current_reachable, reachable_main, sizeof(current_reachable));
		memcpy(current_obj, obj_main, sizeof(current_obj));


		current_new_monsters = &new_monsters_main;
		currentStage->timerOn = true;
		//memcpy(new_map, new_map_stage1, sizeof(new_map));
		//显示游戏界面的按钮
		for (int i = 0; i < game_buttons.size(); i++)
		{
			if (false) //TODO：加载游戏界面需要的按钮
				game_buttons[i]->visible = true;
			else
				game_buttons[i]->visible = false;
		}
		if (player == NULL)
			player = CreatePlayer(400, 200);					//第一次调用：初始化player

		if (npcs.size() == 0) {
			npcs.push_back(CreateNPC(625, 200, NPC_MAN1_ID));	//第一次调用：初始化NPC
		}
		//NPC的可见性
		for (int i = 0; i < npcs.size(); i++)
		{
			NPC* npc = npcs[i];
			if (true) //TODO：加载游戏界面需要的按钮
				npc->visible = true;
			else
				npc->visible = false;
		}
		//Monster的可见性
		for (int i = 0; i < monsters.size(); i++)
		{
			Monster* monster = monsters[i];
			if (false) //TODO：加载游戏界面需要的按钮
				monster->visible = true;
			else
				monster->visible = false;
		}
	}
	else if (stageID == STAGE_HOUSE_1)
	{
		memcpy(current_bg, bg_house_1, sizeof(current_bg));
		memcpy(current_reachable, reachable_house_1, sizeof(current_reachable));
		memcpy(current_obj, obj_house_1, sizeof(current_obj));


		current_new_monsters = &new_monsters_house_1;
		currentStage->timerOn = true;

		for (int i = 0; i < game_buttons.size(); i++)
		{
			Button* button = game_buttons[i];
			if (false)
				button->visible = true;
			else
				button->visible = false;
		}
		if (player == NULL)
			player = CreatePlayer(200, 200);

		if (current_new_monsters->size() == 0) {
			//current_new_monsters->push_back(NewCreateMonster(495, 205, MONSTER_CROW_ID));
			current_new_monsters->push_back(NewCreateMonster(350, 350, MONSTER_CHIKEN_ID));
			current_new_monsters->push_back(NewCreateMonster(300, 300, MONSTER_CHIKEN_ID));
		}

		//NPC的可见性
		for (int i = 0; i < npcs.size(); i++)
		{
			NPC* npc = npcs[i];
			if (false) //TODO：加载游戏界面需要的按钮
				npc->visible = true;
			else
				npc->visible = false;
		}
		//Monster的可见性

		/*for (int i = 0; i < current_new_monsters->size(); i++)
		{
			NewMonster* monster = (*current_new_monsters)[i];
			if (true) //TODO：加载游戏界面需要的按钮
				monster->visible = true;
			else
				monster->visible = false;
		}*/
	}

	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}


void DrawTransparentBitmap(HDC hdc_memBuffer, HDC hdc_loadBmp, int x, int y, int width, int height, int bmpWidth, int bmpHeight, BYTE alpha) {
	// 配置 BLENDFUNCTION 结构体
	BLENDFUNCTION blendFunction;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.BlendFlags = 0;
	blendFunction.SourceConstantAlpha = alpha; // 透明度 (0 = 完全透明, 255 = 完全不透明)
	blendFunction.AlphaFormat = 0; // 如果位图包含 alpha 通道，则设为 AC_SRC_ALPHA

	// 使用 AlphaBlend 绘制
	AlphaBlend(
		hdc_memBuffer, x, y, width, height, // 目标区域
		hdc_loadBmp, 0, 0, bmpWidth, bmpHeight, // 源位图区域
		blendFunction
	);
}


// 绘图函数
void Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);


	// 先分为开始菜单和游戏内部
	if (currentStage->stageID == STAGE_STARTMENU) {
		// 绘制背景到缓存
		SelectObject(hdc_loadBmp, currentStage->bg);
		TransparentBlt(
			hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, 0, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT,
			RGB(255, 255, 255));

		//button
		for (int i = 0; i < menu_buttons.size(); i++)
		{
			Button* button = menu_buttons[i];
			if (button->visible)
			{
				SelectObject(hdc_loadBmp, button->img);
				TransparentBlt(
					hdc_memBuffer, button->x, button->y,
					button->width, button->height,
					hdc_loadBmp, 0, 0, button->width, button->height,
					RGB(255, 255, 255)
				);

				// 设置文本背景透明	
				SetBkMode(hdc_memBuffer, TRANSPARENT);

				// 设置字体颜色（例如白色）
				SetTextColor(hdc_memBuffer, RGB(255, 255, 255));

				// 定义文本绘制区域
				RECT textRect;
				textRect.left = button->x;
				textRect.top = button->y;
				textRect.right = button->x + button->width;
				textRect.bottom = button->y + button->height;

				// 绘制文本在按钮的中心
				DrawText(hdc_memBuffer, button->text.c_str(), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	} else {
		if (currentStage->stageID >= STAGE_1) //TODO：添加多个游戏场景
		{



			
			/*

			SelectObject(hdc_loadBmp, bmp_summer_land);
			for (int i = 0; i < sizeof(new_map) / sizeof(new_map[0]); i++) {
				for (int j = 0; j < sizeof(new_map[0]) / sizeof(new_map[0][0]); j++) {
					
					Land* land = new_map[i][j];

					TransparentBlt(
						hdc_memBuffer,
						j * BLOCK_SIZE_X, i * BLOCK_SIZE_Y,							// 界面上起始绘制点
						BLOCK_SIZE_X, BLOCK_SIZE_Y,									// 界面上绘制宽度高度
						hdc_loadBmp,
						land->bmp_col * land->bmp_size_x,						// 位图上起始绘制点
						land->bmp_row * land->bmp_size_y,
						land->bmp_size_x, land->bmp_size_y,					// 位图上绘制宽度高度
						RGB(255, 255, 255));										// 位图上的哪个颜色会被视为背景
				}
			}


			*/

			//首先绘制背景，背景只有一个块
			//需要一个ID->draw的映射
			for (int i = 0; i < sizeof(current_bg) / sizeof(current_bg[0]); i++) {
				for (int j = 0; j < sizeof(current_bg[0]) / sizeof(current_bg[0][0]); j++) {

					//根据bg的值绘制不同的背景
					SelectObject(hdc_loadBmp, bg_hitmap[current_bg[i][j]].bitmap);

					TransparentBlt(
						hdc_memBuffer,
						j * BLOCK_SIZE_X, i * BLOCK_SIZE_Y,							// 界面上起始绘制点
						BLOCK_SIZE_X, BLOCK_SIZE_Y,									// 界面上绘制宽度高度
						hdc_loadBmp,
						0,						// 位图上起始绘制点
						0,
						bg_hitmap[current_bg[i][j]].bitmap_size_x, bg_hitmap[current_bg[i][j]].bitmap_size_y,					// 位图上绘制宽度高度
						RGB(255, 255, 255));										// 位图上的哪个颜色会被视为背景
				}
			}

			
			unordered_set<int> landValues = {4, 5, 6, 8, 9, 10, 12, 13, 14};
			
			//绘制地图
			/*SelectObject(hdc_loadBmp, bmp_map);
			for (int i = 0; i < sizeof(current_map) / sizeof(current_map[0]); i++) {
				for (int j = 0; j < sizeof(current_map[0]) / sizeof(current_map[0][0]); j++) {

					int bmp_x = (0 % 4) * BLOCK_BITMAP_SIZE_X;
					int bmp_y = (0 / 4) * BLOCK_BITMAP_SIZE_Y;

					if (landValues.count(current_map[i][j]) == 0) { //不是沙子默认画0
						bmp_x = (0 % 4) * BLOCK_BITMAP_SIZE_X;
						bmp_y = (0 / 4) * BLOCK_BITMAP_SIZE_Y;
					}
					else
					{
						bmp_x = (current_map[i][j] % 4) * BLOCK_BITMAP_SIZE_X;
						bmp_y = (current_map[i][j] / 4) * BLOCK_BITMAP_SIZE_Y;
					}

					TransparentBlt(
						hdc_memBuffer,
						j * BLOCK_SIZE_X, i * BLOCK_SIZE_Y,							// 界面上起始绘制点
						BLOCK_SIZE_X, BLOCK_SIZE_Y,									// 界面上绘制宽度高度
						hdc_loadBmp,
						bmp_x,						// 位图上起始绘制点
						bmp_y,
						BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,					// 位图上绘制宽度高度
						RGB(255, 255, 255));										// 位图上的哪个颜色会被视为背景
				}
			}*/

			

			vector<Drawable*> drawables;


			for (int i = 0; i < sizeof(current_obj) / sizeof(current_obj[0]); i++) {
				for (int j = 0; j < sizeof(current_obj[0]) / sizeof(current_obj[0][0]); j++) {

					if (current_obj == 0) {
						continue;
					}

					int num_x = obj_hitmap[current_obj[i][j]].num_x;
					int num_y = obj_hitmap[current_obj[i][j]].num_y;

					Drawable* obj = new Drawable();
					obj->img = obj_hitmap[current_obj[i][j]].bitmap;
					obj->x = j * BLOCK_SIZE_X;
					obj->y = i * BLOCK_SIZE_Y;
					obj->size_x = BLOCK_SIZE_X * num_x;
					obj->size_y = BLOCK_SIZE_Y * num_y;
					obj->bmp_x = 0;
					obj->bmp_y = 0;
					obj->bmp_size_x = obj_hitmap[current_obj[i][j]].bitmap_size_x * num_x;
					obj->bmp_size_y = obj_hitmap[current_obj[i][j]].bitmap_size_y * num_y;
					obj->transparentColor = RGB(255, 255, 255);
					drawables.push_back(obj);
				}
			}

			
			/*for (int i = 0; i < sizeof(current_map) / sizeof(current_map[0]); i++) {
				for (int j = 0; j < sizeof(current_map[0]) / sizeof(current_map[0][0]); j++) {

					if (landValues.count(current_map[i][j]) != 0) {
						continue;
					}else{

						Drawable* tile = new Drawable();
						tile->img = bmp_map;
						tile->x = j * BLOCK_SIZE_X;
						tile->y = i * BLOCK_SIZE_Y;
						tile->size_x = BLOCK_SIZE_X;
						tile->size_y = BLOCK_SIZE_Y;
						tile->bmp_x = (current_map[i][j] % 4) * BLOCK_BITMAP_SIZE_X;
						tile->bmp_y = (current_map[i][j] / 4) * BLOCK_BITMAP_SIZE_Y;
						tile->bmp_size_x = BLOCK_BITMAP_SIZE_X;
						tile->bmp_size_y = BLOCK_BITMAP_SIZE_Y;
						tile->transparentColor = RGB(91, 179, 142);
						drawables.push_back(tile);
					}
				}
			}*/
			


			// 绘制玩家

			Drawable* p = new Drawable();
			p->img = player->img;
			p->x = player->x - 0.5 * HUMAN_SIZE_X;
			p->y = player->y - 0.5 * HUMAN_SIZE_Y;
			p->size_x = HUMAN_SIZE_X;
			p->size_y = HUMAN_SIZE_Y;
			p->bmp_x = HUMAN_BITMAP_SIZE_X * player->frame_column;
			p->bmp_y = HUMAN_BITMAP_SIZE_Y * player->frame_row;
			p->bmp_size_x = HUMAN_BITMAP_SIZE_X;
			p->bmp_size_y = HUMAN_BITMAP_SIZE_Y;
			p->transparentColor = RGB(255, 255, 255);

			if (player->weapon != NULL) {

				Weapon* weapon = player->weapon;
				Drawable* w = new Drawable();
				w->img = weapon->img;
				w->x = player->x - 0.5 * weapon->size_x;
				w->y = player->y - 0.5 * HUMAN_SIZE_Y - 0.5 * weapon->size_y;
				w->size_x = weapon->size_x;
				w->size_y = weapon->size_y;
				w->bmp_x = weapon->bmp_size_x * weapon->bmp_col;
				w->bmp_y = weapon->bmp_size_y * weapon->bmp_row;
				w->bmp_size_x = weapon->bmp_size_x;
				w->bmp_size_y = weapon->bmp_size_y;
				w->transparentColor = RGB(255, 255, 255);

				p->subdrawables.push_back(w);

			}
			drawables.push_back(p);


			for (int i = 0; i < npcs.size(); i++) {
				if (npcs[i]->visible) {


					Drawable* n = new Drawable();
					n->img = npcs[i]->img;
					n->x = npcs[i]->x - 0.5 * HUMAN_SIZE_X;
					n->y = npcs[i]->y - 0.5 * HUMAN_SIZE_Y;
					n->size_x = HUMAN_SIZE_X;
					n->size_y = HUMAN_SIZE_Y;
					n->bmp_x = HUMAN_BITMAP_SIZE_X * npcs[i]->frame_column;
					n->bmp_y = HUMAN_BITMAP_SIZE_Y * npcs[i]->frame_row;
					n->bmp_size_x = HUMAN_BITMAP_SIZE_X;
					n->bmp_size_y = HUMAN_BITMAP_SIZE_Y;
					n->transparentColor = RGB(255, 255, 255);
					
					drawables.push_back(n);
				}
			}



			for (int i = 0; i < current_new_monsters->size(); i++) {
				if ((*current_new_monsters)[i]->visible) {

					NewMonster* monster = (*current_new_monsters)[i];

					Drawable* m = new Drawable();

					m->img = monster->img;
					m->x = monster->x - 0.5 * monster->size_x;
					m->y = monster->y - 0.5 * monster->size_y;
					m->size_x = monster->size_x;
					m->size_y = monster->size_y;
					m->bmp_x = monster->bmp_size_x * monster->frame_column;
					m->bmp_y = monster->bmp_size_y * monster->frame_row;
					m->bmp_size_x = monster->bmp_size_x;
					m->bmp_size_y = monster->bmp_size_y;
					m->transparentColor = RGB(255, 255, 255);
					//受伤动画 粒子效果 血条在外面画？

					drawables.push_back(m);
				}
			}


			//绘制drawable
			std::sort(drawables.begin(), drawables.end(), [](const Drawable* a, const Drawable* b) {
				return (a->y + (BLOCK_SIZE_Y * 0.5)) < (b->y + (BLOCK_SIZE_Y * 0.5));
			});

			for (const auto drawable : drawables) {
				SelectObject(hdc_loadBmp, drawable->img);
				TransparentBlt(
					hdc_memBuffer,
					drawable->x, drawable->y, // 界面上起始绘制点
					drawable->size_x, drawable->size_y,                                    // 绘制宽度高度
					hdc_loadBmp,
					drawable->bmp_x, drawable->bmp_y, // 位图起始点
					drawable->bmp_size_x, drawable->bmp_size_y,                                    // 位图宽度高度
					drawable->transparentColor                                            // 透明色
				);

				for (const auto subdrawable : drawable->subdrawables) { //只能一层
					SelectObject(hdc_loadBmp, subdrawable->img);
					TransparentBlt(
						hdc_memBuffer,
						subdrawable->x, subdrawable->y, // 界面上起始绘制点
						subdrawable->size_x, subdrawable->size_y,                                    // 绘制宽度高度
						hdc_loadBmp,
						subdrawable->bmp_x, subdrawable->bmp_y, // 位图起始点
						subdrawable->bmp_size_x, subdrawable->bmp_size_y,                                    // 位图宽度高度
						subdrawable->transparentColor                                            // 透明色
					);

					delete subdrawable;
				}

				delete drawable;
			}





			//上层动画

			for (int i = 0; i < current_new_monsters->size(); i++) {
				if ((*current_new_monsters)[i]->visible) {

					NewMonster* monster = (*current_new_monsters)[i];

					//受伤动画
					if (current_new_monsters->at(i)->hurt) {

						SelectObject(hdc_loadBmp, monster->img);

						char buff[256];
						sprintf(buff, "hurt %d\n", i);
						OutputDebugStringA(buff);

						// 创建怪物图像的副本
						HDC hdc_monsterCopy = CreateCompatibleDC(hdc_memBuffer);
						HBITMAP hbm_monsterCopy = CreateCompatibleBitmap(hdc_memBuffer, monster->bmp_size_x, monster->bmp_size_y);
						SelectObject(hdc_monsterCopy, hbm_monsterCopy);

						// 将原始怪物图像拷贝到副本
						BitBlt(hdc_monsterCopy, 0, 0, monster->bmp_size_x, monster->bmp_size_y, hdc_loadBmp,
							monster->bmp_size_x * monster->frame_column, monster->bmp_size_y * monster->frame_row, SRCCOPY);


						// 将所有非透明像素替换为红色
						for (int y = 0; y < monster->bmp_size_y; y++) {
							for (int x = 0; x < monster->bmp_size_x; x++) {
								COLORREF pixelColor = GetPixel(hdc_monsterCopy, x, y);
								if (pixelColor != RGB(255, 255, 255)) { // 忽略透明背景
									SetPixel(hdc_monsterCopy, x, y, RGB(255, 0, 0)); // 将像素设置为红色
								}
							}
						}


						// 绘制纯红色的怪物图像
						TransparentBlt(
							hdc_memBuffer,
							monster->x - 0.5 * monster->size_x, monster->y - 0.5 * monster->size_y,
							monster->size_x, monster->size_y,
							hdc_monsterCopy,
							0, 0,
							monster->bmp_size_x, monster->bmp_size_y,
							RGB(255, 255, 255)
						);

						// 清理资源
						DeleteObject(hbm_monsterCopy);
						DeleteDC(hdc_monsterCopy);

						current_new_monsters->at(i)->hurt = false;
					}


					//粒子动画
					//NewMonster* monster = (*current_new_monsters)[i];
					for (int j = 0; j < monster->particles.size(); j++) {
						char buff[256];
						sprintf(buff, "text: %d\n", j);
						OutputDebugStringA(buff);
						Particle* particle = monster->particles[j];

						RECT textRect;
						textRect.left = monster->x - monster->size_x * 2;
						textRect.top = monster->y - monster->size_y - 16 + particle->offset_y; //?
						textRect.right = monster->x + monster->size_x * 2;
						textRect.bottom = monster->y - monster->size_y * 0.5 + particle->offset_y;

						// 绘制文本在按钮的中心
						SetBkMode(hdc_memBuffer, TRANSPARENT);
						SetTextColor(hdc_memBuffer, RGB(255, 0, 0));
						DrawText(hdc_memBuffer, particle->text.c_str(), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

						SetTextColor(hdc_memBuffer, RGB(0, 0, 0));
						//DrawCenteredText(hdc_loadBmp, particle->text, monster->x, monster->y - monster->size_y, 16, RGB(255, 0, 0));
					}

					if (monster->hp_visible) {
						RECT hpRect_bg;
						hpRect_bg.left = monster->x - HP_WIDTH * 0.5;
						hpRect_bg.top = monster->y - monster->size_y * 0.5 - HP_HEIGHT;
						hpRect_bg.right = monster->x + HP_WIDTH * 0.5;
						hpRect_bg.bottom = monster->y - monster->size_y * 0.5;

						if (monster->hp <= 0) {
							monster->hp = 0;
						}

						RECT hpRect_hp;
						hpRect_hp.left = monster->x - HP_WIDTH * 0.5;
						hpRect_hp.top = monster->y - monster->size_y * 0.5 - HP_HEIGHT;
						hpRect_hp.right = monster->x - HP_WIDTH * 0.5 + (monster->hp / monster->hp_max) * HP_WIDTH;
						hpRect_hp.bottom = monster->y - monster->size_y * 0.5;


						// 黑色背景矩形
						HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));  // 创建黑色画刷
						FillRect(hdc_memBuffer, &hpRect_bg, blackBrush);               // 填充背景矩形
						DeleteObject(blackBrush);                            // 释放黑色画刷

						// 红色血量矩形
						HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));  // 创建红色画刷
						FillRect(hdc_memBuffer, &hpRect_hp, redBrush);                 // 填充血量矩形
						DeleteObject(redBrush);                              // 释放红色画刷

					}
				}
			}








			/*

			//绘制地图
			SelectObject(hdc_loadBmp, bmp_map);
			for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
				for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
					TransparentBlt(
						hdc_memBuffer,
						j * BLOCK_SIZE_X, i * BLOCK_SIZE_Y,							// 界面上起始绘制点
						BLOCK_SIZE_X, BLOCK_SIZE_Y,									// 界面上绘制宽度高度
						hdc_loadBmp,
						(map[i][j] % 4) * BLOCK_BITMAP_SIZE_X,						// 位图上起始绘制点
						(map[i][j] / 4) * BLOCK_BITMAP_SIZE_Y,
						BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,					// 位图上绘制宽度高度
						RGB(255, 255, 255));										// 位图上的哪个颜色会被视为背景
				}
			}

			// 绘制玩家
			// 图像坐标是中心
			SelectObject(hdc_loadBmp, player->img);
			TransparentBlt(
				hdc_memBuffer,
				player->x - 0.5 * HUMAN_SIZE_X, player->y - 0.5 * HUMAN_SIZE_Y,			// 界面上起始绘制点
				HUMAN_SIZE_X, HUMAN_SIZE_Y,											// 界面上绘制宽度高度
				hdc_loadBmp,
				HUMAN_BITMAP_SIZE_X * player->frame_column, HUMAN_BITMAP_SIZE_Y * player->frame_row,	// 位图上起始绘制点
				HUMAN_BITMAP_SIZE_X, HUMAN_BITMAP_SIZE_Y,											// 位图上绘制宽度高度
				RGB(255, 255, 255)
			);

			if (player->weapon != NULL) {

				Weapon* weapon = player->weapon;
				SelectObject(hdc_loadBmp, weapon->img);*/

				//TODO

				/*
				TransparentBlt(
					hdc_memBuffer,
					player->x - 0.5 * weapon->size_x, player->y - 0.5 * HUMAN_SIZE_Y - 0.5* weapon->size_y,			// 界面上起始绘制点
					weapon->size_x, weapon->size_y,											// 界面上绘制宽度高度
					hdc_loadBmp,
					weapon->bmp_size_x * weapon->bmp_col, weapon->bmp_size_y * weapon->bmp_row,	// 位图上起始绘制点
					weapon->bmp_size_x, weapon->bmp_size_y,											// 位图上绘制宽度高度
					RGB(255, 255, 255)
				);
				*/

			/*

			}


			//绘制npc
			for (int i = 0; i < npcs.size(); i++) {
				if (npcs[i]->visible) {
					SelectObject(hdc_loadBmp, npcs[i]->img);
					TransparentBlt(
						hdc_memBuffer,
						npcs[i]->x - 0.5 * HUMAN_SIZE_X, npcs[i]->y - 0.5 * HUMAN_SIZE_Y,			// 界面上起始绘制点
						HUMAN_SIZE_X, HUMAN_SIZE_Y,											// 界面上绘制宽度高度
						hdc_loadBmp,
						HUMAN_BITMAP_SIZE_X * npcs[i]->frame_column, HUMAN_BITMAP_SIZE_Y * npcs[i]->frame_row,	// 位图上起始绘制点
						HUMAN_BITMAP_SIZE_X, HUMAN_BITMAP_SIZE_Y,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);
				}
			}
			//绘制怪物
			for (int i = 0; i < monsters.size(); i++) {
				if (monsters[i]->visible) {
					SelectObject(hdc_loadBmp, monsters[i]->img);
					TransparentBlt(
						hdc_memBuffer,
						monsters[i]->x - 0.5 * MOSTER_SIZE_X, monsters[i]->y - 0.5 * MOSTER_SIZE_Y,		// 界面上起始绘制点
						MOSTER_SIZE_X, MOSTER_SIZE_Y,											// 界面上绘制宽度高度
						hdc_loadBmp,
						MOSTER_BITMAP_SIZE_X * monsters[i]->frame_column, MOSTER_BITMAP_SIZE_Y * monsters[i]->frame_row,	// 位图上起始绘制点
						MOSTER_BITMAP_SIZE_X, MOSTER_BITMAP_SIZE_Y,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);

				}
			}

			for (int i = 0; i < current_new_monsters->size(); i++) {
				if ((*current_new_monsters)[i]->visible) {

					NewMonster* monster = (*current_new_monsters)[i];
					SelectObject(hdc_loadBmp, monster->img);
					TransparentBlt(
						hdc_memBuffer,
						monster->x - 0.5 * monster->size_x, monster->y - 0.5 * monster->size_y,		// 界面上起始绘制点
						monster->size_x, monster->size_y,											// 界面上绘制宽度高度
						hdc_loadBmp,
						monster->bmp_size_x* monster->frame_column, monster->bmp_size_y* monster->frame_row,	// 位图上起始绘制点
						monster->bmp_size_x, monster->bmp_size_y,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);

					//受伤动画
					if (current_new_monsters->at(i)->hurt) {

						char buff[256];
						sprintf(buff, "hurt %d\n",i);
						OutputDebugStringA(buff);

						// 创建怪物图像的副本
						HDC hdc_monsterCopy = CreateCompatibleDC(hdc_memBuffer);
						HBITMAP hbm_monsterCopy = CreateCompatibleBitmap(hdc_memBuffer, monster->bmp_size_x, monster->bmp_size_y);
						SelectObject(hdc_monsterCopy, hbm_monsterCopy);

						// 将原始怪物图像拷贝到副本
						BitBlt(hdc_monsterCopy, 0, 0, monster->bmp_size_x, monster->bmp_size_y, hdc_loadBmp,
							monster->bmp_size_x* monster->frame_column, monster->bmp_size_y* monster->frame_row, SRCCOPY);

						
						// 将所有非透明像素替换为红色
						for (int y = 0; y < monster->bmp_size_y; y++) {
							for (int x = 0; x < monster->bmp_size_x; x++) {
								COLORREF pixelColor = GetPixel(hdc_monsterCopy, x, y);
								if (pixelColor != RGB(255, 255, 255)) { // 忽略透明背景
									SetPixel(hdc_monsterCopy, x, y, RGB(255, 0, 0)); // 将像素设置为红色
								}
							}
						}
						

						// 绘制纯红色的怪物图像
						TransparentBlt(
							hdc_memBuffer,
							monster->x - 0.5 * monster->size_x, monster->y - 0.5 * monster->size_y,
							monster->size_x, monster->size_y,
							hdc_monsterCopy,
							0, 0,
							monster->bmp_size_x, monster->bmp_size_y,
							RGB(255, 255, 255)
						);

						// 清理资源
						DeleteObject(hbm_monsterCopy);
						DeleteDC(hdc_monsterCopy);

						current_new_monsters->at(i)->hurt = false;
					}


					//粒子动画
					//NewMonster* monster = (*current_new_monsters)[i];
					for (int j = 0; j < monster->particles.size(); j++) {
						char buff[256];
						sprintf(buff, "text: %d\n", j);
						OutputDebugStringA(buff);
						Particle* particle = monster->particles[j];

						RECT textRect;
						textRect.left = monster->x - monster->size_x * 2;
						textRect.top = monster->y - monster->size_y - 16 + particle->offset_y; //?
						textRect.right = monster->x + monster->size_x * 2;
						textRect.bottom = monster->y - monster->size_y*0.5 + particle->offset_y;

						// 绘制文本在按钮的中心
						SetBkMode(hdc_memBuffer, TRANSPARENT);
						SetTextColor(hdc_memBuffer, RGB(255, 0, 0));
						DrawText(hdc_memBuffer, particle->text.c_str(), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

						SetTextColor(hdc_memBuffer, RGB(0, 0, 0));
						//DrawCenteredText(hdc_loadBmp, particle->text, monster->x, monster->y - monster->size_y, 16, RGB(255, 0, 0));
					}

					if (monster->hp_visible) {
						RECT hpRect_bg;
						hpRect_bg.left = monster->x - HP_WIDTH * 0.5;
						hpRect_bg.top = monster->y - monster->size_y * 0.5 - HP_HEIGHT;
						hpRect_bg.right = monster->x + HP_WIDTH * 0.5;
						hpRect_bg.bottom = monster->y - monster->size_y * 0.5;

						if (monster->hp <= 0) {
							monster->hp = 0;
						}

						RECT hpRect_hp;
						hpRect_hp.left = monster->x - HP_WIDTH * 0.5;
						hpRect_hp.top = monster->y - monster->size_y * 0.5 - HP_HEIGHT;
						hpRect_hp.right = monster->x - HP_WIDTH * 0.5 + (monster->hp / monster->hp_max) * HP_WIDTH;
						hpRect_hp.bottom = monster->y - monster->size_y * 0.5;


						// 黑色背景矩形
						HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));  // 创建黑色画刷
						FillRect(hdc_memBuffer, &hpRect_bg, blackBrush);               // 填充背景矩形
						DeleteObject(blackBrush);                            // 释放黑色画刷

						// 红色血量矩形
						HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));  // 创建红色画刷
						FillRect(hdc_memBuffer, &hpRect_hp, redBrush);                 // 填充血量矩形
						DeleteObject(redBrush);                              // 释放红色画刷

					}
				}
			}

			*/


			//如果正处在对话状态：绘制对话框
			if (in_conversation) {
				SelectObject(hdc_loadBmp, bmp_dialog);
				TransparentBlt(
					hdc_memBuffer,
					0, WINDOW_HEIGHT - DIALOG_SIZE_Y - 38, WINDOW_WIDTH - 16, DIALOG_SIZE_Y,					// 界面上绘制位置
					hdc_loadBmp,
					0, 0, DIALOG_BITMAP_SIZE_X, DIALOG_BITMAP_SIZE_Y,	// 位图上绘制位置
					RGB(255, 255, 255)
				);
				//绘制文字
				HFONT hFont = CreateFontW(
					20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
					L"SimSun");		//创建字体
				SelectObject(hdc_memBuffer, hFont);
				SetTextColor(hdc_memBuffer, RGB(0, 0, 0));	// 设置颜色:黑色字体白色背景
				SetBkColor(hdc_memBuffer, RGB(255, 255, 255));
				RECT rect;
				rect.left = 50;
				rect.top = WINDOW_HEIGHT - DIALOG_SIZE_Y - 18;
				rect.right = WINDOW_WIDTH - 110;
				rect.bottom = WINDOW_HEIGHT - 50;
				DrawTextW(hdc_memBuffer, converstaion_content, -1, &rect, DT_WORDBREAK);
			}
		}


		// 绘制按钮到缓存
		for (int i = 0; i < game_buttons.size(); i++)
		{
			Button* button = game_buttons[i];
			if (button->visible)
			{
				SelectObject(hdc_loadBmp, button->img);
				TransparentBlt(
					hdc_memBuffer, button->x, button->y,
					button->width, button->height,
					hdc_loadBmp, 0, 0, button->width, button->height,
					RGB(255, 255, 255)
				);

				// 设置文本背景透明
				SetBkMode(hdc_memBuffer, TRANSPARENT);

				// 设置字体颜色（例如白色）
				SetTextColor(hdc_memBuffer, RGB(255, 255, 255));

				// 定义文本绘制区域
				RECT textRect;
				textRect.left = button->x;
				textRect.top = button->y;
				textRect.right = button->x + button->width;
				textRect.bottom = button->y + button->height;

				// 绘制文本在按钮的中心
				DrawText(hdc_memBuffer, button->text.c_str(), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}

	}


	//最后加上透明度
	if (in_stop) {
		SelectObject(hdc_loadBmp, currentStage->bg);
		DrawTransparentBitmap(hdc_memBuffer, hdc_loadBmp, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT, 200);

		//TODO button
		for (int i = 0; i < stop_buttons.size(); i++)
		{
			Button* button = stop_buttons[i];
			if (button->visible)
			{
				SelectObject(hdc_loadBmp, button->img);
				TransparentBlt(
					hdc_memBuffer, button->x, button->y,
					button->width, button->height,
					hdc_loadBmp, 0, 0, button->width, button->height,
					RGB(255, 255, 255)
				);

				// 设置文本背景透明
				SetBkMode(hdc_memBuffer, TRANSPARENT);

				// 设置字体颜色（例如白色）
				SetTextColor(hdc_memBuffer, RGB(255, 255, 255));

				// 定义文本绘制区域
				RECT textRect;
				textRect.left = button->x;
				textRect.top = button->y;
				textRect.right = button->x + button->width;
				textRect.bottom = button->y + button->height;

				// 绘制文本在按钮的中心
				DrawText(hdc_memBuffer, button->text.c_str(), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}

	if (in_help) {
		//TODO

		SelectObject(hdc_loadBmp, currentStage->bg);
		DrawTransparentBitmap(hdc_memBuffer, hdc_loadBmp, 0, 0, WINDOW_WIDTH*0.2, WINDOW_HEIGHT*0.2, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT, 200);

	}


	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}
