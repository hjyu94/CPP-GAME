#include "Core.h"

int main()
{
	if (!CCore::GetInst()->Init())
	{
		cout << "���� �ʱ�ȭ ����!!" << endl;
		CCore::DestroyInst();
	}
}