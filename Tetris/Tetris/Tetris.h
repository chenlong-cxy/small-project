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
	int data[ROW][COL + 10]; //用于标记指定位置是否有方块（1为有，0为无）
	int color[ROW][COL + 10]; //用于记录指定位置的方块颜色编码
}face;

struct Block
{
	int space[4][4];
}block[7][4]; //用于存储7种基本形状方块的各自的4种形态的信息，共28

//从文件读取最高分
void ReadGrade();
//将最高分写入文件
void WriteGrade();
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
//颜色设置
void color(int num);
//画出方块
void DrawBlock(int shape, int form, int x, int y);
//空格覆盖
void DrawSpace(int shape, int form, int x, int y);
//判断该方块落到(x, y)处是否合法
int IsLegal(int shape, int form, int x, int y);
//判断函数
int JudeFunc();