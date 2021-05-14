#include "Maze.h"
#include "stack.h"
//打印路径
void Print(int Maze[MAXROW][MAXCOL],  Stack st)
{
	int i = 0, j = 0;
	printf("迷宫布局为:>\n");
	for (i = 0; i < MAXROW; i++)
	{
		for (j = 0; j < MAXCOL; j++)
		{
			printf("%d ", Maze[i][j]);
		}
		printf("\n");
	}
	printf("走出迷宫路径为:>\n");
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
	//设置8种走向的偏移量
	Offsets Move[8] = { { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 } };
	int Mark[MAXROW][MAXCOL] = { 0 };//标记是否走过
	Mark[EXITROW][EXITCOL] = 1;//出口标记为走过
	Stack st;
	StackInit(&st);//初始化栈

	MazePosition pos;
	pos.row = EXITROW;
	pos.col = EXITCOL;
	pos.dir = 0;
	StackPush(&st, pos);//出口位置入栈
	bool Found = false;
	int Row, Col, Dir;
	while (!StackEmpty(&st) && !Found)
	{
		//取栈顶数据
		pos = StackTop(&st);
		StackPop(&st);
		Row = pos.row, Col = pos.col, Dir = pos.dir;//分别记录栈顶数据
		while (!Found&&Dir < 8)//没有找到入口，并且该位置的8个方向未探索完
		{
			//将要探索的下一个位置的坐标
			int nextRow = Row + Move[Dir].vert;
			int nextCol = Col + Move[Dir].horiz;
			if (nextRow == 1 && nextCol == 1)//找到入口
			{
				Found = true;
			}
			else//将要探索的下一个位置不是入口
			{
				if (!Maze[nextRow][nextCol] && !Mark[nextRow][nextCol])//如果该路可以走，并且没有被标记过
				{
					Mark[nextRow][nextCol] = 1;//标记为走过
					//将当前位置压栈，走向将要探索的位置
					pos.row = Row;
					pos.col = Col;
					pos.dir = Dir + 1;
					StackPush(&st, pos);
					//新位置的基本信息
					Row = nextRow;
					Col = nextCol;
					Dir = 0;
				}
				else//将要探索的下一个位置不可走，或已经走过，则探索当前位置的下一个方向
				{
					Dir++;
				}
			}
		}		
	}
	if (Found)
	{
		//将到达入口处的前一个位置入栈
		pos.row = Row;
		pos.col = Col;
		pos.dir = 0;
		StackPush(&st, pos);
		Print(Maze, st);
	}
	else
	{
		printf("该迷宫无解\n");
	}
	StackDestroy(&st);//释放栈空间
}

//void Path(int Maze[MAXROW][MAXCOL])
//{
//	//设置8种走向的偏移量
//	Offsets Move[8] = { { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 } };
//	int Mark[MAXROW][MAXCOL] = { 0 };//标记是否走过
//	Stack st;
//	StackInit(&st);
//	Mark[1][1] = 1;//出口标记为走过
//	MazePosition pos;
//	pos.row = 1;
//	pos.col = 1;
//	pos.dir = 0;
//	StackPush(&st, pos);//出口位置入栈
//	bool Found = false;
//	int Row, Col, Dir;
//	while (!StackEmpty(&st) && !Found)
//	{
//		//取栈顶数据
//		pos = StackTop(&st);
//		StackPop(&st);
//		Row = pos.row, Col = pos.col, Dir = pos.dir;
//		while (!Found&&Dir < 8)
//		{
//			int nextRow = Row + Move[Dir].vert;
//			int nextCol = Col + Move[Dir].horiz;
//			if (nextRow == EXITROW && nextCol == EXITCOL)//找到入口
//			{
//				Found = true;
//			}
//			else
//			{
//				if (!Maze[nextRow][nextCol] && !Mark[nextRow][nextCol])//如果该路可以走，并且没有被标记过
//				{
//					Mark[nextRow][nextCol] = 1;//标记为走过
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
//		printf("找到路径如下\n");
//		printf("行 列\n");
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
//		printf("该迷宫无解\n");
//	}
//
//	StackDestroy(&st);
//}

//void Print(int Maze[MAXROW][MAXCOL], int Mark[MAXROW][MAXCOL])
//{
//	int i = 0, j = 0;
//	printf("迷宫布局为:>\n");
//	for (i = 0; i < MAXROW; i++)
//	{
//		for (j = 0; j < MAXCOL; j++)
//		{
//			printf("%d ", Maze[i][j]);
//		}
//		printf("\n");
//	}
//	printf("走出迷宫路径为:>\n");
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

