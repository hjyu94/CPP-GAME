#include "47 List.h"

enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT,
};

int OutputMenu()
{
	system("cls");
	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생탐색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요: ";
	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT)
	{
		return MM_NONE;
	}

	else return iInput;
}

//void ClearList(PLIST pList)
//{
//	PNODE	pNode = pList->pBegin;
//
//	while (pNode != NULL)
//	{
//		PNODE	pNext = pNode->pNext;
//		delete pNode;
//		pNode = pNext;
//	}
//
//	pList->pBegin = NULL;
//	pList->pEnd = NULL;
//	pList->iSize = 0;
//}

void main()
{
	LIST	tList;

	InitList(&tList);

	while (true)
	{
		int iMenu = OutputMenu();

		if (iMenu == MM_EXIT) break; // 프로그램 종료

		switch (iMenu)
		{
		case MM_INSERT:
			Push_Back(&tList);
			break;

		case MM_DELETE:
			Delete(&tList);
			break;

		case MM_SEARCH:
			Search(&tList);
			break;

		case MM_OUTPUT:
			Output(&tList);
			break;
		}

		system("pause");
	}

	DestroyList(&tList);
	cout << "동적할당 메모리 반납 완료" << endl;
}