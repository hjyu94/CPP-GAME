#include <iostream>

using namespace std;

#define NAME_SIZE 32
// #define STUDENT_MAX 10

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

/*
��ũ�帮��Ʈ : �ڷᱸ���� �� �����̴�. �ڷᱸ���� �����͸� �����ϴ� ����� ���Ѵ�.
��ũ�帮��Ʈ�� ������ ����� ������Ѽ� ������ �� �ִ� ������ �����Ѵ�.
��ũ�帮��Ʈ�� �����͸� �����ϱ� ���� ����� ���� �����Ѵ�.
�� ����� Ư¡�� ���� ��带 �� �� �ְ� �ȴ�. (���� ����� �޸� �ּ� ����)
����Ʈ�� ���������� �Ǿ��ִ�. -> �迭ó�� Ư�� ��ҿ� �ٷ� ������ �Ұ���
������ �տ������� ���ʴ�� Ÿ�� ���� �Ѵ�.
��带 ���� �߰��Ҷ��� ��带 �����ϰ� ������ ��忡 ���Ḹ ���ָ� �Ǳ� ������
������ ������ ����. �޸𸮰� ����ϴ� �ѵ� �������� ��� ������ �ִ�.
*/

// ����Ʈ ��带 �����
typedef struct _tagNode
{
	STUDENT		tStudent;
	_tagNode*	pNext;
} NODE, *PNODE;

// ����Ʈ ����ü�� ������ش�
typedef struct _tagList
{
	PNODE	pBegin;
	PNODE	pEnd;
	int		iSize = 0;
} LIST, *PLIST;

int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear(); // ���� �÷��� �ٲ��ֱ�
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return iInput;
}

void InputString(char* pString, int iSize)
{
	// ���ۿ� ���Ͱ� �������� �� �ִ�.
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize - 1); // ������ 1����Ʈ�� NULL
	
}
void InitList(PLIST pList)
{
	// �����ʹ� �������̸� �ʱ�ȭ�Ҷ� null(0) ���� �ʱ�ȭ�صΰ� ���� ���� ����.
	// �ֳ��ϸ� 0�� false 0�� �ƴ� ��� ���� true�̱� �����̴�.
	// �ʱ�ȭ�� ���� ���� ��� ���ִ� ������ ���� true�̴�.
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

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

void Insert(PLIST pList)
{
	system("cls");
	cout << "=========�л��߰�========" << endl;
	
	STUDENT tStudent;
	
	cout << "�̸�: ";
	InputString(tStudent.strName, NAME_SIZE);
	
	cout << "�й�: ";
	tStudent.iNumber = InputInt();
	
	cout << "����: ";
	tStudent.iKor = InputInt();
	cout << "����: ";
	tStudent.iEng = InputInt();
	cout << "����: ";
	tStudent.iMath = InputInt();
	
	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f; // ������ �Ǽ� ������ �Ǽ��� ������

	// �߰��� ����Ʈ ��带 �����Ѵ�.
	// ���� �������� �߰��� ���̱� ������ ���� ��尡 �������� �ʴ´�.
	PNODE	pNode = new NODE;
	pNode->pNext = NULL;
	pNode->tStudent = tStudent;

	if (pList->pBegin == NULL)
	{
		pList->pBegin = pNode;
	}
	else
	{
		pList->pEnd->pNext = pNode;
	}
	
	pList->pEnd = pNode;

	++pList->iSize;
}

void ClearList(PLIST pList)
{
	PNODE	pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE	pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

// const �������̱� ������ ����Ű�� ����� ���� ������ �� ����
void OutputStudent(const PSTUDENT pStudent)
{
	cout << "�̸�: " << pStudent->strName << endl;
	cout << "�й�: " << pStudent->iNumber << endl;
	cout << "����: " << pStudent->iKor << endl;
	cout << "����: " << pStudent->iEng << endl;
	cout << "����: " << pStudent->iMath << endl;
	cout << "����: " << pStudent->iTotal << endl;
	cout << "���: " << pStudent->fAvg << endl;
}

void Output(PLIST pList)
{
	system("cls");
	cout << "=========�л����========" << endl;

	PNODE	pNode = pList->pBegin;

	if (pNode == NULL) 
	{
		cout << "���� ��ϵ� �л��� �����ϴ�" << endl;
	}

	else
	{
		while(pNode != NULL)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
			cout << endl;
		}
		cout << "�л���: " << pList->iSize << endl;
	}

}

void Search(PLIST pList)
{
	/*
		system("cls");
		cout << "=========�л��˻�========" << endl;
	
		char targetString[NAME_SIZE];
		bool bExist = false;

		cout << "Ž���� �̸��� �Է��ϼ��� :";
		InputString(targetString, NAME_SIZE);
	
		PNODE pNode = pList->pBegin;
		STUDENT resStudent;

		while (pNode != NULL)
		{
			if (strcmp(pNode->tStudent.strName, targetString) == 0)
			{
				resStudent = pNode->tStudent;
				bExist = true;
			}
		
			pNode = pNode->pNext;
		}

		if (bExist)
		{
			OutputStudent(&resStudent);
		}
		else
		{
			cout << "��� �л��� �����ϴ�" << endl;
		}
	*/

	system("cls");
	cout << "=========�л��˻�========" << endl;

	char targetString[NAME_SIZE];
	// bool bExist = false;

	cout << "Ž���� �̸��� �Է��ϼ��� :";
	InputString(targetString, NAME_SIZE);

	PNODE pNode = pList->pBegin;
	// STUDENT resStudent;

	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, targetString) == 0)
		{
			OutputStudent(&pNode->tStudent);
			// bExist = true;
			system("pause");
			return;
		}

		pNode = pNode->pNext;
 	}

	// while���� �������ö����� ã�� ���ߴٴ� ��
	cout << "��� �л��� �����ϴ�" << endl;
}

void Delete(PLIST pList)
{
	system("cls");
	cout << "=========�л�����========" << endl;

	/*
		if (pList->iSize == 0)
		{
			cout << "�л���: 0" << endl;
			return;
		}
		else
		{
			cout << "������ �̸��� �Է��ϼ��� : ";
			char targetName[NAME_SIZE];
			InputString(targetName, NAME_SIZE);

			PNODE pNode = pList->pBegin;
			PNODE pPrev;

			while (pNode != NULL)
			{
				if (strcmp(pNode->tStudent.strName, targetName) == 0)
				{
					// ����Ʈ�� ��尡 �ϳ����� ���
					if (pList->iSize == 1)
					{
						pList->pBegin = NULL;
						pList->pEnd = NULL; // �������� �ȵ�!
					}

					// Ÿ�� ��尡 ù��°�� �ִ� ���
					else if (pNode == pList->pBegin)
					{
						pList->pBegin = pNode->pNext;
					}

					// Ÿ�� ��尡 �������� �ִ� ���
					else if (pNode == pList->pEnd)
					{
						pPrev->pNext = NULL;
						pList->pEnd = pNode;
					}

					// Ÿ�ٳ�尡 �߰��� �ִ� ���
					else
					{
						pPrev->pNext = pNode->pNext;
					}
				
					delete pNode;
					--(pList->iSize);
					// cout << pNode->tStudent.strName << "�л� ���� �Ϸ�!!" << endl;
					// cout << targetName << "�л� ���� �Ϸ�!!" << endl;

					return;
				}

				pPrev = pNode;
				pNode = pNode->pNext;
			}

			cout << "�׷� �л��� �������� �ʽ��ϴ�" << endl;
		}
	*/

	cout << "������ �̸��� �Է��ϼ���: ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE	pNode = pList->pBegin;
	PNODE	pPrev = NULL;

	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			// ���� ����� ���� ��带 ���´�
			PNODE	pNext = pNode->pNext;
			
			// ���� ���� ��尡 NULL �̶�� ���� ù��° ��带 ����ٴ� �ǹ��̴�.
			if (pPrev == NULL)
			{
				delete pNode;
				pList->pBegin = pNext;

				// ���� ��嵵 NULL�̶�� ���� ��Ȳ�� ��尡 1������ ��Ȳ
				if (pNext == NULL)
					pList->pEnd = NULL;
			}

			// ���� ��尡 �ִ� ��쿡�� ���� ����� ������ ���� ����� ���� ���� ����
			else
			{
				delete pNode;
				pPrev->pNext = pNext;

				// ���� ���� ��尡 ���� ������ ��忴�ٸ�
				if (pNext == NULL)
					pList->pEnd = pPrev;
			}

			// cout << pNode->tStudent.strName << "�л� �����Ϸ�!!" << endl;
			// pNode �޸� �ݳ��ؼ� �̻��� �� ��µ�
			cout << strName << "�л� �����Ϸ�!!" << endl;

			--(pList->iSize);
			return;
		}
		
		// �ش� ���� �̸��� ��ġ���� ������ ���� ��尡 ���� ��尡 �ȴ�
		pPrev = pNode;
		pNode = pNode->pNext;
	}

	cout << "������ �л��� ã�� �� �����ϴ�" << endl;
	system("pause");
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
	cout << "�޸� �ݳ� �Ϸ�" << endl;
	return 0;
}