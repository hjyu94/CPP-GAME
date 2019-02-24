#include "47 List.h"
#include <iostream>
using namespace std;

enum GAME_MODE
{
	GM_NONE,
	GM_NEW,
	GM_LOAD,
	GM_EXIT,
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END, 
};

enum ITEM_TYPE
{
	EQ_MIN,
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX,
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK,
};

#define ITEM_DESC_LENGTH	512
#define INVENTORY_MAX		20
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3
#define LEVEL_MAX			10

typedef struct _tagPlayer
{
	char		strName[NAME_SIZE];
	JOB			eJob;
	int			iAttackMin, iAttackMax;
	int			iArmorMin, iArmorMax;
	int			iHP, iHPMax;
	int			iMP, iMPMax;
	int			iExp, iLevel;
	_tagItem	tEquip[EQ_MAX];
	bool		bEquip[EQ_MAX];
	_tagItem	tInventory;
} PLAYER, *PPLAYER;

struct _tagItem
{
	char	strName[NAME_SIZE];
	char	strTypeName[NAME_SIZE];
	ITEM_TYPE eType;
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

// return:true - 불러오기 성공
// return:false - 불러오기 실패
bool LoadPlayer(PPLAYER pPlayer)
{
	FILE*	pFile = NULL;
	fopen_s(&pFile, "Player.ply", "rb");
	
	if (pFile)
	{
		fread(pPlayer->strName, 1, NAME_SIZE, pFile);
		fread(&pPlayer->eJob, sizeof(JOB), 1, pFile);
		fread(&pPlayer->iAttackMin, sizeof(int), 1, pFile);
		fread(&pPlayer->iAttackMax, sizeof(int), 1, pFile);
		fread(&pPlayer->iArmorMin, sizeof(int), 1, pFile);
		fread(&pPlayer->iArmorMax, sizeof(int), 1, pFile);
		fread(&pPlayer->iHP, sizeof(int), 1, pFile);
		fread(&pPlayer->iHPMax, sizeof(int), 1, pFile);
		fread(&pPlayer->iMP, sizeof(int), 1, pFile);
		fread(&pPlayer->iMPMax, sizeof(int), 1, pFile);
		fread(&pPlayer->iExp, sizeof(int), 1, pFile);
		fread(&pPlayer->iLevel, sizeof(int), 1, pFile);

		// 무기 착용 여부
		fread(&pPlayer->bEquip[EQ_WEAPON], 1, 1, pFile);
		if (pPlayer->bEquip[EQ_WEAPON])
			fread(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagItem), 1, pFile);
		
		// 방어구 아이템
		fread(&pPlayer->bEquip[EQ_ARMOR], 1, 1, pFile);
		if (pPlayer->bEquip[EQ_ARMOR])
			fread(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagItem), 1, pFile);

		fclose(pFile);
		return true;
	}
	
	else
		return false;
}

bool SavePlayer(PPLAYER pPlayer)
{
	FILE*	pFile;
	fopen_s(&pFile, "Player.ply", "wb");

	if (pFile)
	{
		fwrite(pPlayer->strName, 1, NAME_SIZE, pFile);
		fwrite(&pPlayer->eJob, sizeof(JOB), 1, pFile);
		fwrite(&pPlayer->iAttackMin, sizeof(int), 1, pFile);
		fwrite(&pPlayer->iAttackMax, sizeof(int), 1, pFile);
		fwrite(&pPlayer->iArmorMin, sizeof(int), 1, pFile);
		fwrite(&pPlayer->iArmorMax, sizeof(int), 1, pFile);
		fwrite(&pPlayer->iHP, sizeof(int), 1, pFile);
		fwrite(&pPlayer->iHPMax, sizeof(int), 1, pFile);
		fwrite(&pPlayer->iMP, sizeof(int), 1, pFile);
		fwrite(&pPlayer->iMPMax, sizeof(int), 1, pFile);
		fwrite(&pPlayer->iExp, sizeof(int), 1, pFile);
		fwrite(&pPlayer->iLevel, sizeof(int), 1, pFile);

		// 무기 착용 여부
		fwrite(&pPlayer->bEquip[EQ_WEAPON], 1, 1, pFile);
		if (pPlayer->bEquip[EQ_WEAPON])
			fwrite(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagItem), 1, pFile);

		// 방어구 아이템
		fwrite(&pPlayer->bEquip[EQ_ARMOR], 1, 1, pFile);
		if (pPlayer->bEquip[EQ_ARMOR])
			fwrite(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagItem), 1, pFile);

		fclose(pFile);
		return true;
	}

	else
		return false;
}

void main()
{
	int iGameMode = 0;
	while (iGameMode <= GM_NONE || iGameMode > GM_EXIT)
	{
		system("cls");
		cout << "1. 새로하기" << endl << "2. 이어하기" 
			<< endl << "3. 종료" << endl;
		iGameMode = InputInt();
	}
	
	if (iGameMode == 3) return;
	
	PLAYER tPlayer = {};

	switch (iGameMode)
	{
	case 1:
		if (!SavePlayer(&tPlayer))
		{
			cout << "플레이어 파일 오류!!" << endl;
		}
		break;

	case 2:
		if (!LoadPlayer(&tPlayer))
		{
			cout << "플레이어 파일 오류!!" << endl;
		}
		break;
	}
}