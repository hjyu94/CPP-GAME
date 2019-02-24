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
	cout << "1. �л��߰�" << endl;
	cout << "2. �л�����" << endl;
	cout << "3. �л�Ž��" << endl;
	cout << "4. �л����" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ���: ";
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

		if (iMenu == MM_EXIT) break; // ���α׷� ����

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
	cout << "�����Ҵ� �޸� �ݳ� �Ϸ�" << endl;
}