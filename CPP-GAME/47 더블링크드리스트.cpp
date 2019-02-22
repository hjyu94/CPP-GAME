#include <iostream>

using namespace std;

#define NAME_SIZE 32

enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT,
};

typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
} STUDENT, *PSTUDENT;

typedef struct _tagNode
{
	STUDENT tStudent;
	_tagNode* pPrev;
	_tagNode* pNext;
} NODE, *PNODE;

typedef struct _tagList
{
	PNODE pBegin;
	PNODE pEnd;
} LIST, *PLIST;

void InitList(PLIST pList)
{
	pList->pBegin = NULL;
	pList->pEnd = NULL;
}

void ClearList(PLIST pList)
{
	//pList->pBegin = NULL;
	//pList->pEnd = NULL;
	//delete[] pList;
	//pList = NULL;

	PNODE pNode = pList->pBegin;
	
	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}
	
	pList->pBegin = NULL;
	pList->pEnd = NULL;	
}

int InputInt()
{
	int iInput;
	cin >> iInput;
	
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}
	
	return iInput;
}

void InputString(char* str, int str_size)
{
	cin.ignore(1024, '\n');
	cin.getline(str, str_size - 1);
}

int OutputMenu()
{
	system("cls");
	int iInput;
	cout << "1. ��� / 2. ���� / 3. �˻� / 4. ��� / 5. ����" << endl;
	iInput = InputInt();
	
	if (iInput <= MM_NONE || iInput > MM_EXIT)
	{
		return MM_NONE;
	}
	else return iInput;
}


void Insert(PLIST pList)
{
	system("cls");
	cout << " ==== �л� �߰� ==== " << endl;
	STUDENT tStudent = {};
	cout << "�̸�: ";
	InputString(tStudent.strName, NAME_SIZE);
	cout << "�й�: ";
	tStudent.iNumber = InputInt();
	cout << "��������: ";
	tStudent.iKor = InputInt();
	cout << "��������: ";
	tStudent.iMath = InputInt();
	cout << "��������: ";
	tStudent.iEng = InputInt();
	tStudent.iTotal = tStudent.iEng + tStudent.iKor + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;
	
	PNODE pNode = new NODE;
	pNode->tStudent = tStudent;
	pNode->pNext = NULL;

	// ���� ����Ʈ�� �ƹ��� ��嵵 ���� ��Ȳ�̶��
	if (pList->pBegin == NULL)
	{
		pList->pBegin = pNode;
		pNode->pPrev = NULL;
	}
	else
	{
		pList->pEnd->pNext = pNode;
		pNode->pPrev = pList->pEnd;
	}

	pList->pEnd = pNode;

}

void Delete(PLIST pList)
{
	system("cls");
	cout << "===== �л� ���� =====" << endl;

	PNODE pNode = pList->pBegin; 
	
	if (pNode == NULL)
	{
		cout << "��ϵ� �л��� �ƹ��� �����ϴ�" << endl;
	}
	else
	{
		cout << "�л� �̸�: " << endl;
		char targetName[NAME_SIZE];
		InputString(targetName, NAME_SIZE);

		while (pNode != NULL)
		{
			if (strcmp(pNode->tStudent.strName, targetName) == 0)
			{
				// ã�� ��Ȳ
				
				// ó������ ������, �� �Ѱ��� �ִ� ���
				if (pList->pBegin == pNode && pList->pEnd == pNode)
				{
					pList->pBegin = NULL;
					pList->pEnd = NULL;
				}

				// ù��° ������
				else if (pList->pBegin == pNode)
				{
					pList->pBegin = pNode->pNext;
					pNode->pNext->pPrev = NULL;
				}

				// �������� ������
				else if (pList->pEnd == pNode)
				{
					pList->pEnd = pNode->pPrev;
					pNode->pPrev->pNext = NULL;
				}

				// ��� ������
				else
				{
					pNode->pPrev->pNext = pNode->pNext;
					pNode->pNext->pPrev = pNode->pPrev;
				}

				delete pNode;
				cout << targetName << " �л� ���� �Ϸ�!!" << endl;
				return;
			}
			pNode = pNode->pNext;
		}

		cout << "�׷� �л��� �����ϴ�" << endl;
	}

}

void OutputStudent(const PSTUDENT pStudent)
{
	cout << "�й�: " << pStudent->iNumber << endl;
	cout << "�̸�: " << pStudent->strName << endl;
	cout << "���: " << pStudent->fAvg << endl;
	cout << endl;
}

void Search(PLIST pList)
{
	system("cls");
	cout << "===== �л� �˻� =====" << endl;
	
	PNODE pNode = pList->pBegin;

	if (pNode == NULL)
	{
		cout << "��ϵ� �л��� �ƹ��� �����ϴ�" << endl;
	}
	else
	{
		cout << "�л� �̸�: ";
		char strName[NAME_SIZE];
		InputString(strName, NAME_SIZE);

		while (pNode != NULL)
		{
			if (strcmp(pNode->tStudent.strName, strName) == 0)
			{
				OutputStudent(&pNode->tStudent);
				return;
			}

			pNode = pNode->pNext;
		}
		
		cout << "�׷� �л��� �����ϴ�" << endl;
	}
}


void Output(PLIST pList)
{
	system("cls");
	cout << "===== �л� ��� =====" << endl;
	if (pList->pBegin == NULL)
	{
		cout << "�л��� �ƹ��� �����ϴ�" << endl;
	}
	else
	{
		PNODE pNode = pList->pBegin;
		while (pNode != NULL)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
		}
		cout << "�л� ��� �Ϸ�!!" << endl;
	}
}

int main()
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
			Insert(&tList);
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

	ClearList(&tList); // �����Ҵ��� �޸𸮴� �ݵ�� �ݳ������ �Ѵ�.
	cout << "�����Ҵ� �޸� �ݳ� �Ϸ�" << endl;
	return 0;
}