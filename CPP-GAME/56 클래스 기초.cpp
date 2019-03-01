#include <iostream>

using namespace std;

/*
객체(object):
	

객체지향 프로그래밍(OOP):
	객체들의 관계를 설정해주어서 부품을 조립하듯이 객체를 조립해 완성된 프로그램을 만들어가는 방식

클래스의 4가지 속성
	- 캡슐화: 클래스 안의 여러 변수, 함수를 하나의 클래스로 묶을 수 있다.
	- 은닉화: 클래스 안에 속하는 변수, 함수를 내가 원하는 부분만 공개
			(public, protected, private)
	- 상속성: 부무 자식 관계 형성. 
	- 다형성: 부모 자식 관계로 상속관계가 형성되어 잇는 클래스간 서로 형
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