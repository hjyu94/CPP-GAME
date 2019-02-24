// �� ��������� �� �ѹ��� ���Խ�Ű�ڴٴ� �ǹ��̴�.
#pragma once

#include <iostream>
using namespace std;


enum OUTPUT_TYPE
{
	OT_NONE,
	OT_OUTPUT,
	OT_INVERSE,
};


// ������Ͽ��� ���� �Լ� ����κ��� ������ش�.
#define NAME_SIZE	32


typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor, iEng, iMath;
	int		iTotal;
	float	fAvg;
} STUDENT, *PSTUDENT;


typedef struct _tagNode
{
	STUDENT		tStudent;
	_tagNode*	pNext;
	_tagNode*	pPrev;
} NODE, *PNODE;


typedef struct _tagList
{
	// pBegin, pEnd�� ��������� ó���� ���� �ǹ��Ѵ�.
	// ���� �����͸� �����ϴ� ���� �ƴϴ�.
	// ���� �����͸� �����ϴ� ���� pBegin�� pEnd ���̿� �����ϰ� ������ش�.
	PNODE	pBegin;
	PNODE	pEnd;
	int		iSize;
} LIST, *PLIST;


// static���� ��������� ������ List.h �� ������ ��Ŭ��� �ϰ� �ȴ�.
// �Լ��� ���������� ���ǵǹǷ� ��ŷ������ �߻��Ѵ�.

// 1) ���ǿ� ������ �и��ϴ���
// 2) static �Լ��� ���������.
static int InputInt()
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

static void InputString(char* pString, int iSize)
{
	// ���ۿ� ���Ͱ� �������� �� �ִ�.
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize - 1); // ������ 1����Ʈ�� NULL
}


// ctrl + . : ���� ����� -> ESC: ����
void InitList(PLIST pList);
// void ClerList(PLIST pList);
void DestroyList(PLIST pList);
void Push_Back(PLIST pList);
void Push_Front(PLIST pList);
void Output(PLIST pList);
void OutputStudent(const PSTUDENT pStudent);
void Search(PLIST pList);
void Delete(PLIST pList);
