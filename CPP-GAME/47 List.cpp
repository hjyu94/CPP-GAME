#include "47 List.h"

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
	cout << endl;
}

void InitList(PLIST pList)
{
	pList->iSize = 0;

	pList->pBegin = new NODE;
	pList->pEnd = new NODE;

	// ���۳���� ���� ���� ������ ����̴�.
	pList->pBegin->pNext = pList->pEnd;

	// ������ ����� �������� ���� ����̴�.
	pList->pEnd->pPrev = pList->pBegin;

	// ������ ����� ���� ���� �����Ƿ� NULL
	pList->pEnd->pNext = NULL;
	
	// ó�� ����� ���� ���� �����Ƿ� NULL
	pList->pBegin->pPrev = NULL;
}


void DestroyList(PLIST pList)
{
	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE pNext;
		pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}
	
	pList->iSize = 0;
	pList->pBegin = NULL;
	pList->pEnd = NULL;
}

void Push_Back(PLIST pList)
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
	pNode->tStudent = tStudent;

	// ���� �߰��ϴ� ���� 
	// End����� ���� ��� ~ End ��� ���̿� �߰��ؾ� �Ѵ�.

	// pEnd ��� ���� ����� �������� �߰��� ��带 �����Ѵ�.
	pList->pEnd->pPrev->pNext = pNode;
	
	// �߰��� ����� ���� ���� End ���� ��带 �����Ѵ�.
	pNode->pPrev = pList->pEnd->pPrev;
	
	// ���� �߰��� ����� ���� ��带 pEnd�� �����Ѵ�
	pNode->pNext = pList->pEnd;
	
	// pEnd����� ���� ���� ���� �߰��� ��带 �����Ѵ�.
	pList->pEnd->pPrev = pNode;

	++pList->iSize;
}

void Push_Front()
{
}

void Output(PLIST pList)
{
	if (pList->iSize == 0)
	{
		cout << "���� ��ϵ� �л��� �����ϴ�" << endl;
		return;
	}

	int iOutputMode=0;

	while (true)
	{
		system("cls");
		cout << "=========�л����========" << endl;

		cout << "1. ������ ���" << endl;
		cout << "2. ������ ���" << endl;
		cout << "�Է�: ";
		iOutputMode = InputInt();

		if (iOutputMode > OT_NONE && iOutputMode <= OT_INVERSE) break;

		system("pause");
	}

	system("cls");

	PNODE pNode;

	switch (iOutputMode)
	{
	case OT_OUTPUT:
		pNode = pList->pBegin->pNext;
		
		//while (pNode->pNext != NULL)
		while (pNode != pList->pEnd)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
		}
		break;

	case OT_INVERSE:
		pNode = pList->pEnd->pPrev;
		
		//while (pNode->pPrev != NULL)
		while (pNode != pList->pBegin)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pPrev;
		}
		break;
	}

	cout << "�л���: " << pList->iSize << endl;
}


void Search(PLIST pList)
{
	system("cls");
	cout << "=========�л��˻�========" << endl;

	char targetString[NAME_SIZE];
	// bool bExist = false;

	cout << "Ž���� �̸��� �Է��ϼ��� :";
	InputString(targetString, NAME_SIZE);

	PNODE pNode = pList->pBegin->pNext;

	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, targetString) == 0)
		{
			OutputStudent(&pNode->tStudent);
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

	cout << "������ �̸��� �Է��ϼ���: ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE	pNode = pList->pBegin->pNext;

	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;
			
			delete pNode;
			--pList->iSize;

			cout << strName << "�л� ���� �Ϸ�!!" << endl;
			system("pause");
			return;
		}

		pNode = pNode->pNext;
	}

	cout << "������ �л��� ã�� �� �����ϴ�" << endl;
}
