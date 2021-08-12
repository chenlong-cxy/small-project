#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define ROW 29 //游戏区行数
#define COL 20 //游戏区列数

#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右

#define SPACE 32 //空格键
#define ESC 27 //Esc键

struct Face
{
	int data[ROW][COL + 10];
	int color[ROW][COL + 10];
}face;

struct Block
{
	int space[4][4];
}block[7][4];


//隐藏光标
void HideCursor();
//光标跳转
void CursorJump(int x, int y);
//初始化界面
void InitInterface();
//初始化方块信息
void InitBlockInfo();
//开始游戏
void StartGame();
//颜色更改
void color(int num);
//画出方块
void DrawBlock(int shape, int form, int x, int y);
//空格覆盖
void DrawSpace(int shape, int form, int x, int y);
//判断该方块落到(x, y)处是否合法
int IsLegal(int shape, int form, int x, int y);
//判断函数
int JudeFunc();