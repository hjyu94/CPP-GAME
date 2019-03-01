#include <iostream>
#include <functional>
using namespace std;

int Sum(int a, int b)
{
	return a + b;
}

int OutSum(int a, int b)
{
	return a - b;
}

class CHanzo
{
public:
	int m_iTest;

	CHanzo() {}
	~CHanzo() {}
public:
	void Output()
	{
		cout << this->m_iTest << endl;
	}
};

typedef struct _tagPoint
{
	int x, y;

	_tagPoint() : x(0), y(0) {}

	_tagPoint(int x, int y) { x = x; y = y; }

	_tagPoint(const _tagPoint& pt)
	{
		*this = pt;
	}
};

void main()
{
	int(*pFunc)(int, int) = Sum;
	cout << pFunc(10, 20) << endl;

	CHanzo hanzo1, hanzo2;
	
	hanzo1.m_iTest = 100;
	hanzo2.m_iTest = 200;

	// Output 멤버 함수는 생기는 객체마다 메모리에 저장하는게 아니라
	// 객체가 몇개가 있는지 상관 없이 클래스 별로 하나만 존재한다.

	// 멤버함수를 호출할 때 this를 호출자로 세팅한다.
	hanzo1.Output();
	hanzo2.Output();

	void (CHanzo::*pFunc2)() = &CHanzo::Output;
	//pFunc2();
	(hanzo1.*pFunc2)(); // 이렇게만 가능

	function<void()> func;
	function<void()> func1;

	func1 = bind(&CHanzo::Output, &hanzo1)


}