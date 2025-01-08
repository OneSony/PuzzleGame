#pragma once Particles
#include "PuzzleGame.h"

class Particle
{
public:
	int offset_x;
	int offset_y;
	int vx;
	int vy;
	int life_max;
	int life_count;

	wstring text;

	Particle(wstring text) {
		this->text = text;
		this->offset_x = 0;
		this->offset_y = 0;
		this->vx = 0;
		this->vy = 2;
		this->life_max = 15;
		this->life_count = 0;
		
		this->text = text;
	}
};


class FigParticle {
public:

	int particle_id;

	HBITMAP img;
	int bitmap_size_x;
	int bitmap_size_y;

	int size_x;
	int size_y;

	vector<int>* frame_sequence = nullptr;	//��ǰ��֡����
	int frame_count;		//֡���еĳ���
	int frame_id;			//��ǰ��ʾ����֡���еĵڼ�֡

	int offset_x;
	int offset_y;

	bool infinity;
	int life_max;
	int life_count;

	FigParticle(int particle_id);

	~FigParticle() {
		if (frame_sequence != nullptr) {
			delete frame_sequence;
			frame_sequence = nullptr;
		}
	}
};
