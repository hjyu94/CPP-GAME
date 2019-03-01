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

	// Output ��� �Լ��� ����� ��ü���� �޸𸮿� �����ϴ°� �ƴ϶�
	// ��ü�� ��� �ִ��� ��� ���� Ŭ���� ���� �ϳ��� �����Ѵ�.

	// ����Լ��� ȣ���� �� this�� ȣ���ڷ� �����Ѵ�.
	hanzo1.Output();
	hanzo2.Output();

	void (CHanzo::*pFunc2)() = &CHanzo::Output;
	//pFunc2();
	(hanzo1.*pFunc2)(); // �̷��Ը� ����

	function<void()> func;
	function<void()> func1;

	func1 = bind(&CHanzo::Output, &hanzo1)


}