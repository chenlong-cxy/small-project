#include"game.h"

void menu()
{
	printf("************************\n");
	printf("****     1.play     ****\n");
	printf("****     0.exit     ****\n");
	printf("************************\n");
	printf("������:>\n");
}

void Displayboard(char board[ROW][COL], int row, int  col)
{
	
}

char checkWin(char board[ROW][COL], int row, int col)
{

}

void game(char board[ROW][COL],int row,int col)
{
	Displayboard(board,row,col);//��ӡ������
	while (1)
	{
		//�����
		playerMove(board, row, col);
		checkWin(board, row, col);
		//������
		checkWin(board, row, col);
		computerMove(board, row, col);

	}
}
