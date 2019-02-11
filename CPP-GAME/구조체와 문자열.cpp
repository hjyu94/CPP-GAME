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

					   // 메뉴를 출력한다
		cout << "1. 등록" << endl;
		cout << "2. 삭제" << endl;
		cout << "3. 검색" << endl;
		cout << "4. 출력" << endl;
		cout << "5. 나가기" << endl;
		cout << "메뉴를 선택하세요: ";

		int iMenu;
		cin >> iMenu;

		if (iMenu == MENU_EXIT) break;
		// switch 문 안에서 break는 while을 빠져나가지 못해서 따로 밴다

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