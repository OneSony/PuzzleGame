#include "Particles.h"
#include "IDs.h"
#include "Resource.h"
#include <map>

std::map<int, HBITMAP> fig_particle_hitmap = {
	{ ANI_DEATH, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ANI_DEATH))},
	{ ANI_EXCLAMATION, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ANI_EXCLAMATION))},
};


FigParticle::FigParticle(int particle_id) {

	this->particle_id = particle_id;

	switch (particle_id) {
	case ANI_DEATH:
	{
		this->img = fig_particle_hitmap[ANI_DEATH];
		this->bitmap_size_x = 32;
		this->bitmap_size_y = 32;

		this->size_x = 32;
		this->size_y = 32;

		this->frame_sequence = new std::vector<int>;

		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 5; ++j) {
				this->frame_sequence->push_back(i);  // 每个数字重复 5 次
			}
		}

		this->frame_count = this->frame_sequence->size();
		this->frame_id = 0;

		this->offset_x = 0; //距离人物头顶中心点
		this->offset_y = 0;

		this->infinity = false;

		break;
	}
	case ANI_EXCLAMATION:
	{
		this->img = fig_particle_hitmap[ANI_EXCLAMATION];
		this->bitmap_size_x = 16;
		this->bitmap_size_y = 16;

		this->size_x = 32;
		this->size_y = 32;

		this->frame_sequence = new std::vector<int>;

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 10; ++j) {
				this->frame_sequence->push_back(i);  // 每个数字
			}
		}

		this->frame_count = this->frame_sequence->size();
		this->frame_id = 0;

		this->offset_x = 0;
		this->offset_y = -32;

		this->infinity = true;

		break;
	}
	}
}