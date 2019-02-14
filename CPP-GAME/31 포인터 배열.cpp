#include <iostream>

using namespace std;

void main()
{
	// char pText[] = "테스트 문자열";
	char *pText = "테스트 문자열";

	cout << pText << endl;
	cout << (int*)pText << endl;
	// cout은 문자열 주소가 들어오면 문자열을 출력하지 주소를 출력하지 않는다.

	/****************************************************************/

	// pText[0] = 'A'; // X
	// pText[1] = 'B'; // X
	// char *pText;
	// const char *pText;
	// 내부적으로 const가 붙어서 나오기 때문에
	// 원소값을 변경할 수 없다.

	pText = "바꾸자!!"; // 얘는 가능
	cout << pText << endl;
	cout << endl;
	
	/****************************************************************/

	char *pTest1 = "A";
	char *pTest2 = "A";
	char *pTest3 = "AAA";
	char arrText[4] = "AAA";

	cout << (int*)pTest1 << endl; // 100
	cout << (int*)pTest2 << endl; // 100
	cout << (int*)pTest3 << endl; // 200
	// 문자열의 내용이 같으면 같은 주소를 가리킨다.
	cout << (int*)arrText << endl;
	// 단 일반 배열에 같은 내용을 담는다면 주소는 달라진다.
}