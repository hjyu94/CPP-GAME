#include <iostream>

using namespace std;

void main()
{
	// char pText[] = "�׽�Ʈ ���ڿ�";
	char *pText = "�׽�Ʈ ���ڿ�";

	cout << pText << endl;
	cout << (int*)pText << endl;
	// cout�� ���ڿ� �ּҰ� ������ ���ڿ��� ������� �ּҸ� ������� �ʴ´�.

	/****************************************************************/

	// pText[0] = 'A'; // X
	// pText[1] = 'B'; // X
	// char *pText;
	// const char *pText;
	// ���������� const�� �پ ������ ������
	// ���Ұ��� ������ �� ����.

	pText = "�ٲ���!!"; // ��� ����
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
	// ���ڿ��� ������ ������ ���� �ּҸ� ����Ų��.
	cout << (int*)arrText << endl;
	// �� �Ϲ� �迭�� ���� ������ ��´ٸ� �ּҴ� �޶�����.
}