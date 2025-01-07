#include "PuzzleGame.h"
#include "NPCs.h"
#include "Maps.h"


NPC* CreateNPC(int x, int y, int npc_id)
{
	NPC* npc = new NPC();
	npc->npcID = npc_id;
	npc->visible = true;
	npc->task_state = 0;
	npc->x = x;
	npc->y = y;
	npc->direction = UNIT_DIRECT_DOWN;
	npc->vx = 0;
	npc->vy = 0;
	npc->state = UNIT_STATE_HOLD;
	npc->frame_row = npc->direction;
	npc->frame_column = 0;
	npc->frame_sequence = NPC_FRAMES_HOLD;
	npc->frame_count = NPC_FRAMES_HOLD_COUNT;
	npc->frame_id = 0;
	npc->next_conversation_id = 0;
	//���ݲ�ͬNPC��ʼ����ͬ��ͼ��ͶԻ�
	switch (npc_id)
	{
	case NPC_MAN1_ID: {
		npc->img = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_NPC_MAN1));

		npc->size_x = 19;
		npc->size_y = 26;

		vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"���������Ĵ峤��");
		conversations_1.push_back(L"��ȥ̽��һ����ɫ��������˰�");
		npc->conversations.push_back(conversations_1);

		break;
	}
	case NPC_MAN2_ID: {
		npc->img = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_NPC_MAN1));

		npc->size_x = 19;
		npc->size_y = 26;

		vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"���԰��ҰѼ��ϻص���̺����");
		npc->conversations.push_back(conversations_1);

		vector<const wchar_t*> conversations_2;
		conversations_2.push_back(L"лл�㣡");
		npc->conversations.push_back(conversations_2);

		vector<const wchar_t*> conversations_3;
		conversations_3.push_back(L"���ְ����Ǹ��������");
		npc->conversations.push_back(conversations_3);

		break;
	}
	case NPC_WEADOW_MAN_ID: {
		npc->img = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_NPC_MAN1));

		npc->size_x = 19;
		npc->size_y = 26;

		vector<const wchar_t*> conversations_1;
		conversations_1.push_back(L"����˭��");
		conversations_1.push_back(L"�Ҳ���ʶ�㣬�㲻���Թ�ȥ��");
		npc->conversations.push_back(conversations_1);

		vector<const wchar_t*> conversations_2;
		conversations_2.push_back(L"ԭ�����������Ĵ峤");
		conversations_2.push_back(L"��������������ǳ��˵�����");
		npc->conversations.push_back(conversations_2);

		vector<const wchar_t*> conversations_3;
		conversations_3.push_back(L"лл�����ѻ����");
		npc->conversations.push_back(conversations_3);

		break;
	}
	default:

		break;
	}

	return npc;
}

std::vector<NPC*> npcs_main;
std::vector<NPC*> npcs_house_1;
std::vector<NPC*> npcs_meadow;


void InitNPCs()
{
	npcs_main.push_back(CreateNPC(BLOCK_SIZE_X * 10, BLOCK_SIZE_Y * 15, NPC_MAN1_ID));

	npcs_house_1.push_back(CreateNPC(BLOCK_SIZE_X * 10, BLOCK_SIZE_Y * 15, NPC_MAN2_ID));

	npcs_main.push_back(CreateNPC(BLOCK_SIZE_X * 26, BLOCK_SIZE_Y * 16, NPC_WEADOW_MAN_ID));
};

