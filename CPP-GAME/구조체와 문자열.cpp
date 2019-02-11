// Ctrl + �ܾ� ������ ���콺 �� Ŭ�� : �� �ܾ� ��ü ��ϵȴ�

#include <iostream>

using namespace std;

#define NAME_SIZE		32
#define ADDRESS_SIZE	128
#define PHONE_SIZE		14 // OOO-OOOO-OOOO(+��) : 14��

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

		// �޴��� ����Ѵ�
		cout << "1. ���" << endl;
		cout << "2. ����" << endl;
		cout << "3. �˻�" << endl;
		cout << "4. ���" << endl;
		cout << "5. ������" << endl;
		cout << "�޴��� �����ϼ���: ";

		int iMenu;
		char strName[NAME_SIZE];

		cin >> iMenu;

		// �Ǽ��� ������ �ƴ϶� ���ڸ� �Է��� ��� ������ �߻��Ѵ�.
		// ������ üũ�Ѵ�
		if (cin.fail())
		{
			cout << "�Էµ� ��: " << iMenu << endl;
			cout << "������ �߻��Ͽ� ���۸� ����ϴ�" << endl;

			// ���� ���۸� �����ش�.
			cin.clear();

			// �Է¹��۸� �˻��Ͽ� \n�� �����ش�
			// �˻��ϰ��� �ϴ� ���� ũ��: 1024
			// ã���� �ϴ� ���ڸ� �־��ش�.
			// ó������ \n�� �ִ� ������ ã�Ƽ� �� �κ��� ��� �����
			cin.ignore(1024, '\n');

			system("pause");

			continue; // while�� ó������ ���ư���
		}

		if (iMenu == MENU_EXIT) break;
		// switch �� �ȿ��� break�� while�� ���������� ���ؼ� ���� ���

		switch (iMenu)
		{
		case MENU_INSERT:
			// �л� ������ �߰��Ѵ�. 
			// �̸�, �ּ�, ��ȭ��ȣ, ����, ����, ���� ������ �Է¹ް�
			// ����, ����� ������ ���� ������ش�.

			// ��ϵ� �� �ִ� �л� �� ���� �ʰ��� ��� ��� ����	 
			if (iStudentCount >= STUDENT_MAX) 
			{
				cout << "�����ʰ��� �� �̻� ����� �� �����ϴ�";
				system("pause");
				break;
			}

			system("cls");
			cout << "================ �л� ��� ================" << endl;
			
			cout << "�̸�: ";
			cin >> tStudentArr[iStudentCount].strName;
			
			cout << "�ּ�: ";
			
			cin.ignore(1024, '\n'); 
			// �갡 ������ ���ۿ� \n �� �����־ �ּҰ� �̹� �Էµ� ���·� ���.
			
			/*
				 cin >> tStudentArr[iStudentCount].strAddress;
				���� ���α� ���ε� --> ���︸ �Էµȴ�
				cin.getline() �� �̿��ؾ� �Ѵ�
			*/	
			cin.getline(tStudentArr[iStudentCount].strAddress, ADDRESS_SIZE);
			
			cout << "��ȭ��ȣ: ";
			cin.getline(tStudentArr[iStudentCount].strPhone, PHONE_SIZE);

			cout << "����: ";
			cin >> tStudentArr[iStudentCount].iKor;

			cout << "����: ";
			cin >> tStudentArr[iStudentCount].iEng;

			cout << "����: ";
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
			cout << "================ �л� ���� ================" << endl;
			
			// �޴� ���ÿ��� 2+���� --> ���ۿ� ���Ͱ� ��������
			cin.ignore(1024, '\n');

			cout << "������ �̸��� �Է��ϼ���: ";
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iStudentCount; ++i)
			{
				// �л��� ã���� ���
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
			cout << "================ �л� �˻� ================" << endl;

			//char strSearchName[NAME_SIZE] = {};
			//// error C2360 : 'strSearchName' �ʱ�ȭ�� 'case' ���̺� ���� �����Ǿ����ϴ�.
			//// case�� ������ �����ϰ� �ʱ�ȭ�ϴ� ��� ������ ���� �� �־
			//// case�� �ۿ��� �������ְ� ����ؾ� �Ѵ�.

			cin.ignore(1024, '\n');
			// �޴� ���ÿ��� 3+���� --> ���ۿ� ���Ͱ� ��������

			cout << "Ž���� �̸��� �Է��ϼ���: ";
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iStudentCount; ++i)
			{
				// �л��� ã���� ���
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					cout << "�̸�: " << tStudentArr[i].strName << endl;
					cout << "��ȭ��ȣ: " << tStudentArr[i].strPhone << endl;
					cout << "�ּ�: " << tStudentArr[i].strAddress << endl;
					cout << "�й�: " << tStudentArr[i].iNumber << endl;
					cout << "���: " << tStudentArr[i].fAvg << endl;
					cout << endl;

					break; // �˻��� ��� �� �̻� �˻��� �ʿ䰡 �����Ƿ� for���� ����������
				}
			}

			break;
			


		case MENU_OUTPUT:
			system("cls");
			cout << "================ �л� ��� ================" << endl;

			// ��ϵ� �л� �� ��ŭ �ݺ��ϸ� �л� ������ ����Ѵ�.
			for (int i = 0; i < iStudentCount; ++i)
			{
				cout << "�̸�: " << tStudentArr[i].strName << endl;
				cout << "��ȭ��ȣ: " << tStudentArr[i].strPhone << endl;
				cout << "�ּ�: " << tStudentArr[i].strAddress << endl;
				cout << "�й�: " << tStudentArr[i].iNumber << endl;
				cout << "���: " << tStudentArr[i].fAvg << endl;
				cout << endl;
			}

			break;

		}

		system("pause");
	}

	return 0;
}