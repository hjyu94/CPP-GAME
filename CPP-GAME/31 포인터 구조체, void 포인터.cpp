#include <iostream>

using namespace std;

struct _tagStudent
{
	int a, b, c, d;
};

int main()
{
	_tagStudent tStudent = {};
	_tagStudent *pStudent = &tStudent;

	// 연산자 우선순위 때문에 * 보다 . 을 먼저 인식한다
	// ()를 이용해야 한다
	(*pStudent).a = 100;
	pStudent->a = 100;

	// void: 타입이 없다
	// void*: 어떤 타입의 메모리 주소든 모두 저장 가능하다
	
	// cf) 
	double d; int* ptr_i = &d; // 불가능

	// 단 역참조가 불가능하고 메모리 주소만 저장 가능하다

	int		iNumber = 100;
	void*	pVoid = &iNumber;

	cout << "iNumber Address: " << pVoid << endl;
	pVoid = &tStudent;

	cout << "tStudent Address: " << pVoid << endl;
	
	cout << *pVoid << endl; // 불가능
	cout << *((int*)pVoid) << endl; // 명시적 형변환을 이용해서 표현은 가능
}