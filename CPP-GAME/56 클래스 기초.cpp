#include <iostream>

using namespace std;

/*
객체(object):
	

객체지향 프로그래밍(OOP):

*/

void main()
{
	/*
		레퍼런스: 다른 대상을 참조하게 만들어주는 기능이다.
		참조를 하게 되면 그 대상에 접근하여 값을 변경할 수 있다.
		처음 레퍼런스 변수 생성시 참조하는 대상을 지정해주어야 한다.
	*/
	int iNumber = 100;
	int iNumber1 = 9999;

	// iRefNum 레퍼런스 변수는 iNumber를 참조한다.
	int &iRefNum = iNumber;
	
	iRefNum = 1234;

	iRefNum = iNumber1; 
	// iRefNum에 넣어줬을 뿐인데 iNumber도 바뀜
	// iRefNum이 iNumber를 참조하고 있었는데 
	// iNumber1을 참조하게끔 바꿀 수 없음
	// 참조하는 대상의 값을 바꿈

	cout << iNumber << endl;
	
	cout << sizeof(bool&) << endl;
	cout << sizeof(int&) << endl;
	cout << sizeof(double&) << endl;

	/*****************************************************/

	
}