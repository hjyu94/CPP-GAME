#include <iostream>

using namespace std;

#define NAME_SIZE	32
#define STUDENT_MAX 10

struct _tagStudent
{
	char strName[NAME_SIZE];
	int iNumber, iKor, iEng, iMath;
	int iTotal;
	float fAvg;
};

enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT,
};

int main()
{
	_tagStudent tStudentArr[STUDENT_MAX] = {};

	while (true)
	{
		system("cls"); // clear console

					   // �޴��� ����Ѵ�
		cout << "1. ���" << endl;
		cout << "2. ����" << endl;
		cout << "3. �˻�" << endl;
		cout << "4. ���" << endl;
		cout << "5. ������" << endl;
		cout << "�޴��� �����ϼ���: ";

		int iMenu;
		cin >> iMenu;

		if (iMenu == MENU_EXIT) break;
		// switch �� �ȿ��� break�� while�� ���������� ���ؼ� ���� ���

		switch (iMenu)
		{
		case MENU_INSERT:
			break;

		case MENU_DELETE:
			break;

		case MENU_SEARCH:
			break;

		case MENU_OUTPUT:
			break;

		}

		system("pause");
	}

	return 0;
}