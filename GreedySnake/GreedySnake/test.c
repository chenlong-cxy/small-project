#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

#define UP    72
#define DOWN  80        //上下左右
#define LEFT  75
#define RIGHT 77
#define SPACE 32
#define ESC 27  
#define KONG 0  
#define WALL 1  
#define FOOD 2  
#define BODY 3
#define SIZE_X 23   //围墙尺寸大小
#define SIZE_Y 30

void gotoxy(int x, int y);   //移动光标
void hidden_cursor();   //隐藏光标
int color(int c);   //颜色
void inter_face();  //初始化界面
void init_snake();  //初始化蛇
void draw_snake(int x);  //x=1画蛇 x=0空格
void rand_food();   //生成食物
void move_snake(int x, int y); //移动
void run(int x, int y, int *time_count);//运行
void pd();          //判断游戏结束，吃到食物
void game();
void MaxGrade();//最高纪录
int map[SIZE_X][SIZE_Y];
int speed = 1000;
int food;
int grade = 0;
int max_grade = 0;
const int snake_color = 11;
const int wall_color = 2;
const int food_color = 12;


struct Snake    //蛇 
{
	int len;    //长度
	int x;
	int y;      //蛇头坐标
}snake;
struct Body    //身体节点
{
	int x;
	int y;
};

struct Body body[SIZE_X*SIZE_Y];
int main()
{
	system("title 贪吃蛇");
	system("cls");
	system("mode con cols=84 lines=26"); //设置窗口尺寸
	srand(time(NULL));  //随机数
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
void game()         //移动控制
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
			break;    //其他键无效
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
			printf("按任意键退出游戏！");
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
void pd()//判断是否撞墙或者撞到身体
{
	if (map[snake.x][snake.y] == WALL || map[snake.x][snake.y] == BODY)
	{
		char n;
		Sleep(2000); //延时
		system("cls");
		gotoxy(SIZE_X / 2 - 2, 2 * (SIZE_Y / 3));
		if (grade>max_grade)
			printf("恭喜您打破记录，目前最高纪录为：%d", grade);
		else if (grade == max_grade)
			printf("与纪录持平，请突破你的极限！");
		else
			printf("请继续努力，你与最高记录只差：%d", max_grade - grade);
		gotoxy(SIZE_X / 2, 2 * (SIZE_Y / 3));
		printf("GAME OVER!\n");
		MaxGrade();
		do
		{
			gotoxy(SIZE_X / 2 + 2, 2 * (SIZE_Y / 3));
			printf("是否重新开始游戏(y/n): ");
			scanf("%c", &n);
			gotoxy(SIZE_X / 2 + 4, 2 * (SIZE_Y / 3));
			if (n != 'n' && n != 'N' && n != 'y' && n != 'Y')
				printf("输入错误，请重新输入!");
			else
				break;
		} while (1);
		if (n == 'n' || n == 'N')
		{
			gotoxy(SIZE_X / 2 + 4, 2 * (SIZE_Y / 3));
			printf("按任意键退出游戏！");
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
		printf("分数: %d", grade); //更新显示分数
		map[food / SIZE_Y][food%SIZE_Y] = KONG; //原本的食物位置设置为KONG
		rand_food();
	}
}
void rand_food()//重新刷新食物
{
	do
	{
		food = rand() % (SIZE_X*SIZE_Y);
	}while(map[food / SIZE_Y][food%SIZE_Y] != KONG);
	map[food / SIZE_Y][food%SIZE_Y] = FOOD;
	color(food_color);
	gotoxy(food / SIZE_Y, 2 * (food%SIZE_Y));
	printf("★");
}
void move_snake(int x, int y)//移动蛇时的赋值
{
	int i;
	draw_snake(0);  //原来的位置画上空格
	map[body[snake.len - 1].x][body[snake.len - 1].y] = KONG; //最后一节蛇尾设置为KONG
	map[snake.x][snake.y] = BODY; //原来的蛇头设置为BODY
	for (i = snake.len - 1; i>0; i--)
	{
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
	body[0].x = snake.x;
	body[0].y = snake.y;
	snake.x = snake.x + x;
	snake.y = snake.y + y;
	draw_snake(1);  //画出新的蛇形
}
void draw_snake(int x)//打印蛇
{
	int i;
	if (x != 0)
	{
		color(snake_color);
		gotoxy(snake.x, 2 * snake.y);
		printf("■");
		for (i = 0; i<snake.len; i++)
		{
			gotoxy(body[i].x, 2 * body[i].y);
			printf("□");
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
void inter_face()//界面
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
				printf("■");
				map[i][j] = WALL;
			}
			else if ((i == SIZE_X / 3 || i == SIZE_X * 2 / 3) && j>SIZE_Y / 3 && j<SIZE_Y * 2 / 3)
			{
				gotoxy(i, 2 * j);
				printf("■");
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
	printf("最高纪录: %d", max_grade);

	gotoxy(7, 2 * (SIZE_Y + 2));
	printf("分数: %d", grade);

	gotoxy(9, 2 * (SIZE_Y + 2));
	printf("重新开始: R");

	gotoxy(11, 2 * (SIZE_Y + 2));
	printf("暂停: space");

	gotoxy(13, 2 * (SIZE_Y + 2));
	printf("退出游戏: ESC");


}
void init_snake()//初始化蛇
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
void MaxGrade()//最高记录
{
	FILE *fp;
	fp = fopen("贪吃蛇最高记录.txt", "r+");
	if (fp == NULL)
	{
		fp = fopen("贪吃蛇最高记录.txt", "w+");
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
void gotoxy(int x, int y) //移动坐标 
{

	COORD coord;

	coord.X = y;

	coord.Y = x;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
void hidden_cursor()//隐藏光标

{

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cci;

	GetConsoleCursorInfo(hOut, &cci);

	cci.bVisible = 0;//赋1为显示，赋0为隐藏

	SetConsoleCursorInfo(hOut, &cci);

}
int color(int c)//设置颜色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}
