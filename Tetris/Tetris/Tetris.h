#include <stdio.h>
#include <Windows.h>

#define ROW 29 //游戏区行数
#define COL 20 //游戏区列数

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