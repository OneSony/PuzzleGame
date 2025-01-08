#include "NPCs.h"
#include "IDs.h"
#include "Resource.h"
#include <map>

int NPC_FRAMES_HOLD[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
int NPC_FRAMES_HOLD_COUNT = sizeof(NPC_FRAMES_HOLD) / sizeof(int);

std::map<int, HBITMAP> npc_hitmap = {
	{ NPC_MAN1_ID, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_NPC_MAN1))},
	{ NPC_MAN2_ID, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_NPC_MAN1))},
	{ NPC_MAN3_ID, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_NPC_MAN1))},
	{ NPC_MEADOW_MAN_ID, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_NPC_MAN1))},
};

NPC::NPC(int x, int y, int npc_id)
{
	this->npcID = npc_id;
	this->visible = true;
	this->task_state = 0;
	this->x = x;
	this->y = y;
	this->direction = UNIT_DIRECT_DOWN;
	this->vx = 0;
	this->vy = 0;
	this->state = UNIT_STATE_HOLD;
	this->frame_row = this->direction;
	this->frame_column = 0;
	this->frame_sequence = NPC_FRAMES_HOLD;
	this->frame_count = NPC_FRAMES_HOLD_COUNT;
	this->frame_id = 0;
	this->next_conversation_id = 0;
	//根据不同NPC初始化不同的图像和对话
	switch (npc_id)
	{
	case NPC_MAN1_ID: {
		this->img = npc_hitmap[NPC_MAN1_ID];

		this->size_x = 19;
		this->size_y = 26;

		std::vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"你是新来的村长吗？");
		conversations_1.push_back(L"你去探望一下绿色房子里的人吧");
		this->conversations.push_back(conversations_1);

		break;
	}
	case NPC_MAN2_ID: {
		this->img = npc_hitmap[NPC_MAN2_ID];

		this->size_x = 19;
		this->size_y = 26;

		std::vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"可以帮我把鸡赶回到地毯上吗");
		this->conversations.push_back(conversations_1);

		std::vector<const wchar_t*> conversations_2;
		conversations_2.push_back(L"谢谢你！它们现在很舒服");
		conversations_2.push_back(L"这是你的工作证，拿去吧");
		this->conversations.push_back(conversations_2);

		std::vector<const wchar_t*> conversations_3;
		conversations_3.push_back(L"你又把它们赶下来干嘛！");
		this->conversations.push_back(conversations_3);

		std::vector<const wchar_t*> conversations_4;
		conversations_4.push_back(L"它们还是在地毯上比较好");
		this->conversations.push_back(conversations_4);

		break;
	}
	case NPC_MAN3_ID: {
		this->img = npc_hitmap[NPC_MAN3_ID];

		this->size_x = 19;
		this->size_y = 26;

		std::vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"你是谁？");
		conversations_1.push_back(L"我不认识你，你不可以过去！");
		this->conversations.push_back(conversations_1);

		std::vector<const wchar_t*> conversations_2;
		conversations_2.push_back(L"原来你是新来的村长");
		conversations_2.push_back(L"这边是牧场，但是出了点问题");
		conversations_2.push_back(L"你去看看吧");
		this->conversations.push_back(conversations_2);

		std::vector<const wchar_t*> conversations_3;
		conversations_3.push_back(L"谢谢你！帮我们");
		this->conversations.push_back(conversations_3);

		break;
	}
	case NPC_MEADOW_MAN_ID: {
		this->img = npc_hitmap[NPC_MEADOW_MAN_ID];

		this->size_x = 19;
		this->size_y = 26;

		std::vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"快来帮帮我吧，鸭圈里面进了乌鸦");
		conversations_1.push_back(L"帮我把乌鸦赶出来");
		conversations_1.push_back(L"这个弹弓你试试");
		conversations_1.push_back(L"帮我把乌鸦赶出来再把鸭子赶回去吧");
		this->conversations.push_back(conversations_1);


		std::vector<const wchar_t*> conversations_2;
		conversations_2.push_back(L"谢谢你把乌鸦赶走");
		this->conversations.push_back(conversations_2);

		break;
	}
	default:

		break;
	}
}

void NPC::AddFigParticle(int particle_id) {
	//如果没有item certificate再添加
	bool has = false;
	for (const auto& p : this->fig_particles) {
		if (p->particle_id == particle_id) {
			has = true;
			break;
		}
	}
	if (!has) {
		this->fig_particles.push_back(new FigParticle(particle_id));
	}
}

void NPC::RemoveFigParticle(int particle_id) {
	for (auto it = this->fig_particles.begin(); it != this->fig_particles.end(); ++it) {
		if ((*it)->particle_id == particle_id) {
			delete* it; // 删除指针指向的对象
			it = this->fig_particles.erase(it); // 从容器中删除指针，更新迭代器
			break; // 一旦找到并删除，退出循环
		}
	}
}

void NPC::ToConversation(int task_id) {
	/*if (this->task_state == task_id) {
		return;
	}
	else {
		this->task_state = task_id;
		this->next_conversation_id = 0;
		AddFigParticle(ANI_EXCLAMATION);
	}*/

	//现在调用应该只会是单次的
	this->task_state = task_id;
	this->next_conversation_id = 0;
	is_finished = false;
	AddFigParticle(ANI_EXCLAMATION);
}

std::vector<NPC*> npcs_main;
std::vector<NPC*> npcs_house_1;
std::vector<NPC*> npcs_meadow;


void InitNPCs()
{

	for (int i = 0; i < npcs_main.size(); i++) {
		delete npcs_main[i];
	}
	npcs_main.clear();

	for (int i = 0; i < npcs_main.size(); i++) {
		delete npcs_house_1[i];
	}
	npcs_house_1.clear();

	for (int i = 0; i < npcs_main.size(); i++) {
		delete npcs_meadow[i];
	}
	npcs_meadow.clear();

	npcs_main.push_back(new NPC(BLOCK_SIZE_X * 10, BLOCK_SIZE_Y * 14, NPC_MAN1_ID));

	npcs_main.push_back(new NPC(BLOCK_SIZE_X * 26, BLOCK_SIZE_Y * 15, NPC_MAN3_ID));

	npcs_house_1.push_back(new NPC(BLOCK_SIZE_X * 10, BLOCK_SIZE_Y * 15, NPC_MAN2_ID));

	npcs_meadow.push_back(new NPC(BLOCK_SIZE_X * 5, BLOCK_SIZE_Y * 15, NPC_MEADOW_MAN_ID));
};

