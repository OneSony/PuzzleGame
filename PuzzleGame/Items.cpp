#include "Items.h"
#include "IDs.h"
#include "Resource.h"
#include <map>

std::map<int, HBITMAP> item_hitmap = {
	{ ITEM_CERTIFICATE, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITEM_CERTIFICATE))},
	{ ITEM_SWORD, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITEM_SWORD))},
	{ ITEM_BOW, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITEM_BOW))},
	{ ITEM_KEY, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITEM_KEY))}
};

Item::Item(int item_id) {
	switch (item_id)
	{
	case ITEM_CERTIFICATE: {
		this->item_id = item_id;
		this->img = item_hitmap[ITEM_CERTIFICATE];
		this->bitmap_size_x = 16;
		this->bitmap_size_y = 16;
		this->description = L"老村长给的证书";
		break;
	}
	case ITEM_SWORD: {
		this->item_id = item_id;
		this->img = item_hitmap[ITEM_SWORD];
		this->bitmap_size_x = 16;
		this->bitmap_size_y = 16;
		this->description = L"打人很疼的棍子";
		break;
	}
	case ITEM_BOW: {
		this->item_id = item_id;
		this->img = item_hitmap[ITEM_BOW];
		this->bitmap_size_x = 16;
		this->bitmap_size_y = 16;
		this->description = L"可以打很远的弹弓";
		break;
	}
	case ITEM_KEY: {
		this->item_id = item_id;
		this->img = item_hitmap[ITEM_KEY];
		this->bitmap_size_x = 16;
		this->bitmap_size_y = 16;
		this->description = L"回家的钥匙";
		break;
	}
	}
}