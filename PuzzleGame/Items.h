#pragma once
#include "PuzzleGame.h"

#define ITEM_SIZE_X 32
#define ITEM_SIZE_Y 32

#define ITEM_BAR_SIZE_X 64
#define ITEM_BAR_SIZE_Y 64
#define ITEM_BAR_MARGIN 5

#define ITEM_NAME_FADING 100
#define ITEM_NAME_SIZE_X 188
#define ITEM_NAME_SIZE_Y 48

#define HURT_RADIUS 50

class Item
{
public:
	int item_id;
	HBITMAP img;
	int bitmap_size_x;
	int bitmap_size_y;
	std::wstring description;

	Item()
	{
		this->item_id = 0;
		this->img = NULL;
		this->bitmap_size_x = 0;
		this->bitmap_size_y = 0;
		this->description = L"";
	}

	Item(int item_id, HBITMAP img, int bitmap_size_x, int bitmap_size_y, std::wstring description)
	{
		this->item_id = item_id;
		this->img = img;
		this->bitmap_size_x = bitmap_size_x;
		this->bitmap_size_y = bitmap_size_y;
		this->description = description;
	}

	Item(int item_id) {
		switch (item_id)
		{
		case ITEM_CERTIFICATE: {
			this->item_id = item_id;
			this->img = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITEM_CERTIFICATE));
			this->bitmap_size_x = 16;
			this->bitmap_size_y = 16;
			this->description = L"老村长给的证书";
			break;
		}
		case ITEM_SWORD: {
			this->item_id = item_id;
			this->img = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITEM_SWORD));
			this->bitmap_size_x = 16;
			this->bitmap_size_y = 16;
			this->description = L"打人很疼的棍子";
			break;
		}
		case ITEM_BOW: {
			this->item_id = item_id;
			this->img = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITEM_BOW));
			this->bitmap_size_x = 16;
			this->bitmap_size_y = 16;
			this->description = L"可以打很远的弹弓";
			break;
			break;
		}
		}
	}
};