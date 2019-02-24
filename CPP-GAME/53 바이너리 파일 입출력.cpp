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
	/************** 파일 쓰기 ***************/
	//STUDENT tStudent[STUDENT_MAX] = {};
	//
	//for (int i = 0; i < STUDENT_MAX; ++i)
	//{
	//	cout << "이름: ";
	//	
	//	cin >> tStudent[i].strName;

	//	tStudent[i].iNumber = i + 1;

	//	cout << "국어점수: ";
	//	cin >> tStudent[i].iKor;
	//	cout << "수학점수: ";
	//	cin >> tStudent[i].iMath;
	//	cout << "영어점수: ";
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
	//	// 학생 수를 저장한다.
	//	fwrite(&iStudentCount, 4, 1, pFile);

	//	for (int i = 0; i < iStudentCount; ++i)
	//	{
	//		// 학생 구조체를 통으로 저장한다.
	//		fwrite(&tStudent[i], sizeof(STUDENT), 1, pFile);
	//	}
	//}

	/************** 파일 읽기 ***************/
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

	// 읽어온 학생을 출력한다
	for (int i = 0; i < iStudentCount; ++i)
	{
		cout << "이름: " << tStudent[i].strName << endl;
		cout << "학번: " << tStudent[i].iNumber << endl;
		cout << "국어: " << tStudent[i].iKor << endl;
		cout << "영어: " << tStudent[i].iEng << endl;
		cout << "수학: " << tStudent[i].iMath << endl;
		cout << "총점: " << tStudent[i].iTotal << endl;
		cout << "평균: " << tStudent[i].fAvg << endl;
		cout << endl;
	}

}