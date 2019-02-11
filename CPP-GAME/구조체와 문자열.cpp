// Ctrl + 단어 위에서 마우스 좌 클릭 : 그 단어 전체 블록된다

#include <iostream>

using namespace std;

#define NAME_SIZE		32
#define ADDRESS_SIZE	128
#define PHONE_SIZE		14 // OOO-OOOO-OOOO(+널) : 14개

#define STUDENT_MAX		10

struct _tagStudent
{
	char strName[NAME_SIZE];
	char strAddress[ADDRESS_SIZE];
	char strPhone[PHONE_SIZE];
	int iNumber, iKor, iEng, iMath;
	int iTotal;
	float fAvg;
};

enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT,
};

int main()
{
	_tagStudent tStudentArr[STUDENT_MAX] = {};

	int iStudentCount = 0;
	int iStdNumber = 1;

	while (true)
	{
		system("cls"); // clear console

		// 메뉴를 출력한다
		cout << "1. 등록" << endl;
		cout << "2. 삭제" << endl;
		cout << "3. 검색" << endl;
		cout << "4. 출력" << endl;
		cout << "5. 나가기" << endl;
		cout << "메뉴를 선택하세요: ";

		int iMenu;
		char strName[NAME_SIZE];

		cin >> iMenu;

		// 실수로 정수가 아니라 문자를 입력할 경우 에러가 발생한다.
		// 에러를 체크한다
		if (cin.fail())
		{
			cout << "입력된 값: " << iMenu << endl;
			cout << "에러가 발생하여 버퍼를 지웁니다" << endl;

			// 에러 버퍼를 지워준다.
			cin.clear();

			// 입력버퍼를 검색하여 \n을 지워준다
			// 검색하고자 하는 버퍼 크기: 1024
			// 찾고자 하는 문자를 넣어준다.
			// 처음부터 \n이 있는 곳까지 찾아서 그 부분을 모두 지운다
			cin.ignore(1024, '\n');

			system("pause");

			continue; // while문 처음으로 돌아간다
		}

		if (iMenu == MENU_EXIT) break;
		// switch 문 안에서 break는 while을 빠져나가지 못해서 따로 밴다

		switch (iMenu)
		{
		case MENU_INSERT:
			// 학생 정보를 추가한다. 
			// 이름, 주소, 전화번호, 국어, 영어, 수학 점수는 입력받고
			// 총점, 평균은 연산을 통해 계산해준다.

			// 등록될 수 있는 학생 수 정원 초과인 경우 등록 실패	 
			if (iStudentCount >= STUDENT_MAX) 
			{
				cout << "정원초과로 더 이상 등록할 수 없습니다";
				system("pause");
				break;
			}

			system("cls");
			cout << "================ 학생 등록 ================" << endl;
			
			cout << "이름: ";
			cin >> tStudentArr[iStudentCount].strName;
			
			cout << "주소: ";
			
			cin.ignore(1024, '\n'); 
			// 얘가 없으면 버퍼에 \n 이 남아있어서 주소가 이미 입력된 상태로 뜬다.
			
			/*
				 cin >> tStudentArr[iStudentCount].strAddress;
				서울 구로구 구로동 --> 서울만 입력된다
				cin.getline() 를 이용해야 한다
			*/	
			cin.getline(tStudentArr[iStudentCount].strAddress, ADDRESS_SIZE);
			
			cout << "전화번호: ";
			cin.getline(tStudentArr[iStudentCount].strPhone, PHONE_SIZE);

			cout << "국어: ";
			cin >> tStudentArr[iStudentCount].iKor;

			cout << "영어: ";
			cin >> tStudentArr[iStudentCount].iEng;

			cout << "수학: ";
			cin >> tStudentArr[iStudentCount].iMath;

			tStudentArr[iStudentCount].iTotal =
				tStudentArr[iStudentCount].iKor +
				tStudentArr[iStudentCount].iEng +
				tStudentArr[iStudentCount].iMath;

			tStudentArr[iStudentCount].fAvg =
				tStudentArr[iStudentCount].iTotal / 3.f;
			
			++iStdNumber, ++iStudentCount;

			break;

		case MENU_DELETE:
			system("cls");
			cout << "================ 학생 삭제 ================" << endl;
			
			// 메뉴 선택에서 2+엔터 --> 버퍼에 엔터가 남아있음
			cin.ignore(1024, '\n');

			cout << "삭제할 이름을 입력하세요: ";
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iStudentCount; ++i)
			{
				// 학생을 찾았을 경우
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					for (int index = i; index < iStudentCount-1; ++index)
					{
						tStudentArr[i] = tStudentArr[i + 1];
					}
					--iStudentCount, --iStdNumber;
				}
			}

			break;

		case MENU_SEARCH:
			system("cls");
			cout << "================ 학생 검색 ================" << endl;

			//char strSearchName[NAME_SIZE] = {};
			//// error C2360 : 'strSearchName' 초기화가 'case' 레이블에 의해 생략되었습니다.
			//// case문 변수를 선언하고 초기화하는 경우 문제가 생길 수 있어서
			//// case문 밖에서 선언해주고 사용해야 한다.

			cin.ignore(1024, '\n');
			// 메뉴 선택에서 3+엔터 --> 버퍼에 엔터가 남아있음

			cout << "탐색할 이름을 입력하세요: ";
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iStudentCount; ++i)
			{
				// 학생을 찾았을 경우
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					cout << "이름: " << tStudentArr[i].strName << endl;
					cout << "전화번호: " << tStudentArr[i].strPhone << endl;
					cout << "주소: " << tStudentArr[i].strAddress << endl;
					cout << "학번: " << tStudentArr[i].iNumber << endl;
					cout << "평균: " << tStudentArr[i].fAvg << endl;
					cout << endl;

					break; // 검색한 경우 더 이상 검색할 필요가 없으므로 for문을 빠져나간다
				}
			}

			break;
			


		case MENU_OUTPUT:
			system("cls");
			cout << "================ 학생 출력 ================" << endl;

			// 등록된 학생 수 만큼 반복하며 학생 정보를 출력한다.
			for (int i = 0; i < iStudentCount; ++i)
			{
				cout << "이름: " << tStudentArr[i].strName << endl;
				cout << "전화번호: " << tStudentArr[i].strPhone << endl;
				cout << "주소: " << tStudentArr[i].strAddress << endl;
				cout << "학번: " << tStudentArr[i].iNumber << endl;
				cout << "평균: " << tStudentArr[i].fAvg << endl;
				cout << endl;
			}

			break;

		}

		system("pause");
	}

	return 0;
}