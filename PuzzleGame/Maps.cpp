#include "PuzzleGame.h"
#include "Maps.h"
#include "Resource.h"
#include<map>


//map用于对一个objID和bitmapID的映射
std::map<int, Obj_info> obj_hitmap = {
    { OBJ_HOUSE_1, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_HOUSE_1)), 16, 16, 6, 7, 0, 4) },
	{ OBJ_BAR_H_LEFT, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_BAR_H_LEFT)), 16, 16, 1, 2, 0, 1)},
	{ OBJ_BAR_H_MID, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_BAR_H_MID)), 16, 16, 1, 2, 0, 1)},
	{ OBJ_BAR_H_RIGHT, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_BAR_H_RIGHT)), 16, 16, 1, 2, 0, 1)},
	{ OBJ_BAR_V_HEAD, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_BAR_V_HEAD)), 16, 16, 1, 2, 0, 1)},
	{ OBJ_BAR_V_TAIL, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_BAR_V_TAIL)), 16, 16, 1, 2, 0, 1)},
	{ OBJ_WALL_1, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_WALL_1)), 16, 16, 1, 3, 0, 1)},
	{ OBJ_TABLE_1, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_TABLE_1)), 16, 16, 5, 3, 0, 1)},
	{ OBJ_CHAIR_1, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_CHAIR_1)), 16, 16, 1, 2, 0, 1)},
	{ OBJ_SOFA_1, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_SOFA_1)), 16, 16, 2, 3, 0, 1)},
	{ OBJ_TV, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_TV)), 16, 16, 3, 3, 0, 1)},
	{ OBJ_CARPET_1, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_OBJ_CARPET_1)), 16, 16, 3, 2, 0, 0)},
};

std::map<int, Obj_info> bg_hitmap = {
	{ BG_BLACK, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BLACK)), 16, 16, 1, 1) },
	{ BG_GRASS, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_GRASS)), 16, 16, 1, 1) },
	{ BG_SAND, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_SAND)), 16, 16, 1, 1) },
	{ BG_FLOOR_1, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_FLOOR_1)), 32, 32, 1, 1) },
	{ BG_BARRIER_LEFT, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_LEFT)), 16, 16, 1, 1) },
	{ BG_BARRIER_RIGHT, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_RIGHT)), 16, 16, 1, 1) },
	{ BG_BARRIER_TOP, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_TOP)), 16, 16, 1, 1) },
	{ BG_BARRIER_BOTTOM, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_BOTTOM)), 16, 16, 1, 1) },
	{ BG_BARRIER_LEFT_TOP, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_LEFT_TOP)), 16, 16, 1, 1) },
	{ BG_BARRIER_LEFT_BOTTOM, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_LEFT_BOTTOM)), 16, 16, 1, 1) },
	{ BG_BARRIER_RIGHT_TOP, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_RIGHT_TOP)), 16, 16, 1, 1) },
	{ BG_BARRIER_RIGHT_BOTTOM, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_RIGHT_BOTTOM)), 16, 16, 1, 1) },
	{ BG_BARRIER_LEFT_TOP_R, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_LEFT_TOP_R)), 16, 16, 1, 1) },
	{ BG_BARRIER_LEFT_BOTTOM_R, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_LEFT_BOTTOM_R)), 16, 16, 1, 1) },
	{ BG_BARRIER_RIGHT_TOP_R, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_RIGHT_TOP_R)), 16, 16, 1, 1) },
	{ BG_BARRIER_RIGHT_BOTTOM_R, Obj_info(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG_BARRIER_RIGHT_BOTTOM_R)), 16, 16, 1, 1) },
};


int reachable_main[20][28] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
};

int bg_main[20][28] = {
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
};

int obj_main[20][28] = {
	{ OBJ_BAR_H_MID, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, OBJ_HOUSE_1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_TAIL,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD,},
	{ OBJ_BAR_H_MID, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID,},
};



int reachable_house_1[20][28] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 0, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 0, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
};


int bg_house_1[20][28] = {
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_TOP, BG_BARRIER_RIGHT_TOP, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_RIGHT, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_RIGHT_TOP_R, BG_FLOOR_1, BG_FLOOR_1, BG_BARRIER_LEFT_TOP_R, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_RIGHT_BOTTOM, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BARRIER_LEFT_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_BOTTOM, BG_BARRIER_RIGHT_BOTTOM, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK,},
	{ BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK, BG_BLACK,},
};

int obj_house_1[20][28] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, OBJ_WALL_1, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_CHAIR_1, OBJ_TABLE_1, 0, 0, 0, 0, OBJ_CHAIR_1, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, OBJ_CARPET_1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
};



int reachable_meadow[20][28] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
};

int bg_meadow[20][28] = {
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
	{ BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS, BG_GRASS,},
};


int obj_meadow[20][28] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_V_HEAD, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_RIGHT, 0, 0, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, OBJ_BAR_H_LEFT, OBJ_BAR_H_MID, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
};
