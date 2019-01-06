// 이진수 단위의 연산으로 컴퓨터가 편하게 느껴
// 속도가 빠르다.

#include <iostream>

using namespace std;

int main() {
	// 상수: 선언과 동시에 값을 지정
	// 0x: 16진수 표현법
	const int iAttack = 0x00000001; // 1
	const int iArmor = 0x00000002; // 10
	const int iHP = 0x00000004; // 100
	const int iMP = 0x00000008; /// 1000
	const int iCritical = 0x00000010; // 10000

	// 00001 | 00100 | 10000 = 10101 
	int iBuf = iAttack | iHP | iCritical;

	// 0이면 false
	// 0만 아니면 true

	// 해당 버프가 켜져있는지 아닌지 확인하는 법

	// 10101 & 00001 = 00001
	cout << "Attack : " << (iBuf & iAttack) << endl;
	// 10101 & 00010 = 00000
	cout << "Armor : " << (iBuf & iArmor) << endl;
	cout << "HP : " << (iBuf & iHP) << endl;
	cout << "MP : " << (iBuf & iMP) << endl;
	cout << "Critical : " << (iBuf & iCritical) << endl;


	// XOR을 이용하면 스위치로 사용 가능
	iBuf ^= iHP;
	cout << "HP : " << (iBuf & iHP) << endl;

	iBuf ^= iHP;
	cout << "HP : " << (iBuf & iHP) << endl;
	
	if ((iBuf & iArmor) != 0) {
		cout << "Armor 버프가 있습니다" << endl;
	}
	else
		cout << "Armor 버프가 없습니다" << endl;

	
	cout << endl;
	
	
	/*
		쉬프트 연산자 : <<. >> 값 대 값을 연산
		
		20 << 1 = 0b10100 << 1 = 0b101000 = 40
		20 << 2 = 0b10100 << 2 = 0b1010000 = 80
		20 << 3 = 0b10100 << 3 = 0b10100000 = 160
		2배씩 곱함

		20 >> 1 = 0b10100 >> 1 = 0b1010 = 10
		20 >> 2 = 0b101 = 5
		20 >> 3 = 0b10 = 2
		2배씩 나눔. 나머지는 버림
	*/

	// 쉬프트 연산자로 메모리를 아껴쓸 수도 있다.
	int iHigh = 187;
	int iLow = 13560;
	
	int iNumber = iHigh;
	
	// 상위 16비트로 167를 표현
	iNumber <<= 16;

	// 하위 16비트로 13560을 표현
	iNumber |= iLow;

	// 출력시에
	cout << "High: " << (iNumber >> 16) << endl;
	cout << "Low: " << (iNumber & 0x0000ffff) << endl;

	
}