#include "Stage.h"
#include "FileStream.h"

enum STAGE_BLOCK_TYPE
{
	// 0:벽 / 1 : 길 / 2 : 시작점 / 3 : 도착점 / 4 : 코인

	SBT_WALL = '0',
	SBT_ROAD = '1',
	SBT_START = '2',
	SBT_END = '3',
	SBT_COIN = '4',
};

CStage::CStage()
{
}

CStage::~CStage()
{
}

bool CStage::Init()
{
	return true;
}

bool CStage::Init(char * pFileName)
{
	CFileStream file; 
	// 지역변수라서 Init 함수가 끝날 때 CFileStream의 소멸자가 호출된다.
	// ~CfileStream() 에서 파일을 닫아주는 기능을 구현해 둔 상태이다.

	if (!file.Open(pFileName, "rt"))
		return false;

	for (int i = 0; i < 10; ++i)
	{
		int iSize = 0;
		file.ReadLine(m_cStage[i], iSize);

		/*for (int j = 0; j < 50; ++j)
		{
			cout << m_cStage[i][j];
		}
		cout << endl;*/
	}

	return true;
}

void CStage::Render()
{
	/* 
	맵은 스크롤 처리를 해야한다. 
	그렇기 때문에 현재 플레이어가 이동한 위치로부터 맵을 출력해주어야 한다.
	출력 크기는 세로 4칸 가로 10칸으로 해준다.
	지금은 플레이어가 처음에 있다 라고 가정하고 처음 4 x 10 출력을 해준다.

	0:벽 / 1:길 / 2:시작점 / 3:도착점 / 4:코인
	*/
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (m_cStage[i][j] == SBT_WALL) cout << "■";
			else if (m_cStage[i][j] == SBT_ROAD) cout << "  ";
			else if (m_cStage[i][j] == SBT_START) cout << "◑";
			else if (m_cStage[i][j] == SBT_END) cout << "◐";
			else if (m_cStage[i][j] == SBT_COIN) cout << "＠";
		}
		cout << endl;
	}
}
