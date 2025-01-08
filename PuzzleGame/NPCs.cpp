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
	//���ݲ�ͬNPC��ʼ����ͬ��ͼ��ͶԻ�
	switch (npc_id)
	{
	case NPC_MAN1_ID: {
		this->img = npc_hitmap[NPC_MAN1_ID];

		this->size_x = 19;
		this->size_y = 26;

		std::vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"���������Ĵ峤��");
		conversations_1.push_back(L"��ȥ̽��һ����ɫ��������˰�");
		this->conversations.push_back(conversations_1);

		break;
	}
	case NPC_MAN2_ID: {
		this->img = npc_hitmap[NPC_MAN2_ID];

		this->size_x = 19;
		this->size_y = 26;

		std::vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"���԰��ҰѼ��ϻص���̺����");
		this->conversations.push_back(conversations_1);

		std::vector<const wchar_t*> conversations_2;
		conversations_2.push_back(L"лл�㣡�������ں����");
		conversations_2.push_back(L"������Ĺ���֤����ȥ��");
		this->conversations.push_back(conversations_2);

		std::vector<const wchar_t*> conversations_3;
		conversations_3.push_back(L"���ְ����Ǹ��������");
		this->conversations.push_back(conversations_3);

		std::vector<const wchar_t*> conversations_4;
		conversations_4.push_back(L"���ǻ����ڵ�̺�ϱȽϺ�");
		this->conversations.push_back(conversations_4);

		break;
	}
	case NPC_MAN3_ID: {
		this->img = npc_hitmap[NPC_MAN3_ID];

		this->size_x = 19;
		this->size_y = 26;

		std::vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"����˭��");
		conversations_1.push_back(L"�Ҳ���ʶ�㣬�㲻���Թ�ȥ��");
		this->conversations.push_back(conversations_1);

		std::vector<const wchar_t*> conversations_2;
		conversations_2.push_back(L"ԭ�����������Ĵ峤");
		conversations_2.push_back(L"��������������ǳ��˵�����");
		conversations_2.push_back(L"��ȥ������");
		this->conversations.push_back(conversations_2);

		std::vector<const wchar_t*> conversations_3;
		conversations_3.push_back(L"лл�㣡������");
		this->conversations.push_back(conversations_3);

		break;
	}
	case NPC_MEADOW_MAN_ID: {
		this->img = npc_hitmap[NPC_MEADOW_MAN_ID];

		this->size_x = 19;
		this->size_y = 26;

		std::vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"��������Ұɣ�ѼȦ���������ѻ");
		conversations_1.push_back(L"���Ұ���ѻ�ϳ���");
		conversations_1.push_back(L"�������������");
		conversations_1.push_back(L"���Ұ���ѻ�ϳ����ٰ�Ѽ�Ӹϻ�ȥ��");
		this->conversations.push_back(conversations_1);


		std::vector<const wchar_t*> conversations_2;
		conversations_2.push_back(L"лл�����ѻ����");
		this->conversations.push_back(conversations_2);

		break;
	}
	default:

		break;
	}
}

void NPC::AddFigParticle(int particle_id) {
	//���û��item certificate�����
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
			delete* it; // ɾ��ָ��ָ��Ķ���
			it = this->fig_particles.erase(it); // ��������ɾ��ָ�룬���µ�����
			break; // һ���ҵ���ɾ�����˳�ѭ��
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

	//���ڵ���Ӧ��ֻ���ǵ��ε�
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

