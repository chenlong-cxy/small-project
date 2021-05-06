#include "Maze.h"
#include "stack.h"

void Path(int Maze[MAXROW][MAXCOL])
{
	//设置8种走向的偏移量
	Offsets Move[8] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };
	int Mark[MAXROW][MAXCOL] = { 0 };//标记是否走过
	Stack st;
	StackInit(&st);
	Mark[EXITROW][EXITCOL] = 1;//出口标记为走过
	MazePosition* p;
	p->row = EXITROW;
	p->col = EXITCOL;
	p->dir = 0;
	StackPush(&st, p);//出口位置入栈
	bool Found = false;
	while (!StackEmpty(&st) && !Found)
	{
		//取栈顶数据
		p = StackTop(&st);
		StackPop(&st);
		while (!Found&&p->dir < 8)
		{
			int nextRow = p->row + Move[p->dir].vert;
			int nextCol = p->col + Move[p->dir].horiz;
			if (nextRow == 1 && nextCol == 1)//找到入口
				Found = true;
			else
			{
				if (!Maze[nextRow][nextCol] && !Mark[nextRow][nextCol])//如果该路可以走，并且没有被标记过
				{
					Mark[nextRow][nextCol] = 1;//标记为走过
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