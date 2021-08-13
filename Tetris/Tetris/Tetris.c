#include "Tetris.h"


extern max = 0; //记录最高历史得分
extern grade = 0; //记录本局游戏得分
//从文件读取最高分
void ReadGrade()
{
	FILE* pf = fopen("俄罗斯方块最高得分记录.txt", "r"); //以只读方式打开文件
	if (pf == NULL) //打开文件失败
	{
		pf = fopen("俄罗斯方块最高得分记录.txt", "w"); //以只写方式打开文件（文件不存在可以自动创建该文件）
		fwrite(&grade, sizeof(int), 1, pf); //将max写入文件（此时max为0），即将最高历史得分初始化为0
	}
	fseek(pf, 0, SEEK_SET); //使文件指针pf指向文件开头
	fread(&max, sizeof(int), 1, pf); //读取文件中的最高历史得分到max当中
	fclose(pf); //关闭文件
	pf = NULL; //文件指针及时置空
}
//将最高分写入文件
void WriteGrade()
{
	FILE* pf = fopen("俄罗斯方块最高得分记录.txt", "w"); //以只写方式打开文件
	if (pf == NULL) //打开文件失败
	{
		printf("保存最高得分记录失败\n");
		exit(0);
	}
	fwrite(&grade, sizeof(int), 1, pf); //将本局游戏得分写入文件当中（更新最高历史得分）
	fclose(pf); //关闭文件
	pf = NULL; //文件指针及时置空
}
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
	color(7); 
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
	//printf("Next Block：");
	printf("下一个方块：");

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
			//获取第form种形态
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp[i][j] = block[shape][form].space[i][j];
				}
			}
			//将第form种形态顺时针旋转，得到第form+1种形态
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

	int shape = rand() % 7, form = rand() % 4; //随机获取方块的形状和形态
	while (1)
	{
		int t = 0;
		int nextShape = rand() % 7, nextForm = rand() % 4; //随机获取下一个方块的形状和形态
		int x = COL / 2 - 2, y = 0; //方块初始下落位置的横纵坐标
		color(nextShape); //颜色设置为下一个方块的颜色
		DrawBlock(nextShape, nextForm, COL + 3, 3); //将下一个方块显示在右上角
		while (1)
		{
			color(shape); //颜色设置为当前正在下落的方块
			DrawBlock(shape, form, x, y); //将该方块显示在初始下落位置
			if (t == 0)
			{
				t = 15000;
			}
			while (--t)
			{
				if (kbhit() != 0) //若键盘被敲击，则退出循环
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
								while (JudeFunc());
							}
						}
					}
					break;
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
				case DOWN: //方向键：下
					if (IsLegal(shape, form, x, y + 1) == 1) //判断方块向下移动一位后是否合法
					{
						//方块下落后合法才进行以下操作
						DrawSpace(shape, form, x, y); //用空格覆盖当前方块所在位置
						y++; //纵坐标自增（下一次显示方块时就相当于下落了一格了）
					}
					break;
				case LEFT: //方向键：左
					if (IsLegal(shape, form, x - 1, y) == 1) //判断方块向左移动一位后是否合法
					{
						//方块左移后合法才进行以下操作
						DrawSpace(shape, form, x, y); //用空格覆盖当前方块所在位置
						x--; //横坐标自减（下一次显示方块时就相当于左移了一格了）
					}
					break;
				case RIGHT: //方向键：右
					if (IsLegal(shape, form, x + 1, y) == 1) //判断方块向右移动一位后是否合法
					{
						//方块右移后合法才进行以下操作
						DrawSpace(shape, form, x, y); //用空格覆盖当前方块所在位置
						x++; //横坐标自增（下一次显示方块时就相当于右移了一格了）
					}
					break;
				case SPACE: //空格键
					if (IsLegal(shape, (form + 1) % 4, x, y + 1) == 1) //判断方块旋转后是否合法
					{
						//方块旋转后合法才进行以下操作
						DrawSpace(shape, form, x, y); //用空格覆盖当前方块所在位置
						y++; //纵坐标自增（总不能原地旋转吧）
						form = (form + 1) % 4; //方块的形态自增（下一次显示方块时就相当于旋转了）
					}
					break;
				case ESC: //Esc键
					system("cls"); //清空屏幕
					color(7);
					CursorJump(COL, ROW / 2);
					printf("  游戏结束  ");
					CursorJump(COL, ROW / 2 + 1);
					printf("按任意键退出");
					system("pause>nul"); //暂停
					CursorJump(COL, ROW / 2 + 2);
					exit(0); //结束程序
				case 's':
				case 'S':  //暂停
					system("pause>nul"); //暂停（按任意键继续）
					break;
				case 'r':
				case 'R': //重新开始
					system("cls"); //清空屏幕
					main(); //重新执行主函数
				}
			}
		}
		shape = nextShape, form = nextForm; //获取下一个方块的信息
		DrawSpace(nextShape, nextForm, COL + 3, 3); //将右上角的方块信息用空格覆盖
	}
}
//颜色设置
void color(int c)
{
	switch (c)
	{
	case 0:
		c = 13; //“T”形方块设置为紫色
		break;
	case 1:
	case 2:
		c = 12; //“L”形和“J”形方块设置为红色
		break;
	case 3:
	case 4:
		c = 10; //“Z”形和“S”形方块设置为绿色
		break;
	case 5:
		c = 14; //“O”形方块设置为黄色
		break;
	case 6:
		c = 11; //“I”形方块设置为浅蓝色
		break;
	default:
		c = 7; //其他默认设置为白色
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置
	//注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}
//画出方块
void DrawBlock(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1) //如果该位置有方块
			{
				CursorJump(2 * (x + j), y + i); //光标跳转到指定位置
				printf("■"); //输出方块
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
			if (block[shape][form].space[i][j] == 1) //如果该位置有方块
			{
				CursorJump(2 * (x + j), y + i); //光标跳转到指定位置
				printf("  "); //打印空格覆盖（两个空格）
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
			//如果方块落下的位置本来就已经有方块了，则不合法
			if ((block[shape][form].space[i][j] == 1) && (face.data[y + i][x + j] == 1))
				return 0; //不合法
		}
	}
	return 1; //合法
}
//判断函数
int JudeFunc()
{
	//判断是否得分
	for (int i = ROW - 2; i > 4; i--)
	{
		int sum = 0; //记录第i行的方块个数
		for (int j = 1; j < COL - 1; j++)
		{
			sum += face.data[i][j]; //统计第i行的方块个数
		}
		if (sum == 0) //该行没有方块，无需再判断其上的层次（无需再继续判断是否得分）
			break; //跳出循环
		if (sum == COL - 2) //该行全是方块，可得分
		{
			grade += 10; //满一行加10分
			color(7); //颜色设置为白色
			CursorJump(2 * COL + 4, ROW - 3); //光标跳转到显示当前分数的位置
			printf("当前分数：%d", grade); //更新当前分数
			for (int j = 1; j < COL - 1; j++) //清除得分行的方块信息
			{
				face.data[i][j] = 0; //该位置得分后被清除，标记为无方块
				CursorJump(2 * j, i); //光标跳转到该位置
				printf("  "); //打印空格覆盖（两个空格）
			}
			//把被清除行上面的行整体向下挪一格
			for (int m = i; m >1; m--)
			{
				sum = 0; //记录第m-1行的方块个数
				for (int n = 1; n < COL - 1; n++)
				{
					sum += face.data[m - 1][n]; //统计第m-1行的方块个数
					face.data[m][n] = face.data[m - 1][n]; //将上一行方块的标识移到下一行
					face.color[m][n] = face.color[m - 1][n]; //将上一行方块的颜色编号移到下一行
					if (face.data[m][n] == 1) //上一行移下来的是方块，打印方块
					{
						CursorJump(2 * n, m); //光标跳转到该位置
						color(face.color[m][n]); //颜色设置为还方块的颜色
						printf("■"); //打印方块
					}
					else //上一行移下来的是空格，打印空格
					{
						CursorJump(2 * n, m); //光标跳转到该位置
						printf("  "); //打印空格（两个空格）
					}
				}
				if (sum == 0) //该行没有方块，无需再将上层的方块向下移动（该行无方块说明该行上方全是空格了）
					return 1; //返回1，表示还需调用判断函数进行判断（移动下来的可能含有满行）
			}
		}
	}
	//判断游戏是否结束
	for (int j = 1; j < COL - 1; j++)
	{
		if (face.data[1][j] == 1) //顶层有方块存在（以第1行为顶层，不是第0行）
		{
			Sleep(1000); //留给玩家反应时间
			system("cls"); //清空屏幕
			color(7); //颜色设置为白色
			CursorJump(2 * (COL / 3), ROW / 2 - 3);
			if (grade>max)
			{
				printf("恭喜你打破最高记录，最高记录更新为%d", grade);
				WriteGrade();
			}
			else if (grade == max)
			{
				printf("与最高记录持平，加油再创佳绩", grade);
			}
			else
			{
				printf("请继续加油，当前与最高记录相差%d", max - grade);
			}
			CursorJump(2 * (COL / 3), ROW / 2);
			printf("GAME OVER");
			while (1)
			{
				char ch;
				CursorJump(2 * (COL / 3), ROW / 2 + 3);
				printf("再来一局?(y/n):");
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
				{
					system("cls");
					main();
				}
				else if (ch == 'n' || ch == 'N')
				{
					CursorJump(2 * (COL / 3), ROW / 2 + 5);
					exit(0);
				}
				else
				{
					CursorJump(2 * (COL / 3), ROW / 2 + 4);
					printf("选择错误，请再次选择");
				}
			}
		}
	}
	return 0;
}

