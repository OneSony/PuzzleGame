#pragma once

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			896+16		//游戏窗口宽度
#define WINDOW_HEIGHT			640+32		//游戏窗口高度

#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的ID
#define STAGE_HOUSE_1			2
#define STAGE_MEADOW			3
#define STAGE_FAILED			4


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
#define BUTTON_FAILED_RESTART 1006

#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		30		//默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					3.0		//单位行走速度

#define NPC_MAN1_ID				2001		//每个NPC的ID号
#define NPC_WOMAN1_ID			2002
#define NPC_MAN2_ID				2003
#define NPC_MEADOW_MAN_ID			2004
#define NPC_MAN3_ID				2005

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
#define OBJ_GRASS 20016
#define OBJ_CHERRY 20018
#define OBJ_TENT 20019
#define OBJ_GRASS_BLOCK 20020


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
#define BG_ROCK_1 40016
#define BG_ROCK_2 40017
#define BG_ROCK_3 40018
#define BG_ROCK_4 40019

#define ITEM_CERTIFICATE 60001
#define ITEM_SWORD 60002
#define ITEM_BOW 60003

#define ANI_DEATH 70001
#define ANI_EXCLAMATION 70002

