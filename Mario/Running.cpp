#include "Core.h"

int main()
{
	if (!CCore::GetInst()->Init())
	{
		cout << "게임 초기화 실패!!" << endl;
		CCore::DestroyInst();
	}
}