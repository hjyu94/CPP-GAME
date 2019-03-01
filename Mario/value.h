#pragma once

#include <iostream> // 키 입력 기능 이용
#include <Windows.h>

using namespace std;

// 매크로는 #define을 이용해서 기능을 만들어주는 것.
// 매크로를 사용하게 되면 사용한 부분에 컴파일 단계에서 뒤의 코드를 복사해준다
// 매크로의 단점: 브레이크 포인터를 걸고 값을 체크할 수 없다.
#define SAFE_DELETE(p)	if(p)	{delete p; p=NULL;}

#define STAGE_MAX_COUNT 3