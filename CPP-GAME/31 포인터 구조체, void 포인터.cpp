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

	// ������ �켱���� ������ * ���� . �� ���� �ν��Ѵ�
	// ()�� �̿��ؾ� �Ѵ�
	(*pStudent).a = 100;
	pStudent->a = 100;

	// void: Ÿ���� ����
	// void*: � Ÿ���� �޸� �ּҵ� ��� ���� �����ϴ�
	
	// cf) 
	double d; int* ptr_i = &d; // �Ұ���

	// �� �������� �Ұ����ϰ� �޸� �ּҸ� ���� �����ϴ�

	int		iNumber = 100;
	void*	pVoid = &iNumber;

	cout << "iNumber Address: " << pVoid << endl;
	pVoid = &tStudent;

	cout << "tStudent Address: " << pVoid << endl;
	
	cout << *pVoid << endl; // �Ұ���
	cout << *((int*)pVoid) << endl; // ����� ����ȯ�� �̿��ؼ� ǥ���� ����
}