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
	cout << "1. 등록 / 2. 삭제 / 3. 검색 / 4. 출력 / 5. 종료" << endl;
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
	cout << " ==== 학생 추가 ==== " << endl;
	STUDENT tStudent = {};
	cout << "이름: ";
	InputString(tStudent.strName, NAME_SIZE);
	cout << "학번: ";
	tStudent.iNumber = InputInt();
	cout << "국어점수: ";
	tStudent.iKor = InputInt();
	cout << "수학점수: ";
	tStudent.iMath = InputInt();
	cout << "영어점수: ";
	tStudent.iEng = InputInt();
	tStudent.iTotal = tStudent.iEng + tStudent.iKor + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;
	
	PNODE pNode = new NODE;
	pNode->tStudent = tStudent;
	pNode->pNext = NULL;

	// 현재 리스트에 아무런 노드도 없는 상황이라면
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
	cout << "===== 학생 삭제 =====" << endl;

	PNODE pNode = pList->pBegin; 
	
	if (pNode == NULL)
	{
		cout << "등록된 학생이 아무도 없습니다" << endl;
	}
	else
	{
		cout << "학생 이름: " << endl;
		char targetName[NAME_SIZE];
		InputString(targetName, NAME_SIZE);

		while (pNode != NULL)
		{
			if (strcmp(pNode->tStudent.strName, targetName) == 0)
			{
				// 찾은 상황
				
				// 처음이자 마지막, 즉 한개만 있는 경우
				if (pList->pBegin == pNode && pList->pEnd == pNode)
				{
					pList->pBegin = NULL;
					pList->pEnd = NULL;
				}

				// 첫번째 있으면
				else if (pList->pBegin == pNode)
				{
					pList->pBegin = pNode->pNext;
					pNode->pNext->pPrev = NULL;
				}

				// 마지막에 있으면
				else if (pList->pEnd == pNode)
				{
					pList->pEnd = pNode->pPrev;
					pNode->pPrev->pNext = NULL;
				}

				// 가운데 있으면
				else
				{
					pNode->pPrev->pNext = pNode->pNext;
					pNode->pNext->pPrev = pNode->pPrev;
				}

				delete pNode;
				cout << targetName << " 학생 삭제 완료!!" << endl;
				return;
			}
			pNode = pNode->pNext;
		}

		cout << "그런 학생은 없습니다" << endl;
	}

}

void OutputStudent(const PSTUDENT pStudent)
{
	cout << "학번: " << pStudent->iNumber << endl;
	cout << "이름: " << pStudent->strName << endl;
	cout << "평균: " << pStudent->fAvg << endl;
	cout << endl;
}

void Search(PLIST pList)
{
	system("cls");
	cout << "===== 학생 검색 =====" << endl;
	
	PNODE pNode = pList->pBegin;

	if (pNode == NULL)
	{
		cout << "등록된 학생이 아무도 없습니다" << endl;
	}
	else
	{
		cout << "학생 이름: ";
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
		
		cout << "그런 학생은 없습니다" << endl;
	}
}


void Output(PLIST pList)
{
	system("cls");
	cout << "===== 학생 출력 =====" << endl;
	if (pList->pBegin == NULL)
	{
		cout << "학생이 아무도 없습니다" << endl;
	}
	else
	{
		PNODE pNode = pList->pBegin;
		while (pNode != NULL)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
		}
		cout << "학생 출력 완료!!" << endl;
	}
}

int main()
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

	ClearList(&tList); // 동적할당한 메모리는 반드시 반납해줘야 한다.
	cout << "동적할당 메모리 반납 완료" << endl;
	return 0;
}