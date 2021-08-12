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
				face.data[i][j] = 1;
				CursorJump(2 * j, i);
				printf("��");
			}
			else if (i == ROW - 1)
			{
				face.data[i][j] = 1;
				printf("��");
			}
			else
				face.data[i][j] = 0;
		}
	}
	for (int i = COL; i < COL + 10; i++)
	{
		face.data[8][i] = 1;
		CursorJump(2 * i, 8);
		printf("��");
	}

	CursorJump(2 * COL, 1);
	printf("Next Block��");

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
	printf("��ǰ������%d", grade);
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
		block[6][0].space[i][1] = 1;

	int temp[4][4];
	for (int shape = 0; shape < 7; shape++) //7����״
	{
		for (int form = 0; form < 3; form++) //4����̬���Ѿ�����һ�֣�����ÿ����������3�֣�
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp[i][j] = block[shape][form].space[i][j]; //��ȡ������״
				}
			}
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					block[shape][form + 1].space[i][j] = temp[3 - j][i];
				}
			}
		}
	}
}

//��ʼ��Ϸ
void StartGame()
{
	int x = COL / 2 - 2, y = 0;
	int t = 0;
	int form = 0, shape = rand() % 7;
	int nextShape = rand() % 7;
	color(nextShape);
	DrawBlock(nextShape, form, COL + 4, 3);
	while (1)
	{
		//��ӡ���ڽ���ķ���
		color(shape);
		DrawBlock(shape, form, x, y);
		if (t == 0)
		{
			t = 15000;
		}
		while (--t)
		{
			if (kbhit() != 0) //���̱��û����˳�ѭ��
				break;
		}
		if (t == 0) //����δ���û�
		{
			if (IsLegal(shape, form, x, y + 1) == 0) //����������Ͳ��Ϸ��ˣ��Ѿ�����ײ���
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (block[shape][form].space[i][j] == 1)
						{
							face.data[y + i][x + j] = 1;
							face.color[y + i][x + j] = shape;
							while(JudeFunc());
						}
					}
				}
				return;
			}
			else //δ���ײ�
			{
				DrawSpace(shape, form, x, y); //�����ǰ����״̬��׼���������������´�ӡһ��
				y++;
			}
		}
		else //���̱��û�
		{
			char ch = getch(); //��ȡkeycode
			switch (ch)
			{
			case DOWN:
				if (IsLegal(shape, form, x, y + 1) == 1)
				{
					DrawSpace(shape, form, x, y);
					y++;
				}
				break;
			case LEFT:
				if (IsLegal(shape, form, x - 1, y) == 1)
				{
					DrawSpace(shape, form, x, y);
					x--;
				}
				break;
			case RIGHT:
				if (IsLegal(shape, form, x + 1, y) == 1)
				{
					DrawSpace(shape, form, x, y);
					x++;
				}
				break;
			case SPACE:
				if (IsLegal(shape, (form + 1) % 4, x, y + 1) == 1)
				{
					DrawSpace(shape, form, x, y);
					y++;
					form = (form + 1) % 4;
				}
				break;
			case ESC:
				system("cls");
				system("pause>nul");
				printf("---�밴������˳�---");
				exit(0);
			case 's':
			case 'S':
				system("pause>nul");
				break;
			case 'r':
			case 'R':
				system("cls");
				main();
			}
		}
	}
}
//��ɫ����
void color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
}
//��������
void DrawBlock(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1)
			{
				CursorJump(2 * (x + j), y + i);
				printf("��");
			}
		}
	}
}
//�ո񸲸�
void DrawSpace(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1)
			{
				CursorJump(2 * (x + j), y + i);
				printf("  ");
			}
		}
	}
}
//�жϸ÷����䵽(x, y)���Ƿ�Ϸ�
int IsLegal(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((block[shape][form].space[i][j] == 1) && (face.data[y + i][x + j] == 1))
				return 0; //���Ϸ�
		}
	}
	return 1; //�Ϸ�
}
//�жϺ���
int JudeFunc()
{
	for (int i = ROW - 2; i > 4; i--)
	{
		int sum = 0;
		for (int j = 1; j < COL - 1; j++)
		{
			sum += face.data[i][j];
		}
		if (sum == 0) //����û�з��飬�������ж����ϵĲ��
			break;
		if (sum == COL - 2) //����ȫ�����ɵ÷�
		{
			grade += 10;
			color(7);
			CursorJump(2 * COL + 4, ROW - 3);
			printf("��ǰ������%d", grade);
			for (int j = 1; j < COL - 1; j++) //���������Ϣ
			{
				face.data[i][j] = 0;
				CursorJump(2 * j, i);
				printf("  ");
			}
			//�Ѹ������������������Ųһ��
			for (int m = i; m >1; m--)
			{
				sum = 0;
				for (int n = 1; n < COL - 1; n++)
				{
					sum += face.data[m - 1][n];
					face.data[m][n] = face.data[m - 1][n];
					face.color[m][n] = face.data[m - 1][n];
					if (face.data[m][n] == 1)
					{
						CursorJump(2 * n, m);
						color(face.color[m][n]);
						printf("��");
					}
					else
					{
						CursorJump(2 * n, m);
						printf("  ");
					}
				}
				if (sum == 0)
					return 1;
			}
		}
	}
	for (int j = 1; j < COL - 1; j++)
	{
		if (face.data[0][j] == 1) //��Ϸ����
		{
			Sleep(1000);
			system("cls");
			color(7);
			if (grade>max)
			{
				printf("��ϲ���Ƽ�¼����¼����Ϊ%d\n", grade);
			}
			else if (grade == max)
			{
				printf("����߼�¼��ƽ��Ϊ%d\n", grade);
			}
			else
			{
				printf("����߼�¼���%d����������\n", max - grade);
			}

			char ch;
			printf("�Ƿ�����һ�̣�(y/n):");
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y')
			{
				system("cls");
				main();
			}
			else
			{
				exit(0);
			}
		}
	}
	return 0;
}