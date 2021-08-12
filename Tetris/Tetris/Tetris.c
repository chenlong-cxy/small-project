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
				face.data[i][j] = 1;
				CursorJump(2 * j, i);
				printf("■");
			}
			else if (i == ROW - 1)
			{
				face.data[i][j] = 1;
				printf("■");
			}
			else
				face.data[i][j] = 0;
		}
	}
	for (int i = COL; i < COL + 10; i++)
	{
		face.data[8][i] = 1;
		CursorJump(2 * i, 8);
		printf("■");
	}

	CursorJump(2 * COL, 1);
	printf("Next Block：");

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
	printf("当前分数：%d", grade);
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
		block[6][0].space[i][1] = 1;

	int temp[4][4];
	for (int shape = 0; shape < 7; shape++) //7种形状
	{
		for (int form = 0; form < 3; form++) //4种形态（已经有了一种，这里每个还需增加3种）
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp[i][j] = block[shape][form].space[i][j]; //获取基本形状
				}
			}
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					block[shape][form + 1].space[i][j] = temp[3 - j][i];
				}
			}
		}
	}
}

//开始游戏
void StartGame()
{
	int x = COL / 2 - 2, y = 0;
	int t = 0;
	int form = 0, shape = rand() % 7;
	int nextShape = rand() % 7;
	color(nextShape);
	DrawBlock(nextShape, form, COL + 4, 3);
	while (1)
	{
		//打印正在降落的方块
		color(shape);
		DrawBlock(shape, form, x, y);
		if (t == 0)
		{
			t = 15000;
		}
		while (--t)
		{
			if (kbhit() != 0) //键盘被敲击，退出循环
				break;
		}
		if (t == 0) //键盘未被敲击
		{
			if (IsLegal(shape, form, x, y + 1) == 0) //方块再下落就不合法了（已经到达底部）
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (block[shape][form].space[i][j] == 1)
						{
							face.data[y + i][x + j] = 1;
							face.color[y + i][x + j] = shape;
							while(JudeFunc());
						}
					}
				}
				return;
			}
			else //未到底部
			{
				DrawSpace(shape, form, x, y); //清除当前方块状态，准备将方块整体向下打印一格
				y++;
			}
		}
		else //键盘被敲击
		{
			char ch = getch(); //读取keycode
			switch (ch)
			{
			case DOWN:
				if (IsLegal(shape, form, x, y + 1) == 1)
				{
					DrawSpace(shape, form, x, y);
					y++;
				}
				break;
			case LEFT:
				if (IsLegal(shape, form, x - 1, y) == 1)
				{
					DrawSpace(shape, form, x, y);
					x--;
				}
				break;
			case RIGHT:
				if (IsLegal(shape, form, x + 1, y) == 1)
				{
					DrawSpace(shape, form, x, y);
					x++;
				}
				break;
			case SPACE:
				if (IsLegal(shape, (form + 1) % 4, x, y + 1) == 1)
				{
					DrawSpace(shape, form, x, y);
					y++;
					form = (form + 1) % 4;
				}
				break;
			case ESC:
				system("cls");
				system("pause>nul");
				printf("---请按任意键退出---");
				exit(0);
			case 's':
			case 'S':
				system("pause>nul");
				break;
			case 'r':
			case 'R':
				system("cls");
				main();
			}
		}
	}
}
//颜色更改
void color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
}
//画出方块
void DrawBlock(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1)
			{
				CursorJump(2 * (x + j), y + i);
				printf("■");
			}
		}
	}
}
//空格覆盖
void DrawSpace(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1)
			{
				CursorJump(2 * (x + j), y + i);
				printf("  ");
			}
		}
	}
}
//判断该方块落到(x, y)处是否合法
int IsLegal(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((block[shape][form].space[i][j] == 1) && (face.data[y + i][x + j] == 1))
				return 0; //不合法
		}
	}
	return 1; //合法
}
//判断函数
int JudeFunc()
{
	for (int i = ROW - 2; i > 4; i--)
	{
		int sum = 0;
		for (int j = 1; j < COL - 1; j++)
		{
			sum += face.data[i][j];
		}
		if (sum == 0) //该行没有方块，无需再判断其上的层次
			break;
		if (sum == COL - 2) //该行全满，可得分
		{
			grade += 10;
			color(7);
			CursorJump(2 * COL + 4, ROW - 3);
			printf("当前分数：%d", grade);
			for (int j = 1; j < COL - 1; j++) //清除本行信息
			{
				face.data[i][j] = 0;
				CursorJump(2 * j, i);
				printf("  ");
			}
			//把该行上面的行整体向下挪一格
			for (int m = i; m >1; m--)
			{
				sum = 0;
				for (int n = 1; n < COL - 1; n++)
				{
					sum += face.data[m - 1][n];
					face.data[m][n] = face.data[m - 1][n];
					face.color[m][n] = face.data[m - 1][n];
					if (face.data[m][n] == 1)
					{
						CursorJump(2 * n, m);
						color(face.color[m][n]);
						printf("■");
					}
					else
					{
						CursorJump(2 * n, m);
						printf("  ");
					}
				}
				if (sum == 0)
					return 1;
			}
		}
	}
	for (int j = 1; j < COL - 1; j++)
	{
		if (face.data[0][j] == 1) //游戏结束
		{
			Sleep(1000);
			system("cls");
			color(7);
			if (grade>max)
			{
				printf("恭喜打破记录，记录更新为%d\n", grade);
			}
			else if (grade == max)
			{
				printf("与最高记录持平，为%d\n", grade);
			}
			else
			{
				printf("与最高记录相差%d，继续加油\n", max - grade);
			}

			char ch;
			printf("是否再来一盘？(y/n):");
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y')
			{
				system("cls");
				main();
			}
			else
			{
				exit(0);
			}
		}
	}
	return 0;
}