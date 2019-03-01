#include "MapManager.h"

#include <iostream>

CMapManager::CMapManager()
{
	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		m_pStage[i] = NULL;
	}
}

CMapManager::~CMapManager()
{
	// 스테이지 메모리 해제
	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		SAFE_DELETE(m_pStage[i]);
	}
}

CMapManager * CMapManager::GetInst()
{
	if (!m_pInst)
		m_pInst = new CMapManager;

	return m_pInst;
}

void CMapManager::DestoryInst()
{
	SAFE_DELETE(m_pInst);
}

bool CMapManager::Init()
{
	char* pStageFile[3] = {
		"Stage1.txt",
		"Stage2.txt",
		"Stage3.txt"
	};

	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		m_pStage[i] = new CStage;

		if (!m_pStage[i]->Init())
			return false;
	}

	return true;
}

void CMapManager::Render()
{
}
