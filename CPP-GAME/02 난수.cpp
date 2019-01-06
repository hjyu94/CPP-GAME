#include <iostream>
#include <time.h> // 시간 관련 코드
using namespace std;

int main() {
	/*
		// 난수 발생, 난수 테이블 작성?
		srand((unsigned int)time(0)); // srand는 파라매터로 unsigned int
	
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
		cout << "Upgrade 기본 수치를 입력하세요 : ";
		cin >> iUpgrade;

		// 강화 확률을 구하자.
		float fPercent = rand() % 10000 / 100.0f; // 0.01 ~ 99.99

		// 강화확률: 업그레이드가
		// 0~3: 100퍼 성공, 4~6 40%, 7~9: 10%
		cout << "upgrade: " << iUpgrade << ", percent: " << fPercent << endl;

		if (iUpgrade <= 3)
			cout << "강화 성공!!" << endl;
		else if (iUpgrade <= 6) {
			if (fPercent < 40.f)
				cout << "강화 성공!!" << endl;
			else
				cout << "강화 실패!!" << endl;
		}
		else if (iUpgrade <= 9) {
			if (fPercent < 10.f)
				cout << "강화 성공!!" << endl;
			else
				cout << "강화 실패!!" << endl;
		}
	}
}