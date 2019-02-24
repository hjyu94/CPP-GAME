// 이 헤더파일을 딱 한번만 포함시키겠다는 의미이다.
#pragma once

#include <iostream>
using namespace std;


enum OUTPUT_TYPE
{
	OT_NONE,
	OT_OUTPUT,
	OT_INVERSE,
};


// 헤더파일에는 보통 함수 선언부분을 만들어준다.
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
	// pBegin, pEnd는 명시적으로 처음과 끝을 의미한다.
	// 실제 데이터를 저장하는 노드는 아니다.
	// 실제 데이터를 저장하는 노드는 pBegin과 pEnd 사이에 존재하게 만들어준다.
	PNODE	pBegin;
	PNODE	pEnd;
	int		iSize;
} LIST, *PLIST;


// static으로 만들어주지 않으면 List.h 를 여러번 인클루드 하게 된다.
// 함수가 여러곳에서 정의되므로 링킹에러가 발생한다.

// 1) 정의와 선언을 분리하던가
// 2) static 함수로 만들어주자.
static int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear(); // 버퍼 플래그 바꿔주기
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return iInput;
}

static void InputString(char* pString, int iSize)
{
	// 버퍼에 엔터가 남아있을 수 있다.
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize - 1); // 마지막 1바이트는 NULL
}


// ctrl + . : 정의 만들기 -> ESC: 끄기
void InitList(PLIST pList);
// void ClerList(PLIST pList);
void DestroyList(PLIST pList);
void Push_Back(PLIST pList);
void Push_Front(PLIST pList);
void Output(PLIST pList);
void OutputStudent(const PSTUDENT pStudent);
void Search(PLIST pList);
void Delete(PLIST pList);
