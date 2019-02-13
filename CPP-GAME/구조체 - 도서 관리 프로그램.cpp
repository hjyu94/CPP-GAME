// 등록 대여 반납 목록 종료
#include <iostream>

using namespace std;

#define NAME_SIZE	30
#define BOOK_MAX	1024

struct book
{
	char strName[NAME_SIZE];
	int iMoney;
	int iNumber;
	bool isLended;
};
// 이름, 대여금액, 번호, 대여 여부

enum MENU
{
	MENU_ADD = 1,
	MENU_LEND,
	MENU_RETURN,
	MENU_LIST,
	MENU_DELETE,
	MENU_OUT,
};

int main()
{
	// book arrBook[BOOK_MAX]; 이 차이가 뭘까
	// --> 0 으로 초기화 해주지 않은 상태.
	// --> 가비지 값이 들어있다.
	book arrBook[BOOK_MAX] = {};
	int iBookIdx = 0;

	char strName[NAME_SIZE];

	while (true)
	{
		system("cls");

		cout << "1. 도서 등록하기" << endl;
		cout << "2. 도서 대여하기" << endl;
		cout << "3. 도서 반납하기" << endl;
		cout << "4. 도서 목록" << endl;
		cout << "5. 도서 삭제하기" << endl;
		cout << "6. 나가기" << endl;
		cout << "입력: ";

		int iInput;
		cin >> iInput;

		if (iInput == MENU_OUT) break;

		// 숫자가 아니라 문자가 입력된 경우
		// cin.fail()은 플래그를 set(1) 하게 된다.
		if (cin.fail())
		{
			cout << "잘못된 입력입니다" << endl;

			// 내부 상태 플래그 초기화
			// 1로 set된 값을 0으로 바꾼다.
			cin.clear();

			// 버퍼 비우기
			cin.ignore(1024, '\n');

			system("pause");
			continue;
		}

		switch (iInput)
		{
		case MENU_ADD:
			system("cls");
			cout << "========== 도서 등록 ==========" << endl;
			cout << "책 이름: ";

			// 버퍼 비우기
			cin.ignore(1024, '\n');
			cin.getline(arrBook[iBookIdx].strName, NAME_SIZE);


			cout << "대여 가격: ";
			cin >> arrBook[iBookIdx].iMoney;

			// 숫자가 아니라 문자가 입력된 경우
			while (cin.fail())
			{
				cout << "숫자를 입력해주세요!" << endl;

				cin.clear();
				cin.ignore(1024, '\n');

				cout << "대여 가격: ";
				cin >> arrBook[iBookIdx].iMoney;
			}

			arrBook[iBookIdx].iNumber = iBookIdx + 1;
			arrBook[iBookIdx].isLended = false;

			++iBookIdx;

			cout << "도서를 등록했습니다" << endl;
			break;

		case MENU_LEND:
			system("cls");
			cout << "========== 도서 대여 ==========" << endl;
			cout << "빌리려는 책 이름을 검색하세요: ";

			cin.ignore(1024, '\n');
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iBookIdx; ++i)
			{
				if (strcmp(strName, arrBook[i].strName) == 0)
				{
					if (arrBook[i].isLended)
					{
						cout << "이미 대여중인 상태로 빌릴 수 없습니다" << endl;
					}
					else
					{
						arrBook[i].isLended = true;
						cout << "책을 빌렸습니다!" << endl;
					}
					break;
				}
			}
			break;

		case MENU_RETURN:
			system("cls");
			cout << "========== 도서 반납 ==========" << endl;
			cout << "반납할 책 이름을 검색하세요: ";

			cin.ignore(1024, '\n');
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iBookIdx; ++i)
			{
				if (strcmp(strName, arrBook[i].strName) == 0)
				{
					if (arrBook[i].isLended)
					{
						arrBook[i].isLended = false;
						cout << "책을 반납했습니다!" << endl;
					}
					else
					{
						cout << "빌리지 않은 도서로 반납할 수 없습니다." << endl;
					}
					break;
				}
			}
			break;

		case MENU_LIST:
			system("cls");
			cout << "========== 도서 목록 ==========" << endl;
			cout << "( 책 이름, 대여 가격, 책 번호, 대여여부 )" << endl;
			for (int i = 0; i < iBookIdx; ++i)
			{
				cout << "( " << arrBook[i].strName << ", " <<
					arrBook[i].iMoney << ", " <<
					arrBook[i].iNumber << ", " <<
					(arrBook[i].isLended ? "Yes" : "Not yet") << " )" << endl;
			}
			break;

		case MENU_DELETE:
			system("cls");
			cout << "========== 도서 삭제 ==========" << endl;

			cout << "삭제하고자 하는 책 번호: ";

			int iTargetIdx;
			cin >> iTargetIdx;

			if (cin.fail())
			{
				cout << "잘못된 입력입니다" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				break;
			}

			if (iTargetIdx <= 0)
			{
				cout << "잘못된 입력입니다" << endl;
				break;
			}

			--iTargetIdx;

			if (iBookIdx < iTargetIdx)
			{
				cout << "해당 책이 없습니다" << endl;
			}
			else
			{
				for (int i = iTargetIdx; i < iBookIdx; ++i)
				{
					arrBook[i] = arrBook[i + 1];
				}
				cout << "삭제했습니다" << endl;
			}

			--iBookIdx;

			break;
		}
		system("pause");
	}

	cout << "종료되었습니다" << endl;
}