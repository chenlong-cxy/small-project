#include"game.h"
int main()
{
	int input = 0;
	char board[ROW][COL] = ' ';
	do{
		menu();
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game(board,ROW,COL);
			break;
		case 0:
			printf("ÍË³öÓÎÏ·\n");
			break;
		}
	} while (input);
	return 0;
}