#include <iostream>
#include <time.h> // �ð� ���� �ڵ�
using namespace std;

int main() {
	/*
		// ���� �߻�, ���� ���̺� �ۼ�?
		srand((unsigned int)time(0)); // srand�� �Ķ���ͷ� unsigned int
	
		for (int i = 0; i < 20; i++) {
			cout << rand() % 3 << endl; // 0,1,2
		}
		cout << endl; 
	
		for (int i = 0; i < 20; i++) {
			cout << rand() % 1000 / 100.f << endl; // 0.01~9.99
		}
	*/
	
	int iUpgrade;
	
	while (true) {
		cout << "Upgrade �⺻ ��ġ�� �Է��ϼ��� : ";
		cin >> iUpgrade;

		// ��ȭ Ȯ���� ������.
		float fPercent = rand() % 10000 / 100.0f; // 0.01 ~ 99.99

		// ��ȭȮ��: ���׷��̵尡
		// 0~3: 100�� ����, 4~6 40%, 7~9: 10%
		cout << "upgrade: " << iUpgrade << ", percent: " << fPercent << endl;

		if (iUpgrade <= 3)
			cout << "��ȭ ����!!" << endl;
		else if (iUpgrade <= 6) {
			if (fPercent < 40.f)
				cout << "��ȭ ����!!" << endl;
			else
				cout << "��ȭ ����!!" << endl;
		}
		else if (iUpgrade <= 9) {
			if (fPercent < 10.f)
				cout << "��ȭ ����!!" << endl;
			else
				cout << "��ȭ ����!!" << endl;
		}
	}
}