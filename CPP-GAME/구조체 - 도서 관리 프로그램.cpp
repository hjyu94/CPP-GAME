// ��� �뿩 �ݳ� ��� ����
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
// �̸�, �뿩�ݾ�, ��ȣ, �뿩 ����

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
	// book arrBook[BOOK_MAX]; �� ���̰� ����
	// --> 0 ���� �ʱ�ȭ ������ ���� ����.
	// --> ������ ���� ����ִ�.
	book arrBook[BOOK_MAX] = {};
	int iBookIdx = 0;

	char strName[NAME_SIZE];

	while (true)
	{
		system("cls");

		cout << "1. ���� ����ϱ�" << endl;
		cout << "2. ���� �뿩�ϱ�" << endl;
		cout << "3. ���� �ݳ��ϱ�" << endl;
		cout << "4. ���� ���" << endl;
		cout << "5. ���� �����ϱ�" << endl;
		cout << "6. ������" << endl;
		cout << "�Է�: ";

		int iInput;
		cin >> iInput;

		if (iInput == MENU_OUT) break;

		// ���ڰ� �ƴ϶� ���ڰ� �Էµ� ���
		// cin.fail()�� �÷��׸� set(1) �ϰ� �ȴ�.
		if (cin.fail())
		{
			cout << "�߸��� �Է��Դϴ�" << endl;

			// ���� ���� �÷��� �ʱ�ȭ
			// 1�� set�� ���� 0���� �ٲ۴�.
			cin.clear();

			// ���� ����
			cin.ignore(1024, '\n');

			system("pause");
			continue;
		}

		switch (iInput)
		{
		case MENU_ADD:
			system("cls");
			cout << "========== ���� ��� ==========" << endl;
			cout << "å �̸�: ";

			// ���� ����
			cin.ignore(1024, '\n');
			cin.getline(arrBook[iBookIdx].strName, NAME_SIZE);


			cout << "�뿩 ����: ";
			cin >> arrBook[iBookIdx].iMoney;

			// ���ڰ� �ƴ϶� ���ڰ� �Էµ� ���
			while (cin.fail())
			{
				cout << "���ڸ� �Է����ּ���!" << endl;

				cin.clear();
				cin.ignore(1024, '\n');

				cout << "�뿩 ����: ";
				cin >> arrBook[iBookIdx].iMoney;
			}

			arrBook[iBookIdx].iNumber = iBookIdx + 1;
			arrBook[iBookIdx].isLended = false;

			++iBookIdx;

			cout << "������ ����߽��ϴ�" << endl;
			break;

		case MENU_LEND:
			system("cls");
			cout << "========== ���� �뿩 ==========" << endl;
			cout << "�������� å �̸��� �˻��ϼ���: ";

			cin.ignore(1024, '\n');
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iBookIdx; ++i)
			{
				if (strcmp(strName, arrBook[i].strName) == 0)
				{
					if (arrBook[i].isLended)
					{
						cout << "�̹� �뿩���� ���·� ���� �� �����ϴ�" << endl;
					}
					else
					{
						arrBook[i].isLended = true;
						cout << "å�� ���Ƚ��ϴ�!" << endl;
					}
					break;
				}
			}
			break;

		case MENU_RETURN:
			system("cls");
			cout << "========== ���� �ݳ� ==========" << endl;
			cout << "�ݳ��� å �̸��� �˻��ϼ���: ";

			cin.ignore(1024, '\n');
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iBookIdx; ++i)
			{
				if (strcmp(strName, arrBook[i].strName) == 0)
				{
					if (arrBook[i].isLended)
					{
						arrBook[i].isLended = false;
						cout << "å�� �ݳ��߽��ϴ�!" << endl;
					}
					else
					{
						cout << "������ ���� ������ �ݳ��� �� �����ϴ�." << endl;
					}
					break;
				}
			}
			break;

		case MENU_LIST:
			system("cls");
			cout << "========== ���� ��� ==========" << endl;
			cout << "( å �̸�, �뿩 ����, å ��ȣ, �뿩���� )" << endl;
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
			cout << "========== ���� ���� ==========" << endl;

			cout << "�����ϰ��� �ϴ� å ��ȣ: ";

			int iTargetIdx;
			cin >> iTargetIdx;

			if (cin.fail())
			{
				cout << "�߸��� �Է��Դϴ�" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				break;
			}

			if (iTargetIdx <= 0)
			{
				cout << "�߸��� �Է��Դϴ�" << endl;
				break;
			}

			--iTargetIdx;

			if (iBookIdx < iTargetIdx)
			{
				cout << "�ش� å�� �����ϴ�" << endl;
			}
			else
			{
				for (int i = iTargetIdx; i < iBookIdx; ++i)
				{
					arrBook[i] = arrBook[i + 1];
				}
				cout << "�����߽��ϴ�" << endl;
			}

			--iBookIdx;

			break;
		}
		system("pause");
	}

	cout << "����Ǿ����ϴ�" << endl;
}