#pragma once

#define WINDOW_TITLEBARHEIGHT	32			//�������߶�
#define WINDOW_WIDTH			896+16		//��Ϸ���ڿ��
#define WINDOW_HEIGHT			640+32		//��Ϸ���ڸ߶�

#define STAGE_STARTMENU			0		//��ʼ�����ID
#define STAGE_MAIN				1		//��һ����Ϸ������ID
#define STAGE_HOUSE_1			2
#define STAGE_MEADOW			3
#define STAGE_HOUSE_2			5
#define STAGE_END				6


//�ߴ�
#define HELP_WIDTH				800 
#define HELP_HEIGHT				600
#define BG_BITMAP_WIDTH			240		//����ͼƬ��λͼ���
#define BG_BITMAP_HEIGHT		160		//����ͼƬ��λͼ�߶�
#define BG_COLUMNS				28		//��������
#define BG_ROWS					20		//��������
#define HUMAN_SIZE_X			38		//��������Ļ�ϵĿ��
#define HUMAN_SIZE_Y			52		
#define HUMAN_BITMAP_SIZE_X		19		//������λͼ�ϵĿ��
#define HUMAN_BITMAP_SIZE_Y		26		
#define BLOCK_SIZE_X			32		//������������Ļ�ϵĿ��
#define BLOCK_SIZE_Y			32		//������������Ļ�ϵĸ߶�
#define BLOCK_BITMAP_SIZE_X		16		//��ͼ����λͼ�ϵĿ��
#define BLOCK_BITMAP_SIZE_Y		16
#define DIALOG_SIZE_X			896		//�Ի��򱳾�
#define DIALOG_SIZE_Y			120
#define DIALOG_BITMAP_SIZE_X	250
#define DIALOG_BITMAP_SIZE_Y	44
#define MOSTER_SIZE_X			28		//����
#define MOSTER_SIZE_Y			30
#define MOSTER_BITMAP_SIZE_X	14
#define MOSTER_BITMAP_SIZE_Y	15
#define NEW_MOSTER_BITMAP_SIZE_X	64
#define NEW_MOSTER_BITMAP_SIZE_Y	64
#define NEW_MOSTER_SIZE_X			30		//����
#define NEW_MOSTER_SIZE_Y			30
#define HP_WIDTH					30
#define HP_HEIGHT					5


//��λ״̬����
#define UNIT_STATE_HOLD			0		//��ֹ
#define UNIT_STATE_WALK			1		//����
#define UNIT_STATE_ATTACK		2		//����

//��λ������
#define UNIT_DIRECT_RIGHT		1		//����
#define UNIT_DIRECT_LEFT		3		//����
#define UNIT_DIRECT_UP			2		//����
#define UNIT_DIRECT_DOWN		0		//����

//��������
#define BUTTON_WIDTH		212		//��ʼ��Ϸ��ť���
#define BUTTON_HEIGHT		76		//��ʼ��Ϸ��ť�߶�

#define BUTTON_STARTGAME			1001	//��ʼ��Ϸ��ťID
#define BUTTON_HELP			1002	//��ʼ��Ϸ��ťID
#define BUTTON_STOP_CONTINUE 1003
#define BUTTON_STOP_HELP	1004
#define BUTTON_STOP_HOME	1005
#define BUTTON_FAILED_RESTART 1006
#define BUTTON_BED_END 1007
#define BUTTON_BED_CONTINUE 1008
#define BUTTON_END_BACK 1009
#define BUTTON_GLOBAL_ACHIEVEMENT 1010

#define TIMER_GAMETIMER				1		//��Ϸ��Ĭ�ϼ�ʱ��ID
#define TIMER_GAMETIMER_ELAPSE		30		//Ĭ�ϼ�ʱ��ˢ�¼���ĺ�����
#define UNIT_SPEED					3.0		//��λ�����ٶ�

#define NPC_MAN1_ID				2001		//ÿ��NPC��ID��
#define NPC_WOMAN1_ID			2002
#define NPC_MAN2_ID				2003
#define NPC_MEADOW_MAN_ID			2004
#define NPC_MAN3_ID				2005

#define MONSTER_CAT_ID			3001
#define MONSTER_CROW_ID			3002
#define MONSTER_DUCK_ID			3003
#define MONSTER_CHIKEN_ID			3004


#define WEAPON_SWORD_ID			4001


#define LAND_GRASS_ID				5001	
#define LAND_DIRT_ID			5002

#define EFFECT_SPEED_UP_ID		6001

#define MONSTER_STATE_MOVE		10001
#define MONSTER_STATE_STOP		10002
#define MONSTER_STATE_HOME		10003

#define OBJ_TREE 20001
#define OBJ_HOUSE_1 20002
#define OBJ_HOUSE_2 20003
#define OBJ_HOUSE_3 20004
#define OBJ_BAR_H_LEFT 20005
#define OBJ_BAR_H_MID 20006
#define OBJ_BAR_H_RIGHT 20007
#define OBJ_BAR_V_HEAD 20008
#define OBJ_BAR_V_TAIL 20009
#define OBJ_WALL_1 20010
#define OBJ_TABLE_1 20011
#define OBJ_CHAIR_1 20012
#define OBJ_SOFA_1 20013
#define OBJ_TV 20014
#define OBJ_CARPET_1 20015
#define OBJ_GRASS 20016
#define OBJ_CHERRY 20018
#define OBJ_TENT 20019
#define OBJ_GRASS_BLOCK 20020
#define OBJ_BED 20021


#define MAP_MAIN 30001

#define BG_BLACK 40000
#define BG_GRASS 40001
#define BG_SAND 40002
#define BG_FLOOR_1 40003
#define BG_BARRIER_LEFT 40004
#define BG_BARRIER_RIGHT 40005
#define BG_BARRIER_TOP 40006
#define BG_BARRIER_BOTTOM 40007
#define BG_BARRIER_LEFT_TOP 40008
#define BG_BARRIER_LEFT_BOTTOM 40009
#define BG_BARRIER_RIGHT_TOP 40010	
#define BG_BARRIER_RIGHT_BOTTOM 40011
#define BG_BARRIER_LEFT_TOP_R 40012
#define BG_BARRIER_LEFT_BOTTOM_R 40013
#define BG_BARRIER_RIGHT_TOP_R 40014
#define BG_BARRIER_RIGHT_BOTTOM_R 40015
#define BG_ROCK_1 40016
#define BG_ROCK_2 40017
#define BG_ROCK_3 40018
#define BG_ROCK_4 40019

#define ITEM_CERTIFICATE 60001
#define ITEM_SWORD 60002
#define ITEM_BOW 60003
#define ITEM_KEY 60004

#define ANI_DEATH 70001
#define ANI_EXCLAMATION 70002

#define ACHIEVE_CROW_HUNTER 80001
#define ACHIEVE_QUICK_SLEEP 80002
#define ACHIEVE_FRIENDLY 80003
#define ACHIEVE_HELPFUL 80004
