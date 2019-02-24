#include <iostream>
using namespace std;

void My_fopen_s(int** pFile)
{
	*pFile = new int;
	// 동적할당: 데이터의 크기만큼을 메모리에 할당 한 후 그 메모리의 주소를 리턴함
}
/*
	(0x100) p: 0
	(0x200) pFile: 0x100

	인 상황일때 *pFile = new int; 가 실행되면
	메모리에 int를 담을 공간을 확보하고
	동적할당의 리턴값으로 그 공간의 주소를 받아
	pFile 가리키는 곳에 그 주소를 적는다

	동적할당해서 만든 곳의 메모리 주소가 0x300 이라고 하면
	(0x100) p: 0x300
	(0x300) 동적할당으로 확보한 4 byte
*/

void main()
{
	int* p = NULL;
	My_fopen_s(&p);
	
	// 일종의 핸들
	FILE*	pFile = NULL;

	while (true)
	{
		system("cls");

		int iInput;
		cout << "1: 파일 쓰기, 2: 읽기" << endl;
		cin >> iInput;

		/********************************** 파일 쓰기 ****************************************/
		if (iInput == 1)
		{

			// fopen(...) -> fopen_s(...)
			// 안정성 때문에 업그레이드 됨

			// fopen(): call by value 방식
			// fopen_s(): call by pointer 방식

			// 파일을 만드는 등은 OS의 권한! 우리가 컨트롤할 수 없음.
			// 우리는 권한이 없기 때문에 파일을 임의로 동적할당 할 수 없고
			// 함수 안에서 운영체제가 내부적으로 파일을 만들어준 후 
			// 이를 컨트롤할 수 있는 주소(포인터)를 이용하는 방식. 
			// (만들어진 파일의 주소를 pFile 값으로 갖고 이를 컨트롤하자.)

			// 1번 인자: 파일의 이중포인터이다
			// 2번 인자: 파일 경로. 현재 프로젝트가 있는 폴더. 만약 exe로 실행할 경우 해당 exe 파일이 있는 경로를 기준으로 새성
			// 3번 인자: 파일 모드. r:읽기, w:쓰기, a:접근 / t:텍스트 파일, b:바이너리 파일

			fopen_s(&pFile, "hot.txt", "wt"); // write + txt

			// pFile이 NULL 이면 파일 만들기 실패
			if (pFile != NULL)
			{
				char* pText = "abcd";

				// fwrite, fread / fputs, fgets

				// 1번 인자: void 포인터. 저장하고자 하는 값의 메모리 주소를 넣어준다.
				// (void pointer: 어떤 데이터가 들어올 지 모르는 경우, 모든 데이터 타입의 포인터 받을 수 있다. 단순 메모리 주소 저장용. 역참조 불가능)
				// 2번 인자: element size. 저장하고자 하는 값의 변수 타입의 메모리 크기를 넣어준다.
				// 3번 인자: element count. 저장하조가 하는 값의 개수를 넣어준다.
				// 4번 인자: 저장할 파일의 스트림

				fwrite(pText, 1, 4, pFile); // null 문자 넣어주지 않아도 됨. 굳이 5라고 적어줄 필요 없음

				fclose(pFile); // 닫아줘야 다른데서 열 수 있다.

				cout << "파일 만들기 성공!" << endl;
			}
		}
		
		/******************************** 파일 읽기 *******************************************/
		else if (iInput == 2)
		{
			fopen_s(&pFile, "hot.txt", "rt"); // read + txt

			// true일 경우에만	 
			if (pFile)
			{
				char strText[5] = {};
				fread(strText, 1, 4, pFile);
				
				cout << strText << endl;

				fclose(pFile);
				cout << "파일 읽기 성공!" << endl;
			}

		}

		system("pause");
	}
}
