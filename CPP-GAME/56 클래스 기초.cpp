#include <iostream>

using namespace std;

/*
��ü(object):
	

��ü���� ���α׷���(OOP):

*/

void main()
{
	/*
		���۷���: �ٸ� ����� �����ϰ� ������ִ� ����̴�.
		������ �ϰ� �Ǹ� �� ��� �����Ͽ� ���� ������ �� �ִ�.
		ó�� ���۷��� ���� ������ �����ϴ� ����� �������־�� �Ѵ�.
	*/
	int iNumber = 100;
	int iNumber1 = 9999;

	// iRefNum ���۷��� ������ iNumber�� �����Ѵ�.
	int &iRefNum = iNumber;
	
	iRefNum = 1234;

	iRefNum = iNumber1; 
	// iRefNum�� �־����� ���ε� iNumber�� �ٲ�
	// iRefNum�� iNumber�� �����ϰ� �־��µ� 
	// iNumber1�� �����ϰԲ� �ٲ� �� ����
	// �����ϴ� ����� ���� �ٲ�

	cout << iNumber << endl;
	
	cout << sizeof(bool&) << endl;
	cout << sizeof(int&) << endl;
	cout << sizeof(double&) << endl;

	/*****************************************************/

	
}