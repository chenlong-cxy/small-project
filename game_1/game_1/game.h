#define _CRT_SECURE_NO_WARNINGS 1
#define ROW 3
#define COL 3

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

//初始化棋盘
void InitBoard(char board[ROW][COL], int row, int col);
//打印棋盘
void DisplayBoard(char board[ROW][COL], int row, int col);
//玩家下棋
void PlayerMove(char board[ROW][COL], int row, int col);
//电脑下棋
void ComputerMove(char board[ROW][COL], int row, int col);
//判断游戏进展情况
char CheckWin(char board[ROW][COL], int row, int col);