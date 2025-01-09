// PuzzleGame.cpp : 定义应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS
#include "PuzzleGame.h"
#include <string>
#include <set>
#include <map>
#define MAX_LOADSTRING 100

HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

HBITMAP bmp_background = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BACKGROUND));
HBITMAP bmp_dialog = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_DIALOG));
HBITMAP bmp_item_bg = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITEM_BG));
HBITMAP bmp_item_name_bg = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITEM_NAME_BG));
HBITMAP bmp_achievement_bg = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ACHIEVE_BG));


std::wstring failed_message;
Stage* currentStage; //当前场景状态
std::vector<NewMonster*>* current_new_monsters;
std::vector<Button*>* current_buttons;
std::list<std::vector<Button*>*> buttons_before;
std::vector<Item*> items;		//物品列表
Item* current_item;	//当前物品
Item* show_name_item;
int item_name_fading_time;
Player* player;		//玩家
int (*current_reachable)[20][28];
int (*current_bg)[20][28];
int (*current_obj)[20][28];
std::vector<NPC*>* current_npcs;



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
bool in_failed = false;
bool in_bed = false;
bool in_global_achievement = false;
bool is_last_time_in_bed = false;
const wchar_t* converstaion_content = nullptr;	//当前对话的内容


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


void AllInit() {
	InitNPCs();
	InitMaps();
	InitMonsters();
	InitButtons();
	InitProgress();
	InitAchievements();
	InitCurrent();
}

void InitCurrent() {

	failed_message = L"";
	currentStage = NULL; //当前场景状态
	current_new_monsters = NULL;
	current_buttons = &void_buttons;
	buttons_before.clear();
	
	//清空物品栏
	for (int i = 0; i < items.size(); i++) {
		delete items[i];
	}
	items.clear();

	current_item = NULL;	//当前物品
	show_name_item = NULL;
	item_name_fading_time = 0;
	player = NULL;		//玩家


	current_reachable = nullptr;
	current_bg = nullptr;
	current_obj = nullptr;

	current_npcs = NULL;

	in_conversation = false;	//当前游戏处在对话状态
	in_stop = false;
	in_help = false;
	in_failed = false;
	in_bed = false;
	is_last_time_in_bed = false;
	converstaion_content = nullptr;	//当前对话的内容
}

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

	AllInit();

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
			if (in_global_achievement) {
				HandleGlobalAchievementEvents(hWnd);
			}
			else {
				HandleStopEvents(hWnd);
			}
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

	for (int i = 0; i < current_buttons->size(); i++)
	{
		Button* button = current_buttons->at(i);

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
				InitStage(hWnd, STAGE_STARTMENU); //内部有invalidate
				break;
			}
			case BUTTON_STARTGAME:
			{
				AllInit();
				InitStage(hWnd, STAGE_MAIN);
				break;
			}
			case BUTTON_HELP:
			{
				HandleHelpEvents(hWnd);
				break;
			}
			case BUTTON_GLOBAL_ACHIEVEMENT:
			{
				HandleGlobalAchievementEvents(hWnd);
				break;
			}
			case BUTTON_FAILED_RESTART:
			{
				AllInit();
				InitStage(hWnd, STAGE_MAIN);
				break;
			}
			case BUTTON_BED_CONTINUE:
			{
				HandleBedEvents(hWnd);
				break;
			}
			case BUTTON_BED_END:
			{
				InitStage(hWnd, STAGE_END);
				break;
			}
			case BUTTON_END_BACK:
			{
				InitStage(hWnd, STAGE_STARTMENU); //内部有invalidate
				break;
			}
			break;
			}
		}
	}


	if(in_help){

	} else if (in_stop) {


	}else if (currentStage->stageID == STAGE_STARTMENU) {

	}
	else if (currentStage->stageID == STAGE_END) {

	}
	else {
		//点到了任务栏

		// 定义任务栏的大小和间距
		int width = ITEM_BAR_SIZE_X;   // 每个任务栏项的宽度
		int height = ITEM_BAR_SIZE_Y;  // 每个任务栏项的高度
		int margin = ITEM_BAR_MARGIN;   // 每个任务栏项之间的间距

		// 计算任务栏项的起始位置（居中）
		int startX = (WINDOW_WIDTH - (width * 3 + margin * 2)) / 2;  // 水平居中
		int yPos = WINDOW_HEIGHT - height - 45;    // 设置垂直位置（距离窗口底部）

		int clickedIndex = -1;

		for (int i = 0; i < 3; i++) {
			int xPos = startX + i * (width + margin);  // 计算每个任务栏项的水平位置

			// 判断鼠标点击是否在当前任务栏项范围内
			if (mouseX >= xPos && mouseX <= xPos + width && mouseY >= yPos && mouseY <= yPos + height) {
				clickedIndex = i;  // 如果点击在当前任务栏项范围内，记录点击的任务栏项索引
				break;  // 结束循环，因为只需要找到第一个点击的任务栏项
			}
		}

		if (clickedIndex != -1) {//点到了
			char buff[256];
			sprintf(buff, "clicked: %d\n", clickedIndex);
			OutputDebugStringA(buff);
			if (clickedIndex < items.size()) {
				//点到了实际存在的
				if (current_item == items[clickedIndex]) { //如果已经拿到了就取下来
					current_item = NULL;
				}
				else {
					current_item = items[clickedIndex];
					show_name_item = current_item;
					item_name_fading_time = ITEM_NAME_FADING;
				}
			}
			else {
				//点到了空的，就不拿东西
				current_item = NULL;
			}
			return;
		}

		//攻击
		for (int i = 0; i < current_new_monsters->size(); i++) {
			NewMonster* monster = current_new_monsters->at(i);

			if (monster->visible) {
				//TODO 碰撞了

				if (mouseX >= monster->x - monster->size_x && mouseX <= monster->x + monster->size_x &&
					mouseY >= monster->y - monster->size_y && mouseY <= monster->y + monster->size_y)
				{
					bool is_near = false;
					bool can_hurt = false;
					int damage = 0;
					if (player->x - HURT_RADIUS < monster->x && player->x + HURT_RADIUS > monster->x && player->y - HURT_RADIUS < monster->y && player->y + HURT_RADIUS > monster->y) {
						is_near = true;
					}



					if (current_item == NULL) {
						if (is_near == true) {
							can_hurt = true;
							damage = 1;
						}
						else {
							continue;
						}
					}
					else if (current_item->item_id == ITEM_BOW) {
						can_hurt = true;
						damage = 5;
					}
					else if (current_item->item_id == ITEM_SWORD) {
						if (is_near == true) {
							can_hurt = true;
							damage = 10;
						}
						else {
							continue;
						}
					}
					else {
						if (is_near == true) {
							can_hurt = true;
							damage = 1;
						}
						else {
							continue;
						}
					}

					if (can_hurt == true) {
						achievement_hurt_flag = true;
						monster->hurt = true;
						monster->hp -= damage;
						monster->hp_visible = true;
						monster->particles.push_back(new Particle(L"-" + to_wstring(damage) + L"HP"));

						AddEffect(monster, EFFECT_SPEED_UP_ID);

						char buff[256];
						sprintf(buff, "monster hp: %d\n", monster->hp);
						OutputDebugStringA(buff);
					}
				}
			}

		}
	}

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

	UpdatePlayer(hWnd);
	UpdateNPCs(hWnd);
	UpdateMonsters(hWnd);
	UpdateMaps(hWnd);
	ScanTasks(hWnd);
	UpdateHolding(hWnd);
	UpdateProgress();


	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}


bool CanMove(int x_before, int y_before, int x_after, int y_after, int size_x, int size_y, int player = false) { //player's x y

	//超过边界
	if (int(y_after + (0.5 * size_y)) / BLOCK_SIZE_Y >= 20 || y_after / BLOCK_SIZE_Y >= 20 || int(x_after + (0.5 * size_x)) / BLOCK_SIZE_X >= 28 || int(x_after - (0.5 * size_x)) / BLOCK_SIZE_X >= 28 ||
		int(y_after + (0.5 * size_y)) / BLOCK_SIZE_Y < 0 || y_after / BLOCK_SIZE_Y < 0 || int(x_after + (0.5 * size_x)) / BLOCK_SIZE_X < 0 || int(x_after - (0.5 * size_x)) / BLOCK_SIZE_X < 0) {
		//允许超过边界，其他逻辑来处理
		return true;
	}


	std::set<int> cannot_move = { 1 };

	if (player == true) {
		cannot_move.insert(2);
	}
	else {
		cannot_move.insert(3);
	}

	/*if ((current_reachable[int(y_after + (0.5 * size_y)) / BLOCK_SIZE_Y][int(x_after + (0.5 * size_x)) / BLOCK_SIZE_X] == 1 || current_reachable[int(y_after + (0.5 * size_y)) / BLOCK_SIZE_Y][int(x_after - (0.5 * size_x)) / BLOCK_SIZE_X] == 1) || (current_reachable[y_after / BLOCK_SIZE_Y][int(x_after + (0.5 * size_x)) / BLOCK_SIZE_X] == 1 || current_reachable[y_after / BLOCK_SIZE_Y][int(x_after - (0.5 * size_x)) / BLOCK_SIZE_X] == 1)) {
		return false;
	}*/

	if (cannot_move.count((*current_reachable)[int(y_after + (0.5 * size_y)) / BLOCK_SIZE_Y][int(x_after + (0.5 * size_x)) / BLOCK_SIZE_X]) > 0 || 
		cannot_move.count((*current_reachable)[int(y_after + (0.5 * size_y)) / BLOCK_SIZE_Y][int(x_after - (0.5 * size_x)) / BLOCK_SIZE_X]) > 0 ||
		cannot_move.count((*current_reachable)[y_after / BLOCK_SIZE_Y][int(x_after + (0.5 * size_x)) / BLOCK_SIZE_X]) > 0 ||
		cannot_move.count((*current_reachable)[y_after / BLOCK_SIZE_Y][int(x_after - (0.5 * size_x)) / BLOCK_SIZE_X]) > 0) {

		return false;
	}

	//monster的碰撞在update中更新，不在这里做，这里当作npcs是墙面。
	//那直接把npcs的位置做成墙 不方便

	for (int i = 0; i < current_npcs->size(); i++) {
		if (current_npcs->at(i)->visible) {
			if (current_npcs->at(i)->x - (0.5 * current_npcs->at(i)->size_x) < x_after + (0.5 * size_x) && current_npcs->at(i)->x + (0.5 * current_npcs->at(i)->size_x) > x_after - (0.5 * size_x) && current_npcs->at(i)->y - (0.5 * current_npcs->at(i)->size_y) < y_after + (0.5 * size_y) && current_npcs->at(i)->y + (0.5 * current_npcs->at(i)->size_y) > y_after - (0.5 * size_y)) {
				return false;
			}
		}
	}
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
			if (CanMove(player->x, player->y, player->x - player->vx, player->y, HUMAN_SIZE_X, HUMAN_SIZE_Y, true)) {
				player->x -= player->vx;
			}
			break;
		case UNIT_DIRECT_UP:
			if (CanMove(player->x, player->y, player->x, player->y - player->vy, HUMAN_SIZE_X, HUMAN_SIZE_Y, true)) {
				player->y -= player->vy;
			}
			break;
		case UNIT_DIRECT_RIGHT:
			if (CanMove(player->x, player->y, player->x + player->vx, player->y, HUMAN_SIZE_X, HUMAN_SIZE_Y, true)) {
				player->x += player->vx;
			}
			break;
		case UNIT_DIRECT_DOWN:
			if (CanMove(player->x, player->y, player->x, player->y + player->vy, HUMAN_SIZE_X, HUMAN_SIZE_Y, true)) {
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

void UpdateHolding(HWND hWnd) {

	if (current_item == NULL) {
		if (currentStage->stageID == STAGE_MAIN) {
			reachable_main[7][21] = 1;
			reachable_main[7][22] = 1;
		}

		return;
	}

	if (current_item->item_id == ITEM_CERTIFICATE) {
		if (currentStage->stageID == STAGE_MAIN) {
			if (npcs_main.at(1)->task_state == 0) {
				npcs_main.at(1)->ToConversation(1);
			}
		}
	}
	else if (current_item->item_id == ITEM_KEY) {
		if (currentStage->stageID == STAGE_MAIN) {
			reachable_main[7][21] = 3;
			reachable_main[7][22] = 3;
		}
	}

}

//更新NPC状态
void UpdateNPCs(HWND hWnd) {

	//顺次更新每个npc
	for (int i = 0; i < current_npcs->size(); i++) {
		//动画运行到下一帧
		(*current_npcs)[i]->frame_id++;
		(*current_npcs)[i]->frame_id = (*current_npcs)[i]->frame_id % (*current_npcs)[i]->frame_count;
		(*current_npcs)[i]->frame_column = (*current_npcs)[i]->frame_sequence[(*current_npcs)[i]->frame_id];

		//更新fig particle
		for (auto it = (*current_npcs)[i]->fig_particles.begin(); it != (*current_npcs)[i]->fig_particles.end(); ) {

			FigParticle* particle = (*it);

			particle->frame_id++;

			if (particle->frame_id >= particle->frame_count) {//超过了
				if (particle->infinity == true) {
					particle->frame_id = 0;
				}
				else {
					//删除！！
					delete particle;
					it = (*current_npcs)[i]->fig_particles.erase(it); // 删除粒子并更新迭代器

					char buff[256];
					sprintf(buff, "delete fig_par\n");
					OutputDebugStringA(buff);

					continue;
				}
			}

			it++;
		}
	}
}
void UpdateMonsters(HWND hWnd)
{

	//顺次更新每个怪物
	for (int i = 0; i < current_new_monsters->size(); i++) {

		NewMonster* monster = (*current_new_monsters)[i];


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

		for (auto it = monster->fig_particles.begin(); it != monster->fig_particles.end(); ) {

			FigParticle* particle = (*it);

			particle->frame_id++;

			if (particle->frame_id >= particle->frame_count) {//超过了
				if (particle->infinity == true) {
					particle->frame_id = 0;
				}
				else {
					//删除！！
					delete particle;
					it = monster->fig_particles.erase(it); // 删除粒子并更新迭代器

					char buff[256];
					sprintf(buff, "delete fig_par\n");
					OutputDebugStringA(buff);

					continue;
				}
			}

			it++;
		}


		if (monster->visible == false) {
			continue;
		}

        /*if (monster->x / BLOCK_SIZE_X < 0 || monster->x / BLOCK_SIZE_X > 27 || monster->y / BLOCK_SIZE_Y < 0 || monster->y / BLOCK_SIZE_Y > 19) {
			monster->visible = false;//放到handel failed event里面处理
        }*/
		//判断位置是否归巢
		if ((*current_reachable)[monster->y / BLOCK_SIZE_Y][monster->x / BLOCK_SIZE_X] == 5) {
			if (monster->effects.size() == 0) { //没有状态时才有用
				monster->state = MONSTER_STATE_HOME;
			}
		}else if(monster->state == MONSTER_STATE_HOME){
			monster->state = MONSTER_STATE_MOVE;
			monster->time_count = - 1; //重新加载
		}


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
				if (CanMove(monster->x, monster->y, monster->x - monster->vx, monster->y, monster->size_x, monster->size_y)) {
					monster->x -= monster->vx;
				}
				else {
					monster->time_count = monster->time_stop - 1; //跳过本回合
				}
				break;
			case UNIT_DIRECT_UP:
				monster->frame_row = UNIT_DIRECT_UP;
				if (CanMove(monster->x, monster->y, monster->x, monster->y - monster->vy, monster->size_x, monster->size_y)) {
					monster->y -= monster->vy;
				}
				else {
					monster->time_count = monster->time_stop - 1; //跳过本回合
				}
				break;
			case UNIT_DIRECT_RIGHT:
				monster->frame_row = UNIT_DIRECT_RIGHT;
				if (CanMove(monster->x, monster->y, monster->x + monster->vx, monster->y, monster->size_x, monster->size_y)) {
					monster->x += monster->vx;
				}
				else {
					monster->time_count = monster->time_stop - 1; //跳过本回合
				}
				break;
			case UNIT_DIRECT_DOWN:
				monster->frame_row = UNIT_DIRECT_DOWN;
				if (CanMove(monster->x, monster->y, monster->x, monster->y + monster->vy, monster->size_x, monster->size_y)) {
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

		//检查死亡
		if (monster->hp <= 0) {
			monster->visible = false;
			monster->hp_visible = false;
			monster->fig_particles.push_back(new FigParticle(ANI_DEATH));
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
				if (CanMove(player->x, player->y, player->x - player->vx, player->y, HUMAN_SIZE_X, HUMAN_SIZE_Y, true)) {
					player->x -= player->vx;
				}
				if (CanMove(monster->x, monster->y, monster->x + player->vx, monster->y, monster->size_x, monster->size_y)) {
					monster->x += player->vx;
				}
				break;
			case UNIT_DIRECT_LEFT:
				if (CanMove(player->x, player->y, player->x + player->vx, player->y, HUMAN_SIZE_X, HUMAN_SIZE_Y, true)) {
					player->x += player->vx;
				}
				if (CanMove(monster->x, monster->y, monster->x - player->vx, monster->y, monster->size_x, monster->size_y)) {
					monster->x -= player->vx;
				}
				break;
			case UNIT_DIRECT_DOWN:
				if (CanMove(player->x, player->y, player->x, player->y - player->vy, HUMAN_SIZE_X, HUMAN_SIZE_Y, true)) {
					player->y -= player->vy;
				}
				if (CanMove(monster->x, monster->y, monster->x, monster->y + player->vy, monster->size_x, monster->size_y)) {
					monster->y += player->vy;
				}
				break;
			case UNIT_DIRECT_UP:
				if (CanMove(player->x, player->y, player->x, player->y + player->vy, HUMAN_SIZE_X, HUMAN_SIZE_Y, true)) {
					player->y += player->vy;
				}
				if (CanMove(monster->x, monster->y, monster->x, monster->y - player->vy, monster->size_x, monster->size_y)) {
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

	if (currentStage->stageID == STAGE_MAIN && (player->x / BLOCK_SIZE_X == 4 || player->x / BLOCK_SIZE_X == 5) && player->y/BLOCK_SIZE_Y == 9)
	{	
		player->y = BLOCK_SIZE_Y * 15;
		player->x = BLOCK_SIZE_X * 7;
		InitStage(hWnd, STAGE_HOUSE_1);
		return;
	}

	//to house 2
	if (currentStage->stageID == STAGE_MAIN && (player->x / BLOCK_SIZE_X == 21 || player->x / BLOCK_SIZE_X == 22) && player->y / BLOCK_SIZE_Y == 7)
	{
		player->y = BLOCK_SIZE_Y * 15;
		player->x = BLOCK_SIZE_X * 6;
		InitStage(hWnd, STAGE_HOUSE_2);
		return;
	}

	if (currentStage->stageID == STAGE_MAIN && player->x / BLOCK_SIZE_X >= 27)
	{
		player->x = BLOCK_SIZE_X * 1; // 将x设置为0，使其跑到屏幕最左边
		player->y = BLOCK_SIZE_Y * 17;
		InitStage(hWnd, STAGE_MEADOW);
		return;
	}
	
	if (currentStage->stageID == STAGE_HOUSE_1 && (player->x / BLOCK_SIZE_X == 6 || player->x / BLOCK_SIZE_X == 7 ) && player->y / BLOCK_SIZE_Y == 16)
	{
		player->x = BLOCK_SIZE_X * 5;
		player->y = BLOCK_SIZE_Y * 10;
		InitStage(hWnd, STAGE_MAIN);
		return;
	}

	if (currentStage->stageID == STAGE_MEADOW && player->x / BLOCK_SIZE_X <= 0)
	{
		player->x = BLOCK_SIZE_X * 26;
		player->y = BLOCK_SIZE_Y * 15;
		InitStage(hWnd, STAGE_MAIN);
		return;
	}

	if (currentStage->stageID == STAGE_HOUSE_2 && (player->x / BLOCK_SIZE_X == 5 || player->x / BLOCK_SIZE_X == 6) && player->y / BLOCK_SIZE_Y == 16)
	{
		player->x = BLOCK_SIZE_X * 22;
		player->y = BLOCK_SIZE_Y * 8;
		InitStage(hWnd, STAGE_MAIN);
		return;
	}

}

void ScanTasks(HWND hWnd) {//顺便判断胜利和结束

	if (currentStage->stageID == STAGE_MAIN) {

		if (current_npcs->at(1)->task_state == 1 &&
			//current_npcs->at(1)->next_conversation_id == current_npcs->at(1)->conversations[current_npcs->at(1)->task_state].size() - 1) {
			current_npcs->at(1)->is_finished == true) {
			progress_list.push_back(PRO_PEOPLE_KNOWN);
		}

	}
	else if (currentStage->stageID == STAGE_HOUSE_1) {

		bool homed_flag = true;
		for (int i = 0; i < current_new_monsters->size(); i++) {
			if ((*current_new_monsters)[i]->visible == false) {
				continue;
			}

			if ((*current_new_monsters)[i]->state != MONSTER_STATE_HOME) {
				progress_list.push_back(PRO_CHICKEN_UNHOMED);
				homed_flag = false;
			}
		}
		//完成任务
		if (homed_flag == true) {
			progress_list.push_back(PRO_CHICKEN_HOMED);
		}

		if (current_npcs->at(0)->task_state == 1 &&
			//current_npcs->at(0)->next_conversation_id == current_npcs->at(0)->conversations[current_npcs->at(0)->task_state].size() - 1) {
			current_npcs->at(0)->is_finished == true) {
			progress_list.push_back(PRO_GET_CERTIFICATE);
		}

		if (current_npcs->at(0)->task_state == 2 &&
			//current_npcs->at(0)->next_conversation_id == current_npcs->at(0)->conversations[current_npcs->at(0)->task_state].size() - 1) {
			current_npcs->at(0)->is_finished == true) {
			progress_list.push_back(PRO_GET_KEY);
		}


		//失败判定
		for (int i = 0; i < current_new_monsters->size(); i++) {
			NewMonster* monster = current_new_monsters->at(i);

			if (monster->visible == false && monster->monsterID == MONSTER_CHIKEN_ID) {
				//鸡死掉了
				HandleFailedEvents(hWnd, L"不能把鸡杀了！");
			}

			if (monster->visible == true && (monster->x / BLOCK_SIZE_X == 6 || monster->x / BLOCK_SIZE_X == 7) && monster->y / BLOCK_SIZE_Y == 16) {
				//到门口了
				HandleFailedEvents(hWnd, L"鸡跑出去了！");
			}

		}

	}
	else if (currentStage->stageID == STAGE_MEADOW) {

		if (current_npcs->at(0)->task_state == 0) {
			//if (current_npcs->at(0)->next_conversation_id == current_npcs->at(0)->conversations[current_npcs->at(0)->task_state].size() - 1) {
			if (current_npcs->at(0)->is_finished == true) {
				progress_list.push_back(PRO_GET_BOW);
			}
		}

		bool homed_flag = true;
		for (int i = 0; i < current_new_monsters->size(); i++) {
			if ((*current_new_monsters)[i]->visible == false) {
				continue;
			}
			if (((*current_new_monsters)[i]->monsterID == MONSTER_DUCK_ID && (*current_new_monsters)[i]->state != MONSTER_STATE_HOME) || ((*current_new_monsters)[i]->monsterID == MONSTER_CROW_ID && (*current_new_monsters)[i]->state == MONSTER_STATE_HOME)) {
				//没完成任务
				progress_list.push_back(PRO_DUCK_UNHOMED);
				homed_flag = false;
			}
		}
		if (homed_flag == true) {
			progress_list.push_back(PRO_DUCK_HOMED);
		}

		//失败判定
		for (int i = 0; i < current_new_monsters->size(); i++) {
			NewMonster* monster = current_new_monsters->at(i);

			if (monster->visible == true && (monster->x / BLOCK_SIZE_X < 0 || monster->x / BLOCK_SIZE_X > 27 || monster->y / BLOCK_SIZE_Y < 0 || monster->y / BLOCK_SIZE_Y > 19)) {
				if (monster->monsterID == MONSTER_DUCK_ID) {
					HandleFailedEvents(hWnd, L"鸭子跑出去了！");
				}
				else {
					monster->visible = false;
				}
			}


			if (monster->visible == false && monster->monsterID == MONSTER_DUCK_ID) {
				HandleFailedEvents(hWnd, L"不能把鸭子杀了！");
			}
		}
	}
	else if (currentStage->stageID == STAGE_HOUSE_2) {

		std::set<pair<int,int>> bed_block = {
			{23, 9},
			{22, 9},
			{21, 9},
			{21, 8},
			{21, 7},
		};

		if (bed_block.count({ player->x / BLOCK_SIZE_X, player->y / BLOCK_SIZE_Y }) > 0) {
			if (is_last_time_in_bed == false) {
				is_last_time_in_bed = true;
				HandleBedEvents(hWnd);
			}
		}
		else {
			is_last_time_in_bed = false;
		}
	}

};


//抬起空格时触发，开启对话
void HandleConversationEvents(HWND hWnd) 
{
	//当前已经开启对话，再按一次空格关闭
	if (in_conversation) {
		in_conversation = false;
		return;
	}
	//player与npc做碰撞检测，判断与哪个npc对话
	for (int i = 0; i < current_npcs->size(); i++) {
		NPC* npc = (*current_npcs)[i];
		if (((player->x <= npc->x && npc->x <= player->x + HUMAN_SIZE_X) || (npc->x <= player->x && player->x <= npc->x + HUMAN_SIZE_X)) &&
			((player->y <= npc->y && npc->y <= player->y + HUMAN_SIZE_Y) || (npc->y <= player->y && player->y <= npc->y + HUMAN_SIZE_X))) {
			in_conversation = true;
			npc->RemoveFigParticle(ANI_EXCLAMATION);

			converstaion_content = npc->conversations[npc->task_state][npc->next_conversation_id];
			if (npc->next_conversation_id == npc->conversations[npc->task_state].size() - 1) {
				npc->is_finished = true;
			}
			if (npc->next_conversation_id < npc->conversations[npc->task_state].size() - 1)
				npc->next_conversation_id++;	//npc的这句话已经说完，下次该说下一句话了；如果已经说到最后一句话了，则一直重复
		}
	}
}

void HandleStopEvents(HWND hWnd)
{
	if (currentStage->stageID != STAGE_STARTMENU) {

		if (in_stop == false) {
			in_stop = true;
			buttons_before.push_back(current_buttons);
			current_buttons = &stop_buttons;
			currentStage->timerOn = false;
		}
		else {
			in_stop = false;
			current_buttons = buttons_before.back();
			buttons_before.pop_back();
			currentStage->timerOn = true;
		}

		InvalidateRect(hWnd, NULL, FALSE);
	}

}

void HandleFailedEvents(HWND hWnd, std::wstring str)
{
	failed_message = str;
	in_failed = !in_failed;
	currentStage->timerOn = !currentStage->timerOn;
	
	current_buttons = &failed_buttons;

	InvalidateRect(hWnd, NULL, FALSE);
}


void HandleHelpEvents(HWND hWnd)
{


	if (in_help == false) {
		in_help = true;
		buttons_before.push_back(current_buttons);
		current_buttons = &void_buttons;
		currentStage->timerOn = false;
	}
	else {
		in_help = false;
		current_buttons = buttons_before.back();
		buttons_before.pop_back();
	}

	InvalidateRect(hWnd, NULL, FALSE);
}

void HandleGlobalAchievementEvents(HWND hWnd)
{


	if (in_global_achievement == false) {
		in_global_achievement = true;
		buttons_before.push_back(current_buttons);
		current_buttons = &void_buttons;
		currentStage->timerOn = false;
	}
	else {
		in_global_achievement = false;
		current_buttons = buttons_before.back();
		buttons_before.pop_back();
	}

	InvalidateRect(hWnd, NULL, FALSE);
}


void HandleBedEvents(HWND hWnd)
{

	if (in_bed == false) {
		in_bed = true;
		buttons_before.push_back(current_buttons);
		current_buttons = &bed_buttons;
		currentStage->timerOn = false;
	}
	else {
		in_bed = false;
		current_buttons = buttons_before.back();
		buttons_before.pop_back();
		currentStage->timerOn = true;
	}

	InvalidateRect(hWnd, NULL, FALSE);
}

// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{
	// 初始化场景实例

	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;



	if (stageID == STAGE_STARTMENU) {
		in_stop = false;
		in_help = false;
		in_bed = false;
		in_failed = false;

		currentStage->timerOn = false;
		current_buttons = &menu_buttons;
	}
	else if (stageID == STAGE_END) {
		in_stop = false;
		in_help = false;
		in_bed = false;
		in_failed = false;

		SummarizeAchievements();

		/*char buff[256];
		sprintf(buff, "ACHIEVEMENT_QUICK_SLEEP %d\n", achievement_record[ACHIEVEMENT_QUICK_SLEEP]);
		OutputDebugStringA(buff);

		sprintf(buff, "ACHIEVEMENT_FRIENDLY %d\n", achievement_record[ACHIEVEMENT_FRIENDLY]);
		OutputDebugStringA(buff);

		sprintf(buff, "ACHIEVEMENT_CROW_HUNTER %d\n", achievement_record[ACHIEVEMENT_CROW_HUNTER]);
		OutputDebugStringA(buff);

		sprintf(buff, "ACHIEVEMENT_HELPFUL %d\n", achievement_record[ACHIEVEMENT_HELPFUL]);
		OutputDebugStringA(buff);*/

		currentStage->timerOn = false;
		current_buttons = &end_buttons;
	}
	else if (stageID == STAGE_MAIN)
	{

		current_bg = &bg_main;
		current_reachable = &reachable_main;
		current_obj = &obj_main;
		current_npcs = &npcs_main;
		current_new_monsters = &new_monsters_main;
		currentStage->timerOn = true;

		current_buttons = &void_buttons;

		if (player == NULL)
			player = CreatePlayer(400, 200);					//第一次调用：初始化player

	}
	else if (stageID == STAGE_HOUSE_1)
	{

		current_bg = &bg_house_1;
		current_reachable = &reachable_house_1;
		current_obj = &obj_house_1;

		current_npcs = &npcs_house_1;
		current_new_monsters = &new_monsters_house_1;
		currentStage->timerOn = true;

		current_buttons = &void_buttons;

		if (player == NULL)
			player = CreatePlayer(200, 200);


	}
	else if (stageID == STAGE_MEADOW) {

		current_bg = &bg_meadow;
		current_reachable = &reachable_meadow;
		current_obj = &obj_meadow;
		current_npcs = &npcs_meadow;
		current_new_monsters = &new_monsters_meadow;
		currentStage->timerOn = true;

		current_buttons = &void_buttons;

		if (player == NULL)
			player = CreatePlayer(200, 200);

	}
	else if (stageID == STAGE_HOUSE_2) {
		current_bg = &bg_house_2;
		current_reachable = &reachable_house_2;
		current_obj = &obj_house_2;

		current_npcs = &npcs_house_2;
		current_new_monsters = &new_monsters_house_2;
		currentStage->timerOn = true;

		current_buttons = &void_buttons;

		if (player == NULL)
			player = CreatePlayer(200, 200);
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

	if (currentStage->stageID == STAGE_STARTMENU) {
		SelectObject(hdc_loadBmp, bmp_background);
		TransparentBlt(
			hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, 0, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT,
			RGB(255, 255, 255));


		HFONT hFont = CreateFontW(
			20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
			L"SimSun");		//创建字体
		SelectObject(hdc_memBuffer, hFont);
		SetTextColor(hdc_memBuffer, RGB(0, 0, 0));
		SetBkMode(hdc_memBuffer, TRANSPARENT);
		RECT rect;
		rect.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
		rect.top = (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1 / 4;
		rect.right = (WINDOW_WIDTH - BUTTON_WIDTH) / 2 + BUTTON_WIDTH;
		rect.bottom = (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1 / 4 + BUTTON_HEIGHT;
		DrawTextW(hdc_memBuffer, L"开始菜单", -1, &rect, DT_CENTER | DT_VCENTER);

	}
	else if (currentStage->stageID == STAGE_END) {
		SelectObject(hdc_loadBmp, bmp_background);
		TransparentBlt(
			hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, 0, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT,
			RGB(255, 255, 255));

		//TODO 写字

		if (achievement_list.size() == 0) {
			HFONT hFont = CreateFontW(
				20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
				L"SimSun");		//创建字体
			SelectObject(hdc_memBuffer, hFont);
			SetTextColor(hdc_memBuffer, RGB(0, 0, 0));
			SetBkMode(hdc_memBuffer, TRANSPARENT);
			RECT rect;
			rect.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
			rect.top = (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1.7 / 4;
			rect.right = (WINDOW_WIDTH - BUTTON_WIDTH) / 2 + BUTTON_WIDTH;
			rect.bottom = (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1.7 / 4 + BUTTON_HEIGHT;
			DrawTextW(hdc_memBuffer, L"本次没有获得成就", -1, &rect, DT_CENTER | DT_VCENTER);

		}
		else {

			int content_margin = 5;

			//计算posY
			int content_height = achievement_list.size() * (ACHIEVE_HEIGHT + content_margin) - content_margin;
			int posX = 0.5 * (WINDOW_WIDTH - ACHIEVE_WIDTH);
			int posY = 0.5 * ((WINDOW_HEIGHT - BUTTON_HEIGHT) - content_height);

			while (!achievement_list.empty()) {

				Achievement* achievement = achievement_list.back();
				achievement_list.pop_back();

				//先画背景
				SelectObject(hdc_loadBmp, bmp_achievement_bg);
				TransparentBlt(
					hdc_memBuffer,
					posX, posY, ACHIEVE_WIDTH, ACHIEVE_HEIGHT, //TODO
					hdc_loadBmp, 0, 0, 125, 32,
					RGB(255, 255, 255));


				int content_left = posX + (0.5 * (ACHIEVE_HEIGHT - achievement->size_y));
				int content_right = posX + ACHIEVE_WIDTH - (0.5 * (ACHIEVE_HEIGHT - achievement->size_y));
				int content_top = posY + (0.5 * (ACHIEVE_HEIGHT - achievement->size_y));
				int content_bottom = posY + ACHIEVE_HEIGHT - (0.5 * (ACHIEVE_HEIGHT - achievement->size_y));

				// 选择图片
				SelectObject(hdc_loadBmp, achievement->img);
				TransparentBlt(
					hdc_memBuffer,
					content_left, content_top, achievement->size_x, achievement->size_y, //TODO
					hdc_loadBmp, 0, 0, achievement->bitmap_size_x, achievement->bitmap_size_y,
					RGB(255, 255, 255));

				// 创建字体
				HFONT hFont = CreateFontW(
					20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
					L"SimSun");		//创建字体
				SelectObject(hdc_memBuffer, hFont);
				SetTextColor(hdc_memBuffer, RGB(0, 0, 0));
				SetBkMode(hdc_memBuffer, TRANSPARENT);

				// 设置标题和描述的位置
				RECT rect_title;
				rect_title.left = content_left + achievement->size_x + 10;
				rect_title.top = content_top;
				rect_title.right = content_right;
				rect_title.bottom = content_bottom - (0.5 * achievement->size_y);
				DrawTextW(hdc_memBuffer, achievement->title.c_str(), -1, &rect_title, DT_CENTER | DT_VCENTER);

				// 设置描述的位置
				RECT rect_description;
				rect_description.left = content_left + achievement->size_x + 10;
				rect_description.top = content_top + (0.5 * achievement->size_y);
				rect_description.right = content_right;
				rect_description.bottom = content_bottom;
				DrawTextW(hdc_memBuffer, achievement->description.c_str(), -1, &rect_description, DT_CENTER | DT_VCENTER);

				// 更新起始位置，向下移动下一个成就
				posY = posY + ACHIEVE_HEIGHT + content_margin;
			}
		}

	} else {

		//首先绘制背景，背景只有一个块
		for (int i = 0; i < sizeof((*current_bg)) / sizeof((*current_bg)[0]); i++) {
			for (int j = 0; j < sizeof((*current_bg)[0]) / sizeof((*current_bg)[0][0]); j++) {

				//根据bg的值绘制不同的背景
				SelectObject(hdc_loadBmp, bg_hitmap[(*current_bg)[i][j]].bitmap);

				TransparentBlt(
					hdc_memBuffer,
					j * BLOCK_SIZE_X, i * BLOCK_SIZE_Y,							// 界面上起始绘制点
					BLOCK_SIZE_X, BLOCK_SIZE_Y,									// 界面上绘制宽度高度
					hdc_loadBmp,
					0,						// 位图上起始绘制点
					0,
					bg_hitmap[(*current_bg)[i][j]].bitmap_size_x, bg_hitmap[(*current_bg)[i][j]].bitmap_size_y,					// 位图上绘制宽度高度
					RGB(255, 255, 255));										// 位图上的哪个颜色会被视为背景
			}
		}

		vector<Drawable*> drawables;


		for (int i = 0; i < sizeof((*current_obj)) / sizeof((*current_obj)[0]); i++) {
			for (int j = 0; j < sizeof((*current_obj)[0]) / sizeof((*current_obj)[0][0]); j++) {

				if ((*current_obj)[i][j] == 0) {
					continue;
				}

				int num_x = obj_hitmap[(*current_obj)[i][j]].num_x;
				int num_y = obj_hitmap[(*current_obj)[i][j]].num_y;

				Drawable* obj = new Drawable();
				obj->img = obj_hitmap[(*current_obj)[i][j]].bitmap;
				obj->x = j * BLOCK_SIZE_X;
				obj->y = i * BLOCK_SIZE_Y;
				obj->size_x = BLOCK_SIZE_X * num_x;
				obj->size_y = BLOCK_SIZE_Y * num_y;
				obj->bmp_x = 0;
				obj->bmp_y = 0;
				obj->bmp_size_x = obj_hitmap[(*current_obj)[i][j]].bitmap_size_x * num_x;
				obj->bmp_size_y = obj_hitmap[(*current_obj)[i][j]].bitmap_size_y * num_y;
				obj->transparentColor = RGB(255, 255, 255);
				obj->weight_x = obj->x + obj_hitmap[(*current_obj)[i][j]].weight_offset_num_x * BLOCK_SIZE_X;
				obj->weight_y = obj->y + obj_hitmap[(*current_obj)[i][j]].weight_offset_num_y * BLOCK_SIZE_Y;
				drawables.push_back(obj);
			}
		}



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

		p->weight_x = p->x;
		p->weight_y = p->y + HUMAN_SIZE_Y; //TODO


		if (current_item != NULL) {
			Drawable* item = new Drawable();
			item->img = current_item->img;
			item->x = player->x - 0.5 * ITEM_SIZE_X;
			item->y = player->y - 0.5 * HUMAN_SIZE_Y - 0.5 * ITEM_SIZE_Y;
			item->size_x = ITEM_SIZE_X;
			item->size_y = ITEM_SIZE_Y;
			item->bmp_x = 0;
			item->bmp_y = 0;
			item->bmp_size_x = current_item->bitmap_size_x;
			item->bmp_size_y = current_item->bitmap_size_x;
			item->transparentColor = RGB(255, 255, 255);
			p->subdrawables.push_back(item);
		}
		drawables.push_back(p);


		for (int i = 0; i < current_npcs->size(); i++) {
			if ((*current_npcs)[i]->visible) {

				Drawable* n = new Drawable();

				n->img = (*current_npcs)[i]->img;
				n->x = (*current_npcs)[i]->x - 0.5 * HUMAN_SIZE_X;
				n->y = (*current_npcs)[i]->y - 0.5 * HUMAN_SIZE_Y;
				n->size_x = HUMAN_SIZE_X;
				n->size_y = HUMAN_SIZE_Y;
				n->bmp_x = HUMAN_BITMAP_SIZE_X * (*current_npcs)[i]->frame_column;
				n->bmp_y = HUMAN_BITMAP_SIZE_Y * (*current_npcs)[i]->frame_row;
				n->bmp_size_x = HUMAN_BITMAP_SIZE_X;
				n->bmp_size_y = HUMAN_BITMAP_SIZE_Y;
				n->transparentColor = RGB(255, 255, 255);

				n->weight_x = n->x;
				n->weight_y = n->y + HUMAN_SIZE_Y;

				for (int j = 0; j < (*current_npcs)[i]->fig_particles.size(); j++) {
					Drawable* animation = new Drawable();

					FigParticle* particle = (*current_npcs)[i]->fig_particles[j];

					animation->img = particle->img;
					animation->x = ((*current_npcs)[i]->x - 0.5 * particle->size_x) + particle->offset_x; //前半部分保证画在人物中心
					animation->y = n->y + particle->offset_y; //n->y是人物头顶
					animation->size_x = particle->size_x;
					animation->size_y = particle->size_y;
					animation->bmp_x = particle->frame_sequence->at(particle->frame_id) * particle->bitmap_size_x;
					animation->bmp_y = 0;
					animation->bmp_size_x = particle->bitmap_size_x;
					animation->bmp_size_y = particle->bitmap_size_y;
					animation->transparentColor = RGB(255, 255, 255);
					n->subdrawables.push_back(animation);
				}
					
				drawables.push_back(n);
			}
		}



		for (int i = 0; i < current_new_monsters->size(); i++) {
			if ((*current_new_monsters)[i]->visible || ((*current_new_monsters)[i]->visible==false && (*current_new_monsters)[i]->fig_particles.size()!=0)) {

				NewMonster* monster = (*current_new_monsters)[i];

				Drawable* m = new Drawable();

				m->visible = (*current_new_monsters)[i]->visible;
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

				m->weight_x = m->x;
				m->weight_y = m->y + monster->size_y;

				for (int j = 0; j < monster->fig_particles.size(); j++) {
					Drawable* animation = new Drawable();

					FigParticle* particle = monster->fig_particles[j];

					animation->img = particle->img;
					animation->x = (monster->x - 0.5 * particle->size_x) + particle->offset_x;
					animation->y = m->y + particle->offset_y;
					animation->size_x = particle->size_x;
					animation->size_y = particle->size_y;
					animation->bmp_x = particle->frame_sequence->at(particle->frame_id) * particle->bitmap_size_x;
					animation->bmp_y = 0;
					animation->bmp_size_x = particle->bitmap_size_x;
					animation->bmp_size_y = particle->bitmap_size_y;
					animation->transparentColor = RGB(255, 255, 255);
					m->subdrawables.push_back(animation);
				}

				drawables.push_back(m);
			}
		}


		//绘制drawable
		std::sort(drawables.begin(), drawables.end(), [](const Drawable* a, const Drawable* b) {
			//return (a->y + (BLOCK_SIZE_Y * 0.5)) < (b->y + (BLOCK_SIZE_Y * 0.5));
			return a->weight_y < b->weight_y;
		});

		for (const auto drawable : drawables) {

			if (drawable->visible == true) {
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
			}

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
			if ((*current_new_monsters)[i]->visible || 
				((*current_new_monsters)[i]->visible==false && ((*current_new_monsters)[i]->particles.size()!=0))) {

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

		//画物品栏

		//画背景
		int width = ITEM_BAR_SIZE_X;    // 绘制在画布上的宽度（缩小为 40px）
		int height = ITEM_BAR_SIZE_Y;   // 绘制在画布上的高度（缩小为 40px）
		int margin = ITEM_BAR_MARGIN;      // 每个图像之间的间距

		SelectObject(hdc_loadBmp, bmp_item_bg);
		int startX = (WINDOW_WIDTH - (width * 3 + margin * 2)) / 2; // 水平居中
		for (int i = 0; i < 3; i++) {
			int xPos = startX + i * (width + margin);  // 计算水平位置
			int yPos = WINDOW_HEIGHT - height - 45;    // 设置垂直位置

			// 使用 TransparentBlt 绘制图像，透明色为 RGB(255, 255, 255)（白色）
			TransparentBlt(
				hdc_memBuffer,         // 目标 HDC
				xPos, yPos,           // 目标绘制位置
				width, height,  // 绘制尺寸
				hdc_loadBmp,        // 源 HDC（包含缩放后的图像）
				0, 0,                 // 源位置
				width, height,  // 源尺寸
				RGB(255, 255, 255)    // 透明色（假设白色为透明）
			);
		}

		int item_width = ITEM_SIZE_X;
		int item_height = ITEM_SIZE_Y;

		//画物品
		for (int i = 0; i < items.size(); i++) {
			SelectObject(hdc_loadBmp, items[i]->img);
			int xPos = startX + i * (width + margin);  // 计算水平位置
			int yPos = WINDOW_HEIGHT - height - 45;    // 设置垂直位置

			TransparentBlt(
				hdc_memBuffer,         // 目标 HDC
				xPos + 0.5 * (width - item_width), yPos + 0.5 * (height - item_height),           // 目标绘制位置
				item_width, item_height,  // 绘制尺寸
				hdc_loadBmp,        // 源 HDC（包含缩放后的图像）
				0, 0,                 // 源位置
				items[i]->bitmap_size_x, items[i]->bitmap_size_y,  // 源尺寸
				RGB(255, 255, 255)    // 透明色（假设白色为透明）
			);

			if (show_name_item == items[i] && item_name_fading_time > 0) {
				SelectObject(hdc_loadBmp, bmp_item_name_bg);
				TransparentBlt(
					hdc_memBuffer,
					xPos - 0.5 * (ITEM_NAME_SIZE_X - ITEM_BAR_SIZE_X), yPos - ITEM_NAME_SIZE_Y - 10, ITEM_NAME_SIZE_X, ITEM_NAME_SIZE_Y,					// 界面上绘制位置
					hdc_loadBmp,
					0, 0, ITEM_NAME_SIZE_X, ITEM_NAME_SIZE_Y,	// 位图上绘制位置
					RGB(255, 255, 255)
				);
				//绘制文字
				HFONT hFont = CreateFontW(
					20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
					L"SimSun");		//创建字体
				SelectObject(hdc_memBuffer, hFont);
				SetTextColor(hdc_memBuffer, RGB(0, 0, 0));	// 设置颜色:黑色字体白色背景
				SetBkMode(hdc_memBuffer, TRANSPARENT);
				RECT rect;
				rect.left = xPos - 0.5 * (ITEM_NAME_SIZE_X - ITEM_BAR_SIZE_X);
				rect.top = yPos - ITEM_NAME_SIZE_Y + 3;
				rect.right = rect.left + ITEM_NAME_SIZE_X;
				rect.bottom = rect.top + ITEM_NAME_SIZE_Y;
				DrawTextW(hdc_memBuffer, show_name_item->description.c_str(), -1, &rect, DT_CENTER | DT_VCENTER);

				item_name_fading_time--;
				char buff[256];

			}

		}


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


	//最后加上透明度
	if (in_stop) {
		SelectObject(hdc_loadBmp, bmp_background);
		DrawTransparentBitmap(hdc_memBuffer, hdc_loadBmp, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT, 200);
	}

	if (in_help) {
		//TODO

		SelectObject(hdc_loadBmp, bmp_background);
		DrawTransparentBitmap(hdc_memBuffer, hdc_loadBmp, 0, 0, WINDOW_WIDTH*0.2, WINDOW_HEIGHT*0.2, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT, 200);

	}

	if (in_failed) {
		SelectObject(hdc_loadBmp, bmp_background);
		DrawTransparentBitmap(hdc_memBuffer, hdc_loadBmp, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT, 200);

		HFONT hFont = CreateFontW(
			20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
			L"SimSun");		//创建字体
		SelectObject(hdc_memBuffer, hFont);
		SetTextColor(hdc_memBuffer, RGB(0, 0, 0));
		SetBkMode(hdc_memBuffer, TRANSPARENT);
		RECT rect;
		rect.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
		rect.top = (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1 / 4;
		rect.right = (WINDOW_WIDTH - BUTTON_WIDTH) / 2 + BUTTON_WIDTH;
		rect.bottom = (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1 / 4 + BUTTON_HEIGHT;
		DrawTextW(hdc_memBuffer, failed_message.c_str(), -1, &rect, DT_CENTER | DT_VCENTER);
	}

	if (in_bed) {
		SelectObject(hdc_loadBmp, bmp_background);
		DrawTransparentBitmap(hdc_memBuffer, hdc_loadBmp, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT, 200);

		HFONT hFont = CreateFontW(
			20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
			L"SimSun");		//创建字体
		SelectObject(hdc_memBuffer, hFont);
		SetTextColor(hdc_memBuffer, RGB(0, 0, 0));
		SetBkMode(hdc_memBuffer, TRANSPARENT);
		RECT rect;
		rect.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
		rect.top = (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1 / 4;
		rect.right = (WINDOW_WIDTH - BUTTON_WIDTH) / 2 + BUTTON_WIDTH;
		rect.bottom = (WINDOW_HEIGHT - BUTTON_HEIGHT) * 1 / 4 + BUTTON_HEIGHT;
		DrawTextW(hdc_memBuffer, L"要结束游戏吗", -1, &rect, DT_CENTER | DT_VCENTER);
	}

	if (in_global_achievement) {
		SelectObject(hdc_loadBmp, bmp_background);
		DrawTransparentBitmap(hdc_memBuffer, hdc_loadBmp, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT, 200);

		int content_margin = 5;

		//计算posY
		int content_height = global_achievements.size() * (ACHIEVE_HEIGHT + content_margin) - content_margin;
		int posX = 0.5 * (WINDOW_WIDTH - ACHIEVE_WIDTH);
		int posY = 0.5 * ((WINDOW_HEIGHT - BUTTON_HEIGHT) - content_height);

		for(int i=0;i < global_achievements.size();i++){

			Achievement* achievement = global_achievements[i];

			//先画背景
			SelectObject(hdc_loadBmp, bmp_achievement_bg);
			TransparentBlt(
				hdc_memBuffer,
				posX, posY, ACHIEVE_WIDTH, ACHIEVE_HEIGHT, //TODO
				hdc_loadBmp, 0, 0, 125, 32,
				RGB(255, 255, 255));


			int content_left = posX + (0.5 * (ACHIEVE_HEIGHT - achievement->size_y));
			int content_right = posX + ACHIEVE_WIDTH - (0.5 * (ACHIEVE_HEIGHT - achievement->size_y));
			int content_top = posY + (0.5 * (ACHIEVE_HEIGHT - achievement->size_y));
			int content_bottom = posY + ACHIEVE_HEIGHT - (0.5 * (ACHIEVE_HEIGHT - achievement->size_y));


			if (global_achievement_record[achievement->achieve_id] == true) {
				//拿到了成就，正常显示
				
				// 选择图片
				SelectObject(hdc_loadBmp, achievement->img);
				TransparentBlt(
					hdc_memBuffer,
					content_left, content_top, achievement->size_x, achievement->size_y, //TODO
					hdc_loadBmp, 0, 0, achievement->bitmap_size_x, achievement->bitmap_size_y,
					RGB(255, 255, 255));

				// 创建字体
				HFONT hFont = CreateFontW(
					20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
					L"SimSun");		//创建字体
				SelectObject(hdc_memBuffer, hFont);
				SetTextColor(hdc_memBuffer, RGB(0, 0, 0));
				SetBkMode(hdc_memBuffer, TRANSPARENT);

				// 设置标题和描述的位置
				RECT rect_title;
				rect_title.left = content_left + achievement->size_x + 10;
				rect_title.top = content_top;
				rect_title.right = content_right;
				rect_title.bottom = content_bottom - (0.5 * achievement->size_y);
				DrawTextW(hdc_memBuffer, achievement->title.c_str(), -1, &rect_title, DT_CENTER | DT_VCENTER);

				// 设置描述的位置
				RECT rect_description;
				rect_description.left = content_left + achievement->size_x + 10;
				rect_description.top = content_top + (0.5 * achievement->size_y);
				rect_description.right = content_right;
				rect_description.bottom = content_bottom;
				DrawTextW(hdc_memBuffer, achievement->description.c_str(), -1, &rect_description, DT_CENTER | DT_VCENTER);
			}
			else {
				//没拿到成就，显示问号

				HFONT hFont = CreateFontW(
					20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
					L"SimSun");		//创建字体
				SelectObject(hdc_memBuffer, hFont);
				SetTextColor(hdc_memBuffer, RGB(0, 0, 0));
				SetBkMode(hdc_memBuffer, TRANSPARENT);

				// 设置标题和描述的位置
				RECT rect_title;
				rect_title.left = content_left;
				rect_title.top = content_top;
				rect_title.right = content_right;
				rect_title.bottom = content_bottom;
				DrawTextW(hdc_memBuffer, L"???", -1, &rect_title, DT_CENTER | DT_VCENTER);

			}

			// 更新起始位置，向下移动下一个成就
			posY = posY + ACHIEVE_HEIGHT + content_margin;
		}

	}

	char buff[256];
	sprintf(buff, "here %d %d %d %d\n", in_stop, in_help, in_failed, in_bed);
	OutputDebugStringA(buff);

	//画按钮，最上层
	for (int i = 0; i < current_buttons->size(); i++)
	{
		Button* button = current_buttons->at(i);
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


	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}
