#pragma once

#include "value.h"
#include "Stage.h"

class CMapManager
{
private:
	CMapManager();
	~CMapManager();

private:
	static CMapManager* m_pInst;

public:
	CMapManager* GetInst();
	void DestoryInst();

private:
	CStage m_pStage[STAGE_MAX_COUNT];

public:
	bool Init();
	void Run();
	void Render();
};