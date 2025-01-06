#pragma once

#include <map>
class Obj_info
{
public:
	HBITMAP bitmap;
	int bitmap_size_x;
	int bitmap_size_y;
	int num_x;
	int num_y;

	Obj_info()
		: bitmap(NULL), bitmap_size_x(0), bitmap_size_y(0), num_x(0), num_y(0) {}

	Obj_info(HBITMAP bitmap, int bitmap_size_x, int bitmap_size_y, int num_x, int num_y)
	{
		this->bitmap = bitmap;
		this->bitmap_size_x = bitmap_size_x;
		this->bitmap_size_y = bitmap_size_y;
		this->num_x = num_x;
		this->num_y = num_y;
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