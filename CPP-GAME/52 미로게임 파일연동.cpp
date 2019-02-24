#include <iostream>
#include <conio.h>
#include <time.h> // rand()

using namespace std;

// �÷��̾��� ��ǥ�� ��Ÿ����
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

// 0 : ��
// 1 : ��
// 2 : ������
// 3 : ������
// 4 : ��ź
// 5 : �Ŀ� ������
// 6 : �� �б� ������
// 7 : ����

void SetMaze(char Maze[20][20],
	PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos)
{
	// MazeList.txt ������ �о�ͼ� �̷� ����� �����.
	FILE*	pFile = NULL;

	fopen_s(&pFile, "MazeList.txt", "rt");
	
	char** pMazeList = NULL;

	if (pFile) // ����� ���� ���
	{
		char	cCount;
		fread(&cCount, 1, 1, pFile);	// ������ � �ִ��� �д´�
		int iMazeCount = atoi(&cCount); // ���ڸ� ���ڷ� ��ȯ
		fread(&cCount, 1, 1, pFile);	// ������� �о ���ش�.

		// �̷� ������ŭ �Ҵ��Ѵ�.
		pMazeList = new char*[iMazeCount]; // char ������(string) �迭�� �����Ҵ�����
		
		for (int i = 0; i < iMazeCount; ++i)
		{
			// \n �� ���ö����� �о�� �Ѵ�.
			int iNameCount = 0;

			// ���� �̷��� ���� �̸��� ������ �迭�� �̸� �˳��ϰ� char 256���� �Ҵ�
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
					break; // \n �� ��� while ��������
			}

			// ���� �̸��� ��� �о��ٸ� ���ڿ��� �������� null�� �߰��Ѵ�.
			pMazeList[i][iNameCount] = 0;
		}

		fclose(pFile);

		// ��� �о�� �� �� ���� �� �ϳ��� �����ϰ� �Ѵ�.
		for (int i = 0; i < iMazeCount; ++i)
		{
			cout << i + 1 << ". " << pMazeList[i] << endl;
		}

		cout << "�̷θ� �����ϼ���: ";
		int iSelect;
		cin >> iSelect;

		// ���õ� �̷������� �д´�.
		fopen_s(&pFile, pMazeList[iSelect - 1], "rt");

		if (pFile)
		{
			// �̷��� ������ ���� ��ŭ �ݺ��Ͽ� �� ���� �о�´�
			for (int i = 0; i < 20; ++i)
			{
				fread(Maze[i], 1, 19, pFile);

				// ����� ������ ����
				for (int j = 0; j < 19; ++j)
				{
					// �������� ���
					if (Maze[i][j] == '2')
					{
						pStartPos->x = j;
						pStartPos->y = i;

						pPlayer->tPos = *pStartPos;
					}
					// �������� ���
					else if (Maze[i][j] == '3')
					{
						pEndPos->x = j;
						pEndPos->y = i;
					}
				}

				// ���� ���ڸ� �о�´�.
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
			if (pPlayer->tPos.x == j && pPlayer->tPos.y == i) cout << "��"; // �÷��̾� ��ġ
			else if (Maze[i][j] == '0') cout << "��"; // ��
			else if (Maze[i][j] == '1') cout << "  "; // ��
			else if (Maze[i][j] == '2') cout << "��"; // ������
			else if (Maze[i][j] == '3') cout << "��"; // ������
			else if (Maze[i][j] == '4') cout << "��"; // ��ź
			else if (Maze[i][j] == '5') cout << "��"; // �Ŀ� ������
			else if (Maze[i][j] == '6') cout << "��"; // �� �б�
			else if (Maze[i][j] == '7') cout << "��"; // ����
		}
		cout << endl;
	}

	cout << "��ź �Ŀ�: " << pPlayer->iBombPower << endl; // MAX: 5
	cout << "�� ���: " << (pPlayer->bTransparency ? "ON" : "OFF") << ", ";

	cout << "�� �б�: ";
	if (pPlayer->bWallPush)
	{
		cout << "���� / ";
		cout << (pPlayer->bPushOnOff ? "ON" : "OFF") << endl;
	}
	else cout << "�Ұ���" << endl;
}

// 5 : �Ŀ� ������
// 6 : �� �б� ������
// 7 : ����

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
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '4') // ������ ���� ��ź�� �ִ� ���
		{
			cout << "��ź�� ����� �� �����ϴ�." << endl;
			system("pause");
		}
		else if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0') // ������ ���� ���� ���
		{
			// ������ ���� ���ε� �� �бⰡ ������ ��� ��, ���� �� ĭ�� ���� �ƴ϶�� ����.
			if (pPlayer->bPushOnOff && pPlayer->tPos.y - 2 >= 0
				&& Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] != '0')
			{
				// ���� ��ĭ�� ������ ����� �ְ�
				Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
				// �ٷ� ��ĭ�� ��� ����� �� ��
				Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
				// �÷��̾ ��ĭ ���� �Ű��ش�.
				--pPlayer->tPos.y;
			}

			// ������ ���� ���ε� �� �бⰡ �Ұ��� ������ ���� �������� �ִ� ���
			// �̵���Ų��: ���� �������� �̿��� �� ����� �Ϸ��� ��Ȳ
			else if (pPlayer->bTransparency)
			{
				--pPlayer->tPos.y;

				// �������� �ִٸ� �԰� �������� ���� ��ġ�� ��� ������ش�.
				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
			}

			// ������ ���� ���̰� ����, �б� ������ ��� ���� ���
			else
			{
				cout << "���� ���� �� �����ϴ�" << endl;
				system("pause");
			}
		}
		else // �̵���Ų��: ��ź�� �ƴϰ� ���� �ƴ� ���
		{
			--pPlayer->tPos.y;

			// �������� �ִٸ� �԰� �������� ���� ��ġ�� ��� ������ش�.
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}
	}
	else
	{
		cout << "�� ���� �� �� �����ϴ�" << endl;
		system("pause");
	}
}

void MoveDown(char Maze[20][20], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '4')
		{
			cout << "��ź�� ����� �� �����ϴ�." << endl;
			system("pause");
		}

		else if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '0') // ������ ���� ���� ���
		{
			// ������ ���� ���ε� �� �бⰡ ������ ��� ��, �Ʒ��� �Ʒ� ĭ�� ���� �ƴ϶�� ����.
			if (pPlayer->bPushOnOff && pPlayer->tPos.y + 2 <= 19
				&& Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] != '0')
			{
				// �Ʒ��� �Ʒ�ĭ�� ������ ����� �ְ�
				Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '0';
				// �ٷ� �Ʒ�ĭ�� ��� ����� �� ��
				Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
				// �÷��̾ ��ĭ �Ʒ��� �Ű��ش�.
				++pPlayer->tPos.y;
			}

			// ������ ���� ���ε� �� �бⰡ �Ұ��� ������ ���� �������� �ִ� ���
			// �̵���Ų��: ���� �������� �̿��� �� ����� �Ϸ��� ��Ȳ
			else if (pPlayer->bTransparency)
			{
				++pPlayer->tPos.y;

				// �������� �ִٸ� �԰� �������� ���� ��ġ�� ��� ������ش�.
				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
			}

			// ������ ���� ���̰� ����, �б� ������ ��� ���� ���
			else
			{
				cout << "���� ���� �� �����ϴ�" << endl;
				system("pause");
			}
		}
		else // �̵���Ų��: ��ź�� �ƴϰ� ���� �ƴ� ���
		{
			++pPlayer->tPos.y;

			// �������� �ִٸ� �԰� �������� ���� ��ġ�� ��� ������ش�.
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}
	}
	else
	{
		cout << "�� �Ʒ��� �� �� �����ϴ�" << endl;
		system("pause");
	}
}


void MoveLeft(char Maze[20][20], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 >= 0)
	{
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '4')
		{
			cout << "��ź�� ����� �� �����ϴ�." << endl;
			system("pause");
		}

		else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0') // ������ ���� ���� ���
		{
			// ������ ���� ���ε� �� �бⰡ ������ ��� ��, ������ ���� ĭ�� ���� �ƴ϶�� ����.
			if (pPlayer->bPushOnOff && pPlayer->tPos.y - 2 >= 0
				&& Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] != '0')
			{
				Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '0';
				Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
				--pPlayer->tPos.x;
			}

			// ������ ���� ���ε� �� �бⰡ �Ұ��� ������ ���� �������� �ִ� ���
			// �̵���Ų��: ���� �������� �̿��� �� ����� �Ϸ��� ��Ȳ
			else if (pPlayer->bTransparency)
			{
				--pPlayer->tPos.x;

				// �������� �ִٸ� �԰� �������� ���� ��ġ�� ��� ������ش�.
				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
			}

			// ������ ���� ���̰� ����, �б� ������ ��� ���� ���
			else
			{
				cout << "���� ���� �� �����ϴ�" << endl;
				system("pause");
			}
		}
		else // �̵���Ų��: ��ź�� �ƴϰ� ���� �ƴ� ���
		{
			--pPlayer->tPos.x;

			// �������� �ִٸ� �԰� �������� ���� ��ġ�� ��� ������ش�.
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}

		/*
		else if ((!pPlayer->bTransparency) && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0')
		{
		cout << "���� ���� �� �����ϴ�" << endl;
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
		cout << "�� �������� �� �� �����ϴ�" << endl;
		system("pause");
	}
}


void MoveRight(char Maze[20][20], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 19)
	{
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '4')
		{
			cout << "��ź�� ����� �� �����ϴ�." << endl;
			system("pause");
		}
		else if ((!pPlayer->bTransparency) && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '0')
		{
			cout << "���� ���� �� �����ϴ�" << endl;
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
		cout << "�� ���������� �� �� �����ϴ�" << endl;
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
	if (*pBombCount >= 5) // ��ź�� 5�� �̻� ��ġ�� �� ����.
	{
		cout << "��ź�� ��� ��ġ�߽��ϴ�" << endl;
		system("pause");
		return;
	}

	// ���� �ִ� ��ġ���� ��ź�� ��ġ�� �� ����.
	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
	{
		cout << "�̰����� ��ź�� ��ġ�� �� �����ϴ�" << endl;
		return;
	}

	// ���� �ڸ��� ��� ��ź�� ��ġ�� �� ����.
	for (int i = 0; i < *pBombCount; ++i)
	{
		if ((pPlayer->tPos.x == pBombArr[i].x) &&
			(pPlayer->tPos.y == pBombArr[i].y))
			return;
	}

	pBombArr[(*pBombCount)++] = pPlayer->tPos;

	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

// 1 : ��
// 5 : �Ŀ� ������
// 6 : �� �б� ������
// 7 : ����

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
			if (pBombArr[i].y >= 1) // ������ ���̶�� �Ͷ߸���.
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
					Maze[pBombArr[i].y - j][pBombArr[i].x] = DropItem(rand() % 100 < 20); // 20���� Ȯ���� ������ ���

																						  // �÷��̾ ��ź�� �¾��� �� ���������� ������
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = 0; pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].y <= 18) // �Ʒ����� ���̶�� �Ͷ߸���.
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
					Maze[pBombArr[i].y + j][pBombArr[i].x] = DropItem(rand() % 100 < 20); // 20���� Ȯ���� ������ ���

																						  // �÷��̾ ��ź�� �¾��� �� ���������� ������
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0; pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x <= 17) // �������� ���̶�� �Ͷ߸���.
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
					Maze[pBombArr[i].y][pBombArr[i].x + j] = DropItem(rand() % 100 < 20); // 20���� Ȯ���� ������ ���

																						  // �÷��̾ ��ź�� �¾��� �� ���������� ������
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0; pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x >= 1) // ������ ���̶�� �Ͷ߸���.
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
					Maze[pBombArr[i].y][pBombArr[i].x - j] = DropItem(rand() % 100 < 20); // 20���� Ȯ���� ������ ���

																						  // �÷��̾ ��ź�� �¾��� �� ���������� ������
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0; pPlayer->tPos.y = 0;
				}
			}
		}

		// ���� ��ź�� �ִ� ��ǥ�� ��� �����.
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';
	}
	*pBombCount = 0;

	cout << "��ź�� �������ϴ�" << endl;
	system("pause");
}

void main()
{
	srand((unsigned int)time(0)); // ������ ��� Ȯ���� ���� ����ǥ �ۼ�

								  // 20 x 20 �̷�
	char	strMaze[20][20];

	PLAYER tPlayer = {}; // 0���� �ʱ�ȭ
						 // POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT tBombPos[5];

	// �̷θ� �����Ѵ�
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{

		system("cls");
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "�����߽��ϴ�" << endl;
			break;
		}

		cout << "t: ��ź��ġ, u: ��ź ��Ʈ����, i: ���б�" << endl;
		cout << "�۵�Ű: w s a d, ����:q" << endl;

		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q') break; // ���� �Է½� while�� ��������

		else if (cInput == 't' || cInput == 'T') // ��ź ��ġ��
		{
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else if (cInput == 'u' || cInput == 'U') // ��ź ��Ʈ�����
		{
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else if (cInput == 'i' || cInput == 'I') // ���б�
		{
			if (tPlayer.bWallPush)
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff; // On <-> Off
		}

		else MovePlayer(strMaze, &tPlayer, cInput);

	}
}