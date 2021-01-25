#include"game.h"
//初始化棋盘
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}
//打印棋盘
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("--------------扫雷游戏----------------\n");
	for (i = 0; i <= row; i++)
		printf("%d ", i);
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("--------------扫雷游戏----------------\n");
}
//布置雷
void SetMine(char mine[ROWS][COLS], int row, int col,int count)
{
	while (count)
	{
		int x = rand() % ROW + 1;
		int y = rand() % COL + 1;
		if (mine[x][y] == '0')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}
//计算该坐标周围8个坐标存在的总雷数
int GetMineCount(char mine[ROWS][COLS], int x, int y)
{
	int i = 0;
	int sum = 0;
	for (i = x - 1; i <= x + 1; i++)
	{
		int j = 0;
		for (j = y - 1; j <= y + 1; j++)
		{
			sum += mine[i][j];
		}
	}
	return sum - 9 * '0';
}
//判断周围雷的数量为0的坐标周围雷的存在情况，实现扫雷中的展开一片现象
void JudgeAround(char mine[ROWS][COLS],char show[ROWS][COLS], int x, int y)
{
	int i = 0;
	int j = 0;
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if (show[i][j] != ' '&&i!=0&&i!=ROWS-1&&j!=0&&j!=COLS-1)
			{
				int count = GetMineCount(mine, i, j);
				show[i][j] = count + '0';
				if (show[i][j] == '0')
				{
					show[i][j] = ' ';
					JudgeAround(mine, show, i, j);
				}
			}
		}
	}
}
//计算剩下未知坐标的数量，当其等于雷的总数时表示扫雷成功
int Remain(char show[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	int count = 0;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (show[i][j] == '*')
				count++;
		}
	}
	return count;
}
//排查雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int ret = 0;
	while (ret!=COUNT)
	{
		printf("请输入要排查的坐标:>");
		int x = 0;
		int y = 0;
		scanf("%d%d", &x, &y);
		//判断输入坐标合法性
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//判断该坐标处是不是雷
			if (mine[x][y] == '1')
			{
				printf("很遗憾，你被炸死了！\n");
				DisplayBoard(mine, ROW, COL);
				break;
			}
			else
			{
				//不是雷，统计该坐标周围雷的个数
				int count = GetMineCount(mine, x, y);
				show[x][y] = count + '0';//存放的是数字字符
				if (show[x][y] == '0')//如果该坐标周围雷的数量为0
				{
					show[x][y] = ' ';
					JudgeAround(mine, show, x, y);
				}
				system("cls");
				DisplayBoard(show, ROW, COL);
			}
		}
		else
		{
			printf("坐标非法，请重新输入！\n");
		}
		ret = Remain(show, ROW, COL);
	}
	if (ret==COUNT)
	{
		printf("恭喜你，排雷成功！\n");
		DisplayBoard(mine, ROW, COL);
	}
}
