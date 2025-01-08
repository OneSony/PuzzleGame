#pragma once
#include <map>
#include <windows.h>
class Obj_info
{
public:
	HBITMAP bitmap;
	int bitmap_size_x;
	int bitmap_size_y;
	int num_x;
	int num_y;
	int weight_offset_num_x;
	int weight_offset_num_y;

	Obj_info()
	{
		this->bitmap = NULL;
		this->bitmap_size_x = 0;
		this->bitmap_size_y = 0;
		this->num_x = 0;
		this->num_y = 0;
		this->weight_offset_num_x = 0;
		this->weight_offset_num_y = 0;
	}

	Obj_info(HBITMAP bitmap, int bitmap_size_x, int bitmap_size_y, int num_x, int num_y, int weight_offset_num_x = 0, int weight_offset_num_y = 0)
	{
		this->bitmap = bitmap;
		this->bitmap_size_x = bitmap_size_x;
		this->bitmap_size_y = bitmap_size_y;
		this->num_x = num_x;
		this->num_y = num_y;
		this->weight_offset_num_x = weight_offset_num_x;
		this->weight_offset_num_y = weight_offset_num_y;
	}
};
extern std::map<int, Obj_info> obj_hitmap;
extern std::map<int, Obj_info> bg_hitmap;
extern int reachable_main[20][28];
extern int obj_main[20][28];
extern int bg_main[20][28];
extern int bg_house_1[20][28];
extern int obj_house_1[20][28];
extern int reachable_house_1[20][28];

extern int bg_meadow[20][28];
extern int obj_meadow[20][28];
extern int reachable_meadow[20][28];

void InitMaps();