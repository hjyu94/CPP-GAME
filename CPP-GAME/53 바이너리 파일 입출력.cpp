#include <iostream>
using namespace std;

#define NAME_SIZE	32
#define STUDENT_MAX	3

typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor, iEng, iMath;
	int		iTotal;
	float	fAvg;
} STUDENT, *PSTUDENT;

void main()
{
	/************** ���� ���� ***************/
	//STUDENT tStudent[STUDENT_MAX] = {};
	//
	//for (int i = 0; i < STUDENT_MAX; ++i)
	//{
	//	cout << "�̸�: ";
	//	
	//	cin >> tStudent[i].strName;

	//	tStudent[i].iNumber = i + 1;

	//	cout << "��������: ";
	//	cin >> tStudent[i].iKor;
	//	cout << "��������: ";
	//	cin >> tStudent[i].iMath;
	//	cout << "��������: ";
	//	cin >> tStudent[i].iEng;

	//	tStudent[i].iTotal = tStudent[i].iEng + tStudent[i].iKor + tStudent[i].iMath;
	//	tStudent[i].fAvg = tStudent[i].iTotal / 3.f;
	//}

	//int iStudentCount = STUDENT_MAX;
	//
	//FILE* pFile = NULL;

	//fopen_s(&pFile, "Student.std", "wb"); // write + binary

	//if (pFile)
	//{
	//	// �л� ���� �����Ѵ�.
	//	fwrite(&iStudentCount, 4, 1, pFile);

	//	for (int i = 0; i < iStudentCount; ++i)
	//	{
	//		// �л� ����ü�� ������ �����Ѵ�.
	//		fwrite(&tStudent[i], sizeof(STUDENT), 1, pFile);
	//	}
	//}

	/************** ���� �б� ***************/
	STUDENT tStudent[STUDENT_MAX] = {};

	FILE* pFile = NULL;
	fopen_s(&pFile, "Student.std", "rb");

	int iStudentCount;

	if (pFile)
	{
		fread(&iStudentCount, 4, 1, pFile);

		for (int i = 0; i < iStudentCount; ++i)
		{
			fread(&tStudent[i], sizeof(STUDENT), 1, pFile);
		}

		fclose(pFile);
	}

	// �о�� �л��� ����Ѵ�
	for (int i = 0; i < iStudentCount; ++i)
	{
		cout << "�̸�: " << tStudent[i].strName << endl;
		cout << "�й�: " << tStudent[i].iNumber << endl;
		cout << "����: " << tStudent[i].iKor << endl;
		cout << "����: " << tStudent[i].iEng << endl;
		cout << "����: " << tStudent[i].iMath << endl;
		cout << "����: " << tStudent[i].iTotal << endl;
		cout << "���: " << tStudent[i].fAvg << endl;
		cout << endl;
	}

}