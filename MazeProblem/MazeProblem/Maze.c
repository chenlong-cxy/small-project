#include "Maze.h"
#include "stack.h"

void Path(int Maze[MAXROW][MAXCOL])
{
	//����8�������ƫ����
	Offsets Move[8] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };
	int Mark[MAXROW][MAXCOL] = { 0 };//����Ƿ��߹�
	Stack st;
	StackInit(&st);
	Mark[EXITROW][EXITCOL] = 1;//���ڱ��Ϊ�߹�
	MazePosition* p;
	p->row = EXITROW;
	p->col = EXITCOL;
	p->dir = 0;
	StackPush(&st, p);//����λ����ջ
	bool Found = false;
	while (!StackEmpty(&st) && !Found)
	{
		//ȡջ������
		p = StackTop(&st);
		StackPop(&st);
		while (!Found&&p->dir < 8)
		{
			int nextRow = p->row + Move[p->dir].vert;
			int nextCol = p->col + Move[p->dir].horiz;
			if (nextRow == 1 && nextCol == 1)//�ҵ����
				Found = true;
			else
			{
				if (!Maze[nextRow][nextCol] && !Mark[nextRow][nextCol])//�����·�����ߣ�����û�б���ǹ�
				{
					Mark[nextRow][nextCol] = 1;//���Ϊ�߹�
					p->dir++;
					StackPush(&st, p);

				}
				else
				{
					p->dir++;
				}
			}
		}

	}

	StackDestroy(&st);
}