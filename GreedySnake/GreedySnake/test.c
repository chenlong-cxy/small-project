#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

#define UP    72
#define DOWN  80        //��������
#define LEFT  75
#define RIGHT 77
#define SPACE 32
#define ESC 27  
#define KONG 0  
#define WALL 1  
#define FOOD 2  
#define BODY 3
#define SIZE_X 23   //Χǽ�ߴ��С
#define SIZE_Y 30

void gotoxy(int x, int y);   //�ƶ����
void hidden_cursor();   //���ع��
int color(int c);   //��ɫ
void inter_face();  //��ʼ������
void init_snake();  //��ʼ����
void draw_snake(int x);  //x=1���� x=0�ո�
void rand_food();   //����ʳ��
void move_snake(int x, int y); //�ƶ�
void run(int x, int y, int *time_count);//����
void pd();          //�ж���Ϸ�������Ե�ʳ��
void game();
void MaxGrade();//��߼�¼
int map[SIZE_X][SIZE_Y];
int speed = 1000;
int food;
int grade = 0;
int max_grade = 0;
const int snake_color = 11;
const int wall_color = 2;
const int food_color = 12;


struct Snake    //�� 
{
	int len;    //����
	int x;
	int y;      //��ͷ����
}snake;
struct Body    //����ڵ�
{
	int x;
	int y;
};

struct Body body[SIZE_X*SIZE_Y];
int main()
{
	system("title ̰����");
	system("cls");
	system("mode con cols=84 lines=26"); //���ô��ڳߴ�
	srand(time(NULL));  //�����
	hidden_cursor();
	grade = 0;
	MaxGrade();
	inter_face();
	init_snake();
	rand_food();
	draw_snake(1);
	game();
	return 0;
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
void game()         //�ƶ�����
{
	int n = RIGHT, time_count = 0, n_tmp;
	goto loop;
	while (1)
	{
		n = getch();
		switch (n)
		{
		case UP:
		case DOWN:  
			if(n_tmp != LEFT && n_tmp != RIGHT) 
				n = n_tmp; 
			break;
		case LEFT:
		case RIGHT: 
			if(n_tmp != UP && n_tmp != DOWN) 
				n = n_tmp; 
			break;
		case 'r':
		case 'R':
		case SPACE:
		case ESC: 
			break;
		default: 
			n = n_tmp; 
			break;    //��������Ч
		}
	loop:
		switch (n)
		{
		case UP:
			if (snake.x - 1 != body[0].x)
			{
				run(-1, 0, &time_count);
				n_tmp = UP;
			}
				break;
		case DOWN: 
			if (snake.x + 1 != body[0].x)
			{
				run(1, 0, &time_count);
				n_tmp = DOWN;
			}
				   break;
		case LEFT: 
			if (snake.y - 1 != body[0].y)
			{
				run(0, -1, &time_count);
				n_tmp = LEFT;
			}
				   break;
		case RIGHT: 
			if (snake.y + 1 != body[0].y)
			{
				run(0, 1, &time_count);
				n_tmp = RIGHT;
			}
					break;
		case  SPACE: 
			while (1)
			{
				if (kbhit != 0)
				break;
			}
					 break;
		case ESC:  
			gotoxy(SIZE_X + 1, 0);
			printf("��������˳���Ϸ��");
			getch();
			exit(0);
			break;
		case 'r':
		case 'R': 
			main(); break;
		}
	}
}
void run(int x, int y, int *time_count)
{
	int t = 0;
	while (1)
	{
		if (*time_count == 0)
			*time_count = speed;
		while (--(*time_count))
		{
			if (t == 0)
				t = 1500000;
			while (--t);
			if (kbhit() != 0)
				break;
		}
		if (*time_count == 0)
		{
			move_snake(x, y);
			pd();
		}
		else
			break;
	}
}
void pd()//�ж��Ƿ�ײǽ����ײ������
{
	if (map[snake.x][snake.y] == WALL || map[snake.x][snake.y] == BODY)
	{
		char n;
		Sleep(2000); //��ʱ
		system("cls");
		gotoxy(SIZE_X / 2 - 2, 2 * (SIZE_Y / 3));
		if (grade>max_grade)
			printf("��ϲ�����Ƽ�¼��Ŀǰ��߼�¼Ϊ��%d", grade);
		else if (grade == max_grade)
			printf("���¼��ƽ����ͻ����ļ��ޣ�");
		else
			printf("�����Ŭ����������߼�¼ֻ�%d", max_grade - grade);
		gotoxy(SIZE_X / 2, 2 * (SIZE_Y / 3));
		printf("GAME OVER!\n");
		MaxGrade();
		do
		{
			gotoxy(SIZE_X / 2 + 2, 2 * (SIZE_Y / 3));
			printf("�Ƿ����¿�ʼ��Ϸ(y/n): ");
			scanf("%c", &n);
			gotoxy(SIZE_X / 2 + 4, 2 * (SIZE_Y / 3));
			if (n != 'n' && n != 'N' && n != 'y' && n != 'Y')
				printf("�����������������!");
			else
				break;
		} while (1);
		if (n == 'n' || n == 'N')
		{
			gotoxy(SIZE_X / 2 + 4, 2 * (SIZE_Y / 3));
			printf("��������˳���Ϸ��");
			exit(0);
		}
		else if (n == 'y' || n == 'Y')
			main();
	}
	else if (map[snake.x][snake.y] == FOOD)
	{
		snake.len++;
		grade += 100;
		if (speed>400)
			speed -= 20;
		gotoxy(7, 2 * (SIZE_Y + 2));
		printf("����: %d", grade); //������ʾ����
		map[food / SIZE_Y][food%SIZE_Y] = KONG; //ԭ����ʳ��λ������ΪKONG
		rand_food();
	}
}
void rand_food()//����ˢ��ʳ��
{
	do
	{
		food = rand() % (SIZE_X*SIZE_Y);
	}while(map[food / SIZE_Y][food%SIZE_Y] != KONG);
	map[food / SIZE_Y][food%SIZE_Y] = FOOD;
	color(food_color);
	gotoxy(food / SIZE_Y, 2 * (food%SIZE_Y));
	printf("��");
}
void move_snake(int x, int y)//�ƶ���ʱ�ĸ�ֵ
{
	int i;
	draw_snake(0);  //ԭ����λ�û��Ͽո�
	map[body[snake.len - 1].x][body[snake.len - 1].y] = KONG; //���һ����β����ΪKONG
	map[snake.x][snake.y] = BODY; //ԭ������ͷ����ΪBODY
	for (i = snake.len - 1; i>0; i--)
	{
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
	body[0].x = snake.x;
	body[0].y = snake.y;
	snake.x = snake.x + x;
	snake.y = snake.y + y;
	draw_snake(1);  //�����µ�����
}
void draw_snake(int x)//��ӡ��
{
	int i;
	if (x != 0)
	{
		color(snake_color);
		gotoxy(snake.x, 2 * snake.y);
		printf("��");
		for (i = 0; i<snake.len; i++)
		{
			gotoxy(body[i].x, 2 * body[i].y);
			printf("��");
		}
	}
	else
	{
		if (body[snake.len - 1].x != 0)
		{
			gotoxy(body[snake.len - 1].x, 2 * body[snake.len - 1].y);
			printf("  ");
		}
	}
}
void inter_face()//����
{
	int i, j;
	for (i = 0; i<SIZE_X; i++)
	{
		for (j = 0; j<SIZE_Y + 12; j++)
		{
			if (i == 0 || j == 0 || i == SIZE_X - 1 || j == SIZE_Y - 1 || j == SIZE_Y + 11)
			{
				color(wall_color);
				gotoxy(i, 2 * j);
				printf("��");
				map[i][j] = WALL;
			}
			else if ((i == SIZE_X / 3 || i == SIZE_X * 2 / 3) && j>SIZE_Y / 3 && j<SIZE_Y * 2 / 3)
			{
				gotoxy(i, 2 * j);
				printf("��");
				map[i][j] = WALL;
			}
			else
			{
				gotoxy(i, 2 * j);
				printf(" ");
				map[i][j] = KONG;
			}
		}
		printf("\n");
	}
	color(snake_color);

	gotoxy(5, 2 * (SIZE_Y + 2));
	printf("��߼�¼: %d", max_grade);

	gotoxy(7, 2 * (SIZE_Y + 2));
	printf("����: %d", grade);

	gotoxy(9, 2 * (SIZE_Y + 2));
	printf("���¿�ʼ: R");

	gotoxy(11, 2 * (SIZE_Y + 2));
	printf("��ͣ: space");

	gotoxy(13, 2 * (SIZE_Y + 2));
	printf("�˳���Ϸ: ESC");


}
void init_snake()//��ʼ����
{
	snake.len = 2;
	snake.x = SIZE_X / 2;
	snake.y = SIZE_Y / 2;
	body[0].x = SIZE_X / 2;
	body[0].y = SIZE_Y / 2 - 1;
	body[1].x = SIZE_X / 2;
	body[1].y = SIZE_Y / 2 - 2;
	map[body[0].x][body[0].y] = BODY;
	map[body[1].x][body[1].y] = BODY;
}
void MaxGrade()//��߼�¼
{
	FILE *fp;
	fp = fopen("̰������߼�¼.txt", "r+");
	if (fp == NULL)
	{
		fp = fopen("̰������߼�¼.txt", "w+");
		fwrite(&max_grade, sizeof(int), 1, fp);
	}
	fseek(fp, 0, SEEK_SET);
	fread(&max_grade, sizeof(int), 1, fp);
	fseek(fp, 0, SEEK_SET);
	if (max_grade<grade)
	{
		fwrite(&grade, sizeof(int), 1, fp);
	}
}
void gotoxy(int x, int y) //�ƶ����� 
{

	COORD coord;

	coord.X = y;

	coord.Y = x;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
void hidden_cursor()//���ع��

{

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cci;

	GetConsoleCursorInfo(hOut, &cci);

	cci.bVisible = 0;//��1Ϊ��ʾ����0Ϊ����

	SetConsoleCursorInfo(hOut, &cci);

}
int color(int c)//������ɫ
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}
