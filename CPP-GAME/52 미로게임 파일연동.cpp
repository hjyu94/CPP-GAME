#include <iostream>
#include <conio.h>
#include <time.h> // rand()

using namespace std;

// 플레이어의 좌표를 나타내자
struct _tagPoint
{
	int x;
	int y;
};

typedef _tagPoint	POINT;
typedef _tagPoint*	PPOINT;

typedef struct _tagPlayer
{
	_tagPoint	tPos;
	bool		bWallPush;
	bool		bPushOnOff;
	bool		bTransparency;
	int			iBombPower;
} PLAYER, *PPLAYER;

// 0 : 벽
// 1 : 길
// 2 : 시작점
// 3 : 도착점
// 4 : 폭탄
// 5 : 파워 아이템
// 6 : 벽 밀기 아이템
// 7 : 투명

void SetMaze(char Maze[20][20],
	PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos)
{
	// MazeList.txt 파일을 읽어와서 미로 목록을 만든다.
	FILE*	pFile = NULL;

	fopen_s(&pFile, "MazeList.txt", "rt");
	
	char** pMazeList = NULL;

	if (pFile) // 목록이 있을 경우
	{
		char	cCount;
		fread(&cCount, 1, 1, pFile);	// 파일이 몇개 있는지 읽는다
		int iMazeCount = atoi(&cCount); // 문자를 숫자로 변환
		fread(&cCount, 1, 1, pFile);	// 개행까지 읽어서 없앤다.

		// 미로 개수만큼 할당한다.
		pMazeList = new char*[iMazeCount]; // char 포인터(string) 배열을 동적할당하자
		
		for (int i = 0; i < iMazeCount; ++i)
		{
			// \n 이 나올때까지 읽어야 한다.
			int iNameCount = 0;

			// 현재 미로의 파일 이름을 저장할 배열을 미리 넉넉하게 char 256개로 할당
			pMazeList[i] = new char[256];

			while (true)
			{
				fread(&cCount, 1, 1, pFile);
				if (cCount != '\n')
				{
					pMazeList[i][iNameCount] = cCount;
					++iNameCount;
				}
				else
					break; // \n 인 경우 while 빠져나감
			}

			// 파일 이름을 모두 읽었다면 문자열의 마지막에 null을 추가한다.
			pMazeList[i][iNameCount] = 0;
		}

		fclose(pFile);

		// 모두 읽어온 뒤 각 파일 중 하나를 선택하게 한다.
		for (int i = 0; i < iMazeCount; ++i)
		{
			cout << i + 1 << ". " << pMazeList[i] << endl;
		}

		cout << "미로를 선택하세요: ";
		int iSelect;
		cin >> iSelect;

		// 선택된 미로파일을 읽는다.
		fopen_s(&pFile, pMazeList[iSelect - 1], "rt");

		if (pFile)
		{
			// 미로의 세로줄 개수 만큼 반복하여 줄 별로 읽어온다
			for (int i = 0; i < 20; ++i)
			{
				fread(Maze[i], 1, 19, pFile);

				// 출발지 도착지 설정
				for (int j = 0; j < 19; ++j)
				{
					// 시작점일 경우
					if (Maze[i][j] == '2')
					{
						pStartPos->x = j;
						pStartPos->y = i;

						pPlayer->tPos = *pStartPos;
					}
					// 도착점일 경우
					else if (Maze[i][j] == '3')
					{
						pEndPos->x = j;
						pEndPos->y = i;
					}
				}

				// 개행 문자를 읽어온다.
				fread(&cCount, 1, 1, pFile);
			}
			fclose(pFile);
		}
	}

}

void Output(char Maze[20][20], PPLAYER pPlayer)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (pPlayer->tPos.x == j && pPlayer->tPos.y == i) cout << "☆"; // 플레이어 위치
			else if (Maze[i][j] == '0') cout << "■"; // 벽
			else if (Maze[i][j] == '1') cout << "  "; // 길
			else if (Maze[i][j] == '2') cout << "★"; // 시작점
			else if (Maze[i][j] == '3') cout << "◎"; // 도착점
			else if (Maze[i][j] == '4') cout << "♨"; // 폭탄
			else if (Maze[i][j] == '5') cout << "㈜"; // 파워 아이템
			else if (Maze[i][j] == '6') cout << "※"; // 벽 밀기
			else if (Maze[i][j] == '7') cout << "○"; // 투명
		}
		cout << endl;
	}

	cout << "폭탄 파워: " << pPlayer->iBombPower << endl; // MAX: 5
	cout << "벽 통과: " << (pPlayer->bTransparency ? "ON" : "OFF") << ", ";

	cout << "벽 밀기: ";
	if (pPlayer->bWallPush)
	{
		cout << "가능 / ";
		cout << (pPlayer->bPushOnOff ? "ON" : "OFF") << endl;
	}
	else cout << "불가능" << endl;
}

// 5 : 파워 아이템
// 6 : 벽 밀기 아이템
// 7 : 투명

bool AddItem(char cItemType, PPLAYER pPlayer)
{
	switch (cItemType)
	{
	case('5'):
		if (pPlayer->iBombPower < 5) // iBombPower_max = 5;
			pPlayer->iBombPower++;
		return true;

	case('6'):
		pPlayer->bWallPush = true;
		pPlayer->bPushOnOff = true;
		return true;

	case('7'):
		pPlayer->bTransparency = true;
		return true;

	default:
		return false;
	}
}

void MoveUp(char Maze[20][20], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y - 1 >= 0)
	{
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '4') // 가려는 곳에 폭탄이 있는 경우
		{
			cout << "폭탄을 통과할 수 없습니다." << endl;
			system("pause");
		}
		else if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0') // 가려는 곳이 벽인 경우
		{
			// 가려는 곳이 벽인데 벽 밀기가 가능한 경우 또, 위의 위 칸이 벽이 아니라면 밀자.
			if (pPlayer->bPushOnOff && pPlayer->tPos.y - 2 >= 0
				&& Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] != '0')
			{
				// 위의 위칸은 벽으로 만들어 주고
				Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
				// 바로 위칸은 길로 만들어 준 뒤
				Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
				// 플레이어를 한칸 위로 옮겨준다.
				--pPlayer->tPos.y;
			}

			// 가려는 곳이 벽인데 벽 밀기가 불가능 하지만 투명 아이템이 있는 경우
			// 이동시킨다: 투명 아이템을 이용해 벽 통과를 하려는 상황
			else if (pPlayer->bTransparency)
			{
				--pPlayer->tPos.y;

				// 아이템이 있다면 먹고 아이템이 놓인 위치를 길로 만들어준다.
				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
			}

			// 가려는 곳이 벽이고 투명, 밀기 아이템 모두 없는 경우
			else
			{
				cout << "벽을 뚫을 수 없습니다" << endl;
				system("pause");
			}
		}
		else // 이동시킨다: 폭탄도 아니고 벽도 아닌 경우
		{
			--pPlayer->tPos.y;

			// 아이템이 있다면 먹고 아이템이 놓인 위치를 길로 만들어준다.
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}
	}
	else
	{
		cout << "더 위로 갈 수 없습니다" << endl;
		system("pause");
	}
}

void MoveDown(char Maze[20][20], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '4')
		{
			cout << "폭탄을 통과할 수 없습니다." << endl;
			system("pause");
		}

		else if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '0') // 가려는 곳이 벽인 경우
		{
			// 가려는 곳이 벽인데 벽 밀기가 가능한 경우 또, 아래의 아래 칸이 벽이 아니라면 밀자.
			if (pPlayer->bPushOnOff && pPlayer->tPos.y + 2 <= 19
				&& Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] != '0')
			{
				// 아래의 아래칸은 벽으로 만들어 주고
				Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '0';
				// 바로 아래칸은 길로 만들어 준 뒤
				Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
				// 플레이어를 한칸 아래로 옮겨준다.
				++pPlayer->tPos.y;
			}

			// 가려는 곳이 벽인데 벽 밀기가 불가능 하지만 투명 아이템이 있는 경우
			// 이동시킨다: 투명 아이템을 이용해 벽 통과를 하려는 상황
			else if (pPlayer->bTransparency)
			{
				++pPlayer->tPos.y;

				// 아이템이 있다면 먹고 아이템이 놓인 위치를 길로 만들어준다.
				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
			}

			// 가려는 곳이 벽이고 투명, 밀기 아이템 모두 없는 경우
			else
			{
				cout << "벽을 뚫을 수 없습니다" << endl;
				system("pause");
			}
		}
		else // 이동시킨다: 폭탄도 아니고 벽도 아닌 경우
		{
			++pPlayer->tPos.y;

			// 아이템이 있다면 먹고 아이템이 놓인 위치를 길로 만들어준다.
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}
	}
	else
	{
		cout << "더 아래로 갈 수 없습니다" << endl;
		system("pause");
	}
}


void MoveLeft(char Maze[20][20], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 >= 0)
	{
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '4')
		{
			cout << "폭탄을 통과할 수 없습니다." << endl;
			system("pause");
		}

		else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0') // 가려는 곳이 벽인 경우
		{
			// 가려는 곳이 벽인데 벽 밀기가 가능한 경우 또, 왼쪽의 왼쪽 칸이 벽이 아니라면 밀자.
			if (pPlayer->bPushOnOff && pPlayer->tPos.y - 2 >= 0
				&& Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] != '0')
			{
				Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '0';
				Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
				--pPlayer->tPos.x;
			}

			// 가려는 곳이 벽인데 벽 밀기가 불가능 하지만 투명 아이템이 있는 경우
			// 이동시킨다: 투명 아이템을 이용해 벽 통과를 하려는 상황
			else if (pPlayer->bTransparency)
			{
				--pPlayer->tPos.x;

				// 아이템이 있다면 먹고 아이템이 놓인 위치를 길로 만들어준다.
				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
			}

			// 가려는 곳이 벽이고 투명, 밀기 아이템 모두 없는 경우
			else
			{
				cout << "벽을 뚫을 수 없습니다" << endl;
				system("pause");
			}
		}
		else // 이동시킨다: 폭탄도 아니고 벽도 아닌 경우
		{
			--pPlayer->tPos.x;

			// 아이템이 있다면 먹고 아이템이 놓인 위치를 길로 만들어준다.
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}

		/*
		else if ((!pPlayer->bTransparency) && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0')
		{
		cout << "벽을 뚫을 수 없습니다" << endl;
		system("pause");
		}
		else
		{
		--pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
		Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}*/
	}
	else
	{
		cout << "더 왼쪽으로 갈 수 없습니다" << endl;
		system("pause");
	}
}


void MoveRight(char Maze[20][20], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 19)
	{
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '4')
		{
			cout << "폭탄을 통과할 수 없습니다." << endl;
			system("pause");
		}
		else if ((!pPlayer->bTransparency) && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '0')
		{
			cout << "벽을 뚫을 수 없습니다" << endl;
			system("pause");
		}
		else
		{
			++pPlayer->tPos.x;

			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}
	}
	else
	{
		cout << "더 오른쪽으로 갈 수 없습니다" << endl;
		system("pause");
	}
}

void MovePlayer(char Maze[20][20], PPLAYER pPlayer, char cInput)
{
	switch (cInput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;

	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;

	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;

	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;

	}
}

void CreateBomb(char Maze[20][20], const PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount)
{
	if (*pBombCount >= 5) // 폭탄은 5개 이상 설치할 수 없다.
	{
		cout << "폭탄을 모두 설치했습니다" << endl;
		system("pause");
		return;
	}

	// 벽이 있는 위치에는 폭탄을 설치할 수 없다.
	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
	{
		cout << "이곳에는 폭탄을 설치할 수 없습니다" << endl;
		return;
	}

	// 같은 자리에 계속 폭탄을 설치할 수 없다.
	for (int i = 0; i < *pBombCount; ++i)
	{
		if ((pPlayer->tPos.x == pBombArr[i].x) &&
			(pPlayer->tPos.y == pBombArr[i].y))
			return;
	}

	pBombArr[(*pBombCount)++] = pPlayer->tPos;

	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

// 1 : 길
// 5 : 파워 아이템
// 6 : 벽 밀기 아이템
// 7 : 투명

char DropItem(bool bDrop)
{
	if (bDrop)
	{
		int iRand = rand() % 100;

		if (iRand < 70) return '7';
		else if (iRand < 80) return '6';
		else return '5';
	}
	else
		return '1';
}

void Fire(char Maze[20][20], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		for (int j = 1; j <= pPlayer->iBombPower; ++j)
		{
			if (pBombArr[i].y >= 1) // 위쪽이 벽이라면 터뜨린다.
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
					Maze[pBombArr[i].y - j][pBombArr[i].x] = DropItem(rand() % 100 < 20); // 20퍼의 확률로 아이템 드랍

																						  // 플레이어가 폭탄에 맞았을 때 시작점으로 보내자
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = 0; pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].y <= 18) // 아래쪽이 벽이라면 터뜨린다.
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
					Maze[pBombArr[i].y + j][pBombArr[i].x] = DropItem(rand() % 100 < 20); // 20퍼의 확률로 아이템 드랍

																						  // 플레이어가 폭탄에 맞았을 때 시작점으로 보내자
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0; pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x <= 17) // 오른쪽이 벽이라면 터뜨린다.
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
					Maze[pBombArr[i].y][pBombArr[i].x + j] = DropItem(rand() % 100 < 20); // 20퍼의 확률로 아이템 드랍

																						  // 플레이어가 폭탄에 맞았을 때 시작점으로 보내자
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0; pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x >= 1) // 왼쪽이 벽이라면 터뜨린다.
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
					Maze[pBombArr[i].y][pBombArr[i].x - j] = DropItem(rand() % 100 < 20); // 20퍼의 확률로 아이템 드랍

																						  // 플레이어가 폭탄에 맞았을 때 시작점으로 보내자
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0; pPlayer->tPos.y = 0;
				}
			}
		}

		// 원래 폭탄이 있던 좌표를 길로 만든다.
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';
	}
	*pBombCount = 0;

	cout << "폭탄이 터졌습니다" << endl;
	system("pause");
}

void main()
{
	srand((unsigned int)time(0)); // 아이템 드랍 확률을 위해 난수표 작성

								  // 20 x 20 미로
	char	strMaze[20][20];

	PLAYER tPlayer = {}; // 0으로 초기화
						 // POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT tBombPos[5];

	// 미로를 설정한다
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{

		system("cls");
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "도착했습니다" << endl;
			break;
		}

		cout << "t: 폭탄설치, u: 폭탄 터트리기, i: 벽밀기" << endl;
		cout << "작동키: w s a d, 종료:q" << endl;

		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q') break; // 종료 입력시 while문 빠져나감

		else if (cInput == 't' || cInput == 'T') // 폭탄 설치시
		{
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else if (cInput == 'u' || cInput == 'U') // 폭탄 터트리기시
		{
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else if (cInput == 'i' || cInput == 'I') // 벽밀기
		{
			if (tPlayer.bWallPush)
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff; // On <-> Off
		}

		else MovePlayer(strMaze, &tPlayer, cInput);

	}
}