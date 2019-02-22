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
링크드리스트 : 자료구조의 한 종류이다. 자료구조란 데이터를 관리하는 방법을 말한다.
링크드리스트는 데이터 목록을 연결시켜서 접근할 수 있는 구조를 제공한다.
링크드리스트는 데이터를 저장하기 위한 노드라는 것이 존재한다.
각 노드의 특징은 다음 노드를 알 수 있게 된다. (다음 노드의 메모리 주소 저장)
리스트는 선형구조로 되어있다. -> 배열처럼 특정 요소에 바로 접근이 불가능
무조건 앞에서부터 차례대로 타고 들어가야 한다.
노드를 새로 추가할때는 노드를 생성하고 마지막 노드에 연결만 해주면 되기 때문에
개수에 제한이 없다. 메모리가 허용하는 한도 내에서는 계속 만들어낼수 있다.
*/

// 리스트 노드를 만든다
typedef struct _tagNode
{
	STUDENT		tStudent;
	_tagNode*	pNext;
} NODE, *PNODE;

// 리스트 구조체를 만들어준다
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
		cin.clear(); // 버퍼 플래그 바꿔주기
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return iInput;
}

void InputString(char* pString, int iSize)
{
	// 버퍼에 엔터가 남아있을 수 있다.
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize - 1); // 마지막 1바이트는 NULL
	
}
void InitList(PLIST pList)
{
	// 포인터는 가급적이면 초기화할때 null(0) 으로 초기화해두고 쓰는 것이 좋다.
	// 왜냐하면 0은 false 0이 아닌 모든 수는 true이기 때문이다.
	// 초기화를 하지 않을 경우 들어가있는 쓰레기 값은 true이다.
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

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

void Insert(PLIST pList)
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
}

void Output(PLIST pList)
{
	system("cls");
	cout << "=========학생출력========" << endl;

	PNODE	pNode = pList->pBegin;

	if (pNode == NULL) 
	{
		cout << "아직 등록된 학생이 없습니다" << endl;
	}

	else
	{
		while(pNode != NULL)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
			cout << endl;
		}
		cout << "학생수: " << pList->iSize << endl;
	}

}

void Search(PLIST pList)
{
	/*
		system("cls");
		cout << "=========학생검색========" << endl;
	
		char targetString[NAME_SIZE];
		bool bExist = false;

		cout << "탐색할 이름을 입력하세요 :";
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
			cout << "등록 학생이 없습니다" << endl;
		}
	*/

	system("cls");
	cout << "=========학생검색========" << endl;

	char targetString[NAME_SIZE];
	// bool bExist = false;

	cout << "탐색할 이름을 입력하세요 :";
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

	// while문을 빠져나올때까지 찾지 못했다는 것
	cout << "등록 학생이 없습니다" << endl;
}

void Delete(PLIST pList)
{
	system("cls");
	cout << "=========학생삭제========" << endl;

	/*
		if (pList->iSize == 0)
		{
			cout << "학생수: 0" << endl;
			return;
		}
		else
		{
			cout << "삭제할 이름을 입력하세요 : ";
			char targetName[NAME_SIZE];
			InputString(targetName, NAME_SIZE);

			PNODE pNode = pList->pBegin;
			PNODE pPrev;

			while (pNode != NULL)
			{
				if (strcmp(pNode->tStudent.strName, targetName) == 0)
				{
					// 리스트에 노드가 하나뿐인 경우
					if (pList->iSize == 1)
					{
						pList->pBegin = NULL;
						pList->pEnd = NULL; // 빼먹으면 안돼!
					}

					// 타겟 노드가 첫번째에 있는 경우
					else if (pNode == pList->pBegin)
					{
						pList->pBegin = pNode->pNext;
					}

					// 타겟 노드가 마지막에 있는 경우
					else if (pNode == pList->pEnd)
					{
						pPrev->pNext = NULL;
						pList->pEnd = pNode;
					}

					// 타겟노드가 중간에 있는 경우
					else
					{
						pPrev->pNext = pNode->pNext;
					}
				
					delete pNode;
					--(pList->iSize);
					// cout << pNode->tStudent.strName << "학생 삭제 완료!!" << endl;
					// cout << targetName << "학생 삭제 완료!!" << endl;

					return;
				}

				pPrev = pNode;
				pNode = pNode->pNext;
			}

			cout << "그런 학생은 존재하지 않습니다" << endl;
		}
	*/

	cout << "삭제할 이름을 입력하세요: ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE	pNode = pList->pBegin;
	PNODE	pPrev = NULL;

	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			// 지울 노드의 다음 노드를 얻어온다
			PNODE	pNext = pNode->pNext;
			
			// 만약 이전 노드가 NULL 이라면 제일 첫번째 노드를 지운다는 의미이다.
			if (pPrev == NULL)
			{
				delete pNode;
				pList->pBegin = pNext;

				// 이후 노드도 NULL이라면 현재 상황은 노드가 1개뿐인 상황
				if (pNext == NULL)
					pList->pEnd = NULL;
			}

			// 이전 노드가 있는 경우에는 이전 노드의 다음을 지운 노드의 다음 노드로 연결
			else
			{
				delete pNode;
				pPrev->pNext = pNext;

				// 만약 지운 노드가 제일 마지막 노드였다면
				if (pNext == NULL)
					pList->pEnd = pPrev;
			}

			// cout << pNode->tStudent.strName << "학생 삭제완료!!" << endl;
			// pNode 메모리 반납해서 이상한 값 출력됨
			cout << strName << "학생 삭제완료!!" << endl;

			--(pList->iSize);
			return;
		}
		
		// 해당 노드와 이름이 일치하지 않으면 현재 노드가 이전 노드가 된다
		pPrev = pNode;
		pNode = pNode->pNext;
	}

	cout << "삭제할 학생을 찾을 수 없습니다" << endl;
	system("pause");
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
	cout << "메모리 반납 완료" << endl;
	return 0;
}