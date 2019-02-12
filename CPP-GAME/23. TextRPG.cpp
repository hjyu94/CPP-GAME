#include <iostream>
#include <time.h> // rand

using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT,
};

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK,
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	
	//...

	JOB_END,
};

#define NAME_SIZE	32

struct _tagPlayer
{
	char strName[NAME_SIZE];
	char strJobName[NAME_SIZE];
	JOB eJob;
	int iAttackMin, iAttackMax;
	int iArmorMin, iArmorMax;
	int iHP, iHPMax;
	int iMP, iMPMax;
	int iExp, iLevel;
};

struct _tagMonster
{
	char strName[NAME_SIZE];
	int iAttackMin, iAttackMax;
	int iArmorMin, iArmorMax;
	int iHP, iHPMax;
	int iMP, iMPMax;
	int iLevel;
	int iExp; // 플레이어에게 보상으로 주는 경험치
	int iGoldMin, iGoldMax; // 플레이어에게 보상으로 주는 돈

};

void main()
{
	srand((unsigned int)time(0));

	// 플레이어 정보 입력
	_tagPlayer tPlayer = {};

	cout << "플레이어의 이름: ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1); // null 자리 때문에 -1

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		cout << "1.기사 / 2.궁수 / 3.마법사" << endl;
		cout << "직업을 선택하세요: ";

		cin >> iJob;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\0');
			continue; // while 문 처음으로
		}
		else if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}
	
	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;

	switch (tPlayer.eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "기사");
		// 스탯 설정
		// ...
		break;

	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "궁수");
		// 스탯 설정
		// ...
		break;

	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "마법사");
		// 스탯 설정
		// ...
		break;

	}

	// 몬스터 생성
	_tagMonster tMonsterArr[MT_BACK - 1];
	
	// 고블린, 트롤, 드래곤
	strcpy_s(tMonsterArr[0].strName, "고블린");
	strcpy_s(tMonsterArr[1].strName, "트롤");
	strcpy_s(tMonsterArr[2].strName, "드래곤");

	/*
		int min = 5, max = 15;
		int iAttack = rand() % (max - min + 1) + min;
		int iDamage = iAttack - iArmor;
		iDamage = iDamage < 1 ? 1 : iDamage;
	*/

	while (true) 
	{
		system("cls");

		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요" << endl;

		int iMenu;
		cin >> iMenu;

		// 숫자가 아니라 문자를 입력한 경우
		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT)
		{
			cout << "종료합니다" << endl;
			break;
		}

		switch (iMenu)
		{
		case MM_MAP:
			break;

		case MM_STORE:
			break;

		case MM_INVENTORY:
			break;

		}
	}
	
}