#include "Tetris.h"


int max = 100;
int grade = 100;
//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.dwSize = 1;  //���û��ֵ�Ļ������ع����Ч
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

//�����ת
void CursorJump(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//��ʼ������
void InitInterface()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL + 10; j++)
		{
			if (j == 0 || j == COL - 1 || j == COL + 9)
			{
				CursorJump(2 * j, i);
				printf("��");
			}
			else if (i == ROW - 1)
			{
				printf("��");
			}

		}
	}
	CursorJump(2 * COL + 4, ROW - 19);
	printf("���ƣ���");

	CursorJump(2 * COL + 4, ROW - 17);
	printf("���ƣ���");

	CursorJump(2 * COL + 4, ROW - 15);
	printf("���٣���");

	CursorJump(2 * COL + 4, ROW - 13);
	printf("��ת���ո�");

	CursorJump(2 * COL + 4, ROW - 11);
	printf("��ͣ: S");

	CursorJump(2 * COL + 4, ROW - 9);
	printf("�˳�: Esc");

	CursorJump(2 * COL + 4, ROW - 7);
	printf("���¿�ʼ:R");

	CursorJump(2 * COL + 4, ROW - 5);
	printf("��߼�¼:%d", max);

	CursorJump(2 * COL + 4, ROW - 3);
	printf("������%d", grade);
}

//��ʼ��������Ϣ
void InitBlockInfo()
{
	//��T����
	for (int i = 0; i <= 2; i++)
		block[0][0].space[1][i] = 1;
	block[0][0].space[2][1] = 1;

	//��L����
	for (int i = 1; i <= 3; i++)
		block[1][0].space[i][1] = 1;
	block[1][0].space[3][2] = 1;

	//��J����
	for (int i = 1; i <= 3; i++)
		block[2][0].space[i][2] = 1;
	block[2][0].space[3][1] = 1;

	for (int i = 0; i <= 1; i++)
	{
		//��Z����
		block[3][0].space[1][i] = 1;
		block[3][0].space[2][i + 1] = 1;
		//��S����
		block[4][0].space[1][i + 1] = 1;
		block[4][0].space[2][i] = 1;
		//��O����
		block[5][0].space[1][i + 1] = 1;
		block[5][0].space[2][i + 1] = 1;
	}

	//��I����
	for (int i = 0; i <= 3;i++)
		block[6][0].space[i][2] = 1;

	int temp[4][4];
	for (int shape = 0; shape < 7; shape++) //7����״
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp[i][j] = block[shape][0].space[i][j]; //��ȡ������״
			}
		}
		for (int form = 0; form < 3; form++) //4����̬���Ѿ�����һ�֣�����ÿ����������3�֣�
		{
			for (int m = 0; m < 4; m++)
			{
				for (int n = 0; n < 4; n++)
				{
					block[shape][form].space[m][n] = temp[3 - n][m];
				}
			}
		}
	}
}