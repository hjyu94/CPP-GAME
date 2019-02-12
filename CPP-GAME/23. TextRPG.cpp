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
	int iExp; // �÷��̾�� �������� �ִ� ����ġ
	int iGoldMin, iGoldMax; // �÷��̾�� �������� �ִ� ��

};

void main()
{
	srand((unsigned int)time(0));

	// �÷��̾� ���� �Է�
	_tagPlayer tPlayer = {};

	cout << "�÷��̾��� �̸�: ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1); // null �ڸ� ������ -1

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		cout << "1.��� / 2.�ü� / 3.������" << endl;
		cout << "������ �����ϼ���: ";

		cin >> iJob;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\0');
			continue; // while �� ó������
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
		strcpy_s(tPlayer.strJobName, "���");
		// ���� ����
		// ...
		break;

	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "�ü�");
		// ���� ����
		// ...
		break;

	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "������");
		// ���� ����
		// ...
		break;

	}

	// ���� ����
	_tagMonster tMonsterArr[MT_BACK - 1];
	
	// ���, Ʈ��, �巡��
	strcpy_s(tMonsterArr[0].strName, "���");
	strcpy_s(tMonsterArr[1].strName, "Ʈ��");
	strcpy_s(tMonsterArr[2].strName, "�巡��");

	/*
		int min = 5, max = 15;
		int iAttack = rand() % (max - min + 1) + min;
		int iDamage = iAttack - iArmor;
		iDamage = iDamage < 1 ? 1 : iDamage;
	*/

	while (true) 
	{
		system("cls");

		cout << "1. ��" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� �����ϼ���" << endl;

		int iMenu;
		cin >> iMenu;

		// ���ڰ� �ƴ϶� ���ڸ� �Է��� ���
		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT)
		{
			cout << "�����մϴ�" << endl;
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