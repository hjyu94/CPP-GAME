#pragma once

#include <iostream> // Ű �Է� ��� �̿�
#include <Windows.h>

using namespace std;

// ��ũ�δ� #define�� �̿��ؼ� ����� ������ִ� ��.
// ��ũ�θ� ����ϰ� �Ǹ� ����� �κп� ������ �ܰ迡�� ���� �ڵ带 �������ش�
// ��ũ���� ����: �극��ũ �����͸� �ɰ� ���� üũ�� �� ����.
#define SAFE_DELETE(p)	if(p)	{delete p; p=NULL;}

#define STAGE_MAX_COUNT 3