#include "47 List.h"

// const 포인터이기 때문에 가리키는 대상의 값을 변경할 수 없다
void OutputStudent(const PSTUDENT pStudent)
{
	cout << "이름: " << pStudent->strName << endl;
	cout << "학번: " << pStudent->iNumber << endl;
	cout << "국어: " << pStudent->iKor << endl;
	cout << "영어: " << pStudent->iEng << endl;
	cout << "수학: " << pStudent->iMath << endl;
	cout << "총점: " << pStudent->iTotal << endl;
	cout << "평균: " << pStudent->fAvg << endl;
	cout << endl;
}

void InitList(PLIST pList)
{
	pList->iSize = 0;

	pList->pBegin = new NODE;
	pList->pEnd = new NODE;

	// 시작노드의 다음 노드는 마지막 노드이다.
	pList->pBegin->pNext = pList->pEnd;

	// 마지막 노드의 이전노드는 시작 노드이다.
	pList->pEnd->pPrev = pList->pBegin;

	// 마지막 노드의 다음 노드는 없으므로 NULL
	pList->pEnd->pNext = NULL;
	
	// 처음 노드의 이전 노드는 없으므로 NULL
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
	cout << "=========학생추가========" << endl;

	STUDENT tStudent;

	cout << "이름: ";
	InputString(tStudent.strName, NAME_SIZE);

	cout << "학번: ";
	tStudent.iNumber = InputInt();

	cout << "국어: ";
	tStudent.iKor = InputInt();
	cout << "영어: ";
	tStudent.iEng = InputInt();
	cout << "수학: ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f; // 정수와 실수 연산은 실수로 리턴함
	
	// 추가할 리스트 노드를 생성한다.
	// 가장 마지막에 추가될 것이기 때문에 다음 노드가 존재하지 않는다.
	
	PNODE	pNode = new NODE;
	pNode->tStudent = tStudent;

	// 새로 추가하는 노드는 
	// End노드의 이전 노드 ~ End 노드 사이에 추가해야 한다.

	// pEnd 노드 이전 노드의 다음으로 추가할 노드를 지정한다.
	pList->pEnd->pPrev->pNext = pNode;
	
	// 추가할 노드의 이전 노드로 End 이전 노드를 지정한다.
	pNode->pPrev = pList->pEnd->pPrev;
	
	// 새로 추가할 노드의 다음 노드를 pEnd에 연결한다
	pNode->pNext = pList->pEnd;
	
	// pEnd노드의 이전 노드로 새로 추가할 노드를 연결한다.
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
		cout << "아직 등록된 학생이 없습니다" << endl;
		return;
	}

	int iOutputMode=0;

	while (true)
	{
		system("cls");
		cout << "=========학생출력========" << endl;

		cout << "1. 정방향 출력" << endl;
		cout << "2. 역방향 출력" << endl;
		cout << "입력: ";
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

	cout << "학생수: " << pList->iSize << endl;
}


void Search(PLIST pList)
{
	system("cls");
	cout << "=========학생검색========" << endl;

	char targetString[NAME_SIZE];
	// bool bExist = false;

	cout << "탐색할 이름을 입력하세요 :";
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

	// while문을 빠져나올때까지 찾지 못했다는 것
	cout << "등록 학생이 없습니다" << endl;
}

void Delete(PLIST pList)
{
	system("cls");
	cout << "=========학생삭제========" << endl;

	cout << "삭제할 이름을 입력하세요: ";
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

			cout << strName << "학생 삭제 완료!!" << endl;
			system("pause");
			return;
		}

		pNode = pNode->pNext;
	}

	cout << "삭제할 학생을 찾을 수 없습니다" << endl;
}
