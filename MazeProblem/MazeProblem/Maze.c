#include "Maze.h"
#include "stack.h"
//��ӡ·��
void Print(int Maze[MAXROW][MAXCOL],  Stack st)
{
	int i = 0, j = 0;
	printf("�Թ�����Ϊ:>\n");
	for (i = 0; i < MAXROW; i++)
	{
		for (j = 0; j < MAXCOL; j++)
		{
			printf("%d ", Maze[i][j]);
		}
		printf("\n");
	}
	printf("�߳��Թ�·��Ϊ:>\n");
	printf("(1,1)");
	while (!StackEmpty(&st))
	{
		MazePosition pos = StackTop(&st);
		StackPop(&st);
		printf("->(%d,%d)", pos.row, pos.col);
	}
	printf("\n");
}

void Path(int Maze[MAXROW][MAXCOL])
{
	//����8�������ƫ����
	Offsets Move[8] = { { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 } };
	int Mark[MAXROW][MAXCOL] = { 0 };//����Ƿ��߹�
	Mark[EXITROW][EXITCOL] = 1;//���ڱ��Ϊ�߹�
	Stack st;
	StackInit(&st);//��ʼ��ջ

	MazePosition pos;
	pos.row = EXITROW;
	pos.col = EXITCOL;
	pos.dir = 0;
	StackPush(&st, pos);//����λ����ջ
	bool Found = false;
	int Row, Col, Dir;
	while (!StackEmpty(&st) && !Found)
	{
		//ȡջ������
		pos = StackTop(&st);
		StackPop(&st);
		Row = pos.row, Col = pos.col, Dir = pos.dir;//�ֱ��¼ջ������
		while (!Found&&Dir < 8)//û���ҵ���ڣ����Ҹ�λ�õ�8������δ̽����
		{
			//��Ҫ̽������һ��λ�õ�����
			int nextRow = Row + Move[Dir].vert;
			int nextCol = Col + Move[Dir].horiz;
			if (nextRow == 1 && nextCol == 1)//�ҵ����
			{
				Found = true;
			}
			else//��Ҫ̽������һ��λ�ò������
			{
				if (!Maze[nextRow][nextCol] && !Mark[nextRow][nextCol])//�����·�����ߣ�����û�б���ǹ�
				{
					Mark[nextRow][nextCol] = 1;//���Ϊ�߹�
					//����ǰλ��ѹջ������Ҫ̽����λ��
					pos.row = Row;
					pos.col = Col;
					pos.dir = Dir + 1;
					StackPush(&st, pos);
					//��λ�õĻ�����Ϣ
					Row = nextRow;
					Col = nextCol;
					Dir = 0;
				}
				else//��Ҫ̽������һ��λ�ò����ߣ����Ѿ��߹�����̽����ǰλ�õ���һ������
				{
					Dir++;
				}
			}
		}		
	}
	if (Found)
	{
		//��������ڴ���ǰһ��λ����ջ
		pos.row = Row;
		pos.col = Col;
		pos.dir = 0;
		StackPush(&st, pos);
		Print(Maze, st);
	}
	else
	{
		printf("���Թ��޽�\n");
	}
	StackDestroy(&st);//�ͷ�ջ�ռ�
}

//void Path(int Maze[MAXROW][MAXCOL])
//{
//	//����8�������ƫ����
//	Offsets Move[8] = { { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 } };
//	int Mark[MAXROW][MAXCOL] = { 0 };//����Ƿ��߹�
//	Stack st;
//	StackInit(&st);
//	Mark[1][1] = 1;//���ڱ��Ϊ�߹�
//	MazePosition pos;
//	pos.row = 1;
//	pos.col = 1;
//	pos.dir = 0;
//	StackPush(&st, pos);//����λ����ջ
//	bool Found = false;
//	int Row, Col, Dir;
//	while (!StackEmpty(&st) && !Found)
//	{
//		//ȡջ������
//		pos = StackTop(&st);
//		StackPop(&st);
//		Row = pos.row, Col = pos.col, Dir = pos.dir;
//		while (!Found&&Dir < 8)
//		{
//			int nextRow = Row + Move[Dir].vert;
//			int nextCol = Col + Move[Dir].horiz;
//			if (nextRow == EXITROW && nextCol == EXITCOL)//�ҵ����
//			{
//				Found = true;
//			}
//			else
//			{
//				if (!Maze[nextRow][nextCol] && !Mark[nextRow][nextCol])//�����·�����ߣ�����û�б���ǹ�
//				{
//					Mark[nextRow][nextCol] = 1;//���Ϊ�߹�
//					pos.row = Row;
//					pos.col = Col;
//					pos.dir = Dir + 1;
//					StackPush(&st, pos);
//					Row = nextRow;
//					Col = nextCol;
//					Dir = 0;
//				}
//				else
//				{
//					Dir++;
//				}
//			}
//		}
//	}
//	if (Found)
//	{
//		printf("�ҵ�·������\n");
//		printf("�� ��\n");
//		printf("1 1 \n");
//		printf("%-2d%-2d\n", Row, Col);
//		while (!StackEmpty(&st))
//		{
//			pos = StackTop(&st);
//			StackPop(&st);
//			printf("%-2d%-2d\n", pos.row, pos.col);
//		}
//	}
//	else
//	{
//		printf("���Թ��޽�\n");
//	}
//
//	StackDestroy(&st);
//}

//void Print(int Maze[MAXROW][MAXCOL], int Mark[MAXROW][MAXCOL])
//{
//	int i = 0, j = 0;
//	printf("�Թ�����Ϊ:>\n");
//	for (i = 0; i < MAXROW; i++)
//	{
//		for (j = 0; j < MAXCOL; j++)
//		{
//			printf("%d ", Maze[i][j]);
//		}
//		printf("\n");
//	}
//	printf("�߳��Թ�·��Ϊ:>\n");
//	for (i = 0; i < MAXROW; i++)
//	{
//		for (j = 0; j < MAXCOL; j++)
//		{
//			if (Mark[i][j] == 1)
//			{
//				printf("%c ", '@');
//			}
//			else
//			{
//				printf("%d ", Maze[i][j]);
//			}
//		}
//		printf("\n");
//	}
//}

