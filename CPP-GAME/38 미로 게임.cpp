#include <iostream>
#include <conio.h>

using namespace std;

// �÷��̾��� ��ǥ�� ��Ÿ����
struct _tagPoint
{
	int x;
	int y;
};

typedef _tagPoint	POINT;
typedef _tagPoint*	pPOINT;


// (0~3) 0��, 1��, 2������, 3������
void setMaze(char Maze[20][20], 
	pPOINT pPlayerPos, pPOINT pStartPos, pPOINT pEndPos)
{
	/*
		Maze =
		{
			{'2','1','1', ...}
		};
		// �ʹ� ���� �ɸ�
	*/
	
	pStartPos->x = 0;
	pStartPos->y = 0;

	strcpy_s(Maze[0],  "2110000000000000000");
	strcpy_s(Maze[1],  "0011111000000000000");
	strcpy_s(Maze[2],  "0010001111111110000");
	strcpy_s(Maze[3],  "0110001000000010000");
	strcpy_s(Maze[4],  "0100001110011110000");
	strcpy_s(Maze[5],  "0100000001110000000");
	strcpy_s(Maze[6],  "0111000001000000000");
	strcpy_s(Maze[7],  "0001000001111110000");
	strcpy_s(Maze[8],  "0000000000000010000");
	strcpy_s(Maze[9],  "0000000000000010000");
	strcpy_s(Maze[10], "0000000000000010000");
	strcpy_s(Maze[11], "0000000000000010000");
	strcpy_s(Maze[12], "0000000000000010000");
	strcpy_s(Maze[13], "0000000000000010000");
	strcpy_s(Maze[14], "0000000000000010000");
	strcpy_s(Maze[15], "0000000000000010000");
	strcpy_s(Maze[16], "0000000000000010000");
	strcpy_s(Maze[17], "0000000000000010000");
	strcpy_s(Maze[18], "0000000000000010000");
	strcpy_s(Maze[19], "0000000000000011113");
}

void Output(char Maze[20][20])
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Maze[i][j] == '0') cout << "��";
			else if (Maze[i][j] == '1') cout << "  ";
			else if (Maze[i][j] == '2') cout << "��";
			else if (Maze[i][j] == '3') cout << "��";
		}
		cout << endl;
	}
}

void main()
{
	// 20 x 20 �̷�
	char	strMaze[20][20];
	
	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	// �̷θ� �����Ѵ�
	setMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		
		Output(strMaze);
		cout << "�۵�Ű: wsad, ����:q" << endl;
		
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q') break; // while�� ��������

		
	}
}