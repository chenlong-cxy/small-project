#define _CRT_SECURE_NO_WARNINGS 1
//地雷的总数
#define COUNT 10

#define ROW 9//扫雷的行数
#define COL 9//扫雷的列数

#define ROWS ROW+2//需要创建的二维数组的行数
#define COLS COL+2//需要创建的二维数组的列数

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

//初始化棋盘
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);
//打印棋盘
void DisplayBoard(char board[ROWS][COLS], int row, int col);
//布置雷
void SetMine(char mine[ROWS][COLS], int row, int col, int count);
//排查雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);

