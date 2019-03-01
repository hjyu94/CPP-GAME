#pragma once

#include "value.h"

class CStage
{
public:
	CStage();
	~CStage();

private:
	char	m_cStage[10][50];

public:
	// 그냥 초기화할 목적의 함수
	bool Init();

	// 파일에서 정보를 읽어와서 설정할 함수
	bool Init(char* pFileName);

	void Render();
};