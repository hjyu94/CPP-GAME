// ������ ������ �������� ��ǻ�Ͱ� ���ϰ� ����
// �ӵ��� ������.

#include <iostream>

using namespace std;

int main() {
	// ���: ����� ���ÿ� ���� ����
	// 0x: 16���� ǥ����
	const int iAttack = 0x00000001; // 1
	const int iArmor = 0x00000002; // 10
	const int iHP = 0x00000004; // 100
	const int iMP = 0x00000008; /// 1000
	const int iCritical = 0x00000010; // 10000

	// 00001 | 00100 | 10000 = 10101 
	int iBuf = iAttack | iHP | iCritical;

	// 0�̸� false
	// 0�� �ƴϸ� true

	// �ش� ������ �����ִ��� �ƴ��� Ȯ���ϴ� ��

	// 10101 & 00001 = 00001
	cout << "Attack : " << (iBuf & iAttack) << endl;
	// 10101 & 00010 = 00000
	cout << "Armor : " << (iBuf & iArmor) << endl;
	cout << "HP : " << (iBuf & iHP) << endl;
	cout << "MP : " << (iBuf & iMP) << endl;
	cout << "Critical : " << (iBuf & iCritical) << endl;


	// XOR�� �̿��ϸ� ����ġ�� ��� ����
	iBuf ^= iHP;
	cout << "HP : " << (iBuf & iHP) << endl;

	iBuf ^= iHP;
	cout << "HP : " << (iBuf & iHP) << endl;
	
	if ((iBuf & iArmor) != 0) {
		cout << "Armor ������ �ֽ��ϴ�" << endl;
	}
	else
		cout << "Armor ������ �����ϴ�" << endl;

	
	cout << endl;
	
	
	/*
		����Ʈ ������ : <<. >> �� �� ���� ����
		
		20 << 1 = 0b10100 << 1 = 0b101000 = 40
		20 << 2 = 0b10100 << 2 = 0b1010000 = 80
		20 << 3 = 0b10100 << 3 = 0b10100000 = 160
		2�辿 ����

		20 >> 1 = 0b10100 >> 1 = 0b1010 = 10
		20 >> 2 = 0b101 = 5
		20 >> 3 = 0b10 = 2
		2�辿 ����. �������� ����
	*/

	// ����Ʈ �����ڷ� �޸𸮸� �Ʋ��� ���� �ִ�.
	int iHigh = 187;
	int iLow = 13560;
	
	int iNumber = iHigh;
	
	// ���� 16��Ʈ�� 167�� ǥ��
	iNumber <<= 16;

	// ���� 16��Ʈ�� 13560�� ǥ��
	iNumber |= iLow;

	// ��½ÿ�
	cout << "High: " << (iNumber >> 16) << endl;
	cout << "Low: " << (iNumber & 0x0000ffff) << endl;

	
}