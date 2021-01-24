#include"game.h"

void menu()
{
	printf("|----------------------|\n");
	printf("|        1.play        |\n");
	printf("|        0.exit        |\n");
	printf("|----------------------|\n");
	printf("������:>\n");
}

void game()
{
	char ret = 0;
	char board[ROW][COL];
	//��ʼ�����̣���ʼ��Ϊ�ո�
	InitBoard(board, ROW, COL);
	//��ӡ����
	DisplayBoard(board, ROW, COL);
	while (1)
	{
		//�������
		PlayerMove(board, ROW, COL);
		system("cls");
		DisplayBoard(board, ROW, COL);
		ret = CheckWin(board, ROW, COL);
		if (ret != 'c')
			break;
		//��������
		ComputerMove(board, ROW, COL);
		system("cls");
		DisplayBoard(board, ROW, COL);
		Sleep(1500);
		ret = CheckWin(board, ROW, COL);
		if (ret != 'c')
			break;
	}
	if (ret == '#')
		printf("���Ӯ\n");
	else if (ret == '*')
		printf("����Ӯ\n");
	else if (ret == 'q')
		printf("����\n");
	Sleep(1000);
}

int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			system("cls");
			game();//���������Ϸ
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ�����������ѡ��!\n");
			break;
		}
		system("cls");
	} while (input);
	return 0;
}