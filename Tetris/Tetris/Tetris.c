#include "Tetris.h"


int max = 100;
int grade = 100;
//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.dwSize = 1;  //如果没赋值的话，隐藏光标无效
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

//光标跳转
void CursorJump(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//初始化界面
void InitInterface()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL + 10; j++)
		{
			if (j == 0 || j == COL - 1 || j == COL + 9)
			{
				CursorJump(2 * j, i);
				printf("■");
			}
			else if (i == ROW - 1)
			{
				printf("■");
			}

		}
	}
	CursorJump(2 * COL + 4, ROW - 19);
	printf("左移：←");

	CursorJump(2 * COL + 4, ROW - 17);
	printf("右移：→");

	CursorJump(2 * COL + 4, ROW - 15);
	printf("加速：↓");

	CursorJump(2 * COL + 4, ROW - 13);
	printf("旋转：空格");

	CursorJump(2 * COL + 4, ROW - 11);
	printf("暂停: S");

	CursorJump(2 * COL + 4, ROW - 9);
	printf("退出: Esc");

	CursorJump(2 * COL + 4, ROW - 7);
	printf("重新开始:R");

	CursorJump(2 * COL + 4, ROW - 5);
	printf("最高纪录:%d", max);

	CursorJump(2 * COL + 4, ROW - 3);
	printf("分数：%d", grade);
}

//初始化方块信息
void InitBlockInfo()
{
	//“T”形
	for (int i = 0; i <= 2; i++)
		block[0][0].space[1][i] = 1;
	block[0][0].space[2][1] = 1;

	//“L”形
	for (int i = 1; i <= 3; i++)
		block[1][0].space[i][1] = 1;
	block[1][0].space[3][2] = 1;

	//“J”形
	for (int i = 1; i <= 3; i++)
		block[2][0].space[i][2] = 1;
	block[2][0].space[3][1] = 1;

	for (int i = 0; i <= 1; i++)
	{
		//“Z”形
		block[3][0].space[1][i] = 1;
		block[3][0].space[2][i + 1] = 1;
		//“S”形
		block[4][0].space[1][i + 1] = 1;
		block[4][0].space[2][i] = 1;
		//“O”形
		block[5][0].space[1][i + 1] = 1;
		block[5][0].space[2][i + 1] = 1;
	}

	//“I”形
	for (int i = 0; i <= 3;i++)
		block[6][0].space[i][2] = 1;

	int temp[4][4];
	for (int shape = 0; shape < 7; shape++) //7种形状
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp[i][j] = block[shape][0].space[i][j]; //获取基本形状
			}
		}
		for (int form = 0; form < 3; form++) //4种形态（已经有了一种，这里每个还需增加3种）
		{
			for (int m = 0; m < 4; m++)
			{
				for (int n = 0; n < 4; n++)
				{
					block[shape][form].space[m][n] = temp[3 - n][m];
				}
			}
		}
	}
}