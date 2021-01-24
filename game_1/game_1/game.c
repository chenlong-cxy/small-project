#include"game.h"

void menu()
{
	printf("************************\n");
	printf("****     1.play     ****\n");
	printf("****     0.exit     ****\n");
	printf("************************\n");
	printf("请输入:>\n");
}

void Displayboard(char board[ROW][COL], int row, int  col)
{
	
}

char checkWin(char board[ROW][COL], int row, int col)
{

}

void game(char board[ROW][COL],int row,int col)
{
	Displayboard(board,row,col);//打印空棋盘
	while (1)
	{
		//玩家走
		playerMove(board, row, col);
		checkWin(board, row, col);
		//电脑走
		checkWin(board, row, col);
		computerMove(board, row, col);

	}
}
