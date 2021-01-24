#define ROW 3
#define COL 3

#include<stdio.h>

void menu();

void game(char board[ROW][COL],int row,int col);

void Displayboard(char board[ROW][COL], int row, int  col);

char checkWin(char board[ROW][COL], int row, int col);