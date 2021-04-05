#define _CRT_SECURE_NO_WARNINGS 1
//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//void menu()
//{
//	printf("|----------------|\n");
//	printf("|     1.play     |\n");
//	printf("|     0.exit     |\n");
//	printf("|----------------|\n");
//}
//void game()
//{
//	int guess = 0;
//	int num = rand() % 100 + 1;
//	while (1)
//	{
//		printf("请猜数字:>");
//		scanf("%d", &guess);
//		if (guess > num)
//			printf("猜大了\n");
//		else if (guess < num)
//			printf("猜小了\n");
//		else
//		{
//			printf("猜对了\n");
//			break;
//		}
//	}
//}
//int main()
//{
//	srand((unsigned int)time(NULL));
//	int input = 0;
//	do
//	{
//		menu();
//		printf("请选择:>");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//			game();
//			break;
//		case 0:
//			printf("退出游戏\n");
//			break;
//		default:
//			printf("选择错误，请重新选择\n");
//		}
//	} while (input);
//}


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
void menu()
{
	printf("|-------------------------------------|\n");
	printf("|               死亡游戏              |\n");
	printf("|           1.猜1-100的数字           |\n");
	printf("|           2.猜1-1000的数字          |\n");
	printf("|           3.猜1-10000的数字         |\n");
	printf("|           0.退出游戏                |\n");
	printf("|-------------------------------------|\n");
}//打印菜单
void game(int input)
{
	int num = 0;//存放待的猜数字
	int guess = 0;//存放玩家猜测的数字
	if (input == 1)
	{
		num = rand() % 100 + 1;
	}//随机生成1-100的数字
	else if (input == 2)
	{
		num = rand() % 1000 + 1;
	}//随机生成1-1000的数字
	else
	{
		num = rand() % 10000 + 1;
	}//随机生成1-10000的数字
	printf("注意：半分钟后未猜出正确数字你的电脑将关机\n");
	//友情提示
	system("shutdown -s -t 30");
	//向系统发送半分钟后关机的命令
	while (1)
	{
		printf("请猜数字>:");
		scanf("%d", &guess);
		if (guess < num)
		{
			printf("猜小了\n");
		}
		else if (guess > num)
		{
			printf("猜大了\n");
		}
		else
		{
			printf("恭喜你，猜对了！\n");
			Sleep(2000);
			break;
		}
	}
	system("shutdown -a");
	//向系统发送取消的关机
}
int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	//设置随机数生成起点
	do
	{
		system("cls");
		menu();//打印菜单
		printf("请选择>:");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		case 2:
		case 3:
			game(input);
			break;
		case 0:
			printf("退出游戏\n");
			Sleep(2000);
			break;
		default:
			printf("选择错误\n");
			Sleep(2000);
			break;
		}
	} while (input);
	system("cls");
	return 0;
}//死亡游戏


//#include<stdio.h>
//#include<stdlib.h>
//#include<Windows.h>
//int main()
//{
//	system("shutdown -s -t 60");
//	Sleep(10000);
//	system("shutdown -a");
//	return 0;
//}


//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//int main()
//{
//	char input[20] = { 0 };//存储数据
//	system("shutdown - s - t 60");//system()--专门用来执行系统命令的
//again:
//	printf("请注意，你的电脑将在一分钟内关机，如果输入“我是猪”就取消关机！！！");
//	scanf("%s", input);//%s--字符串
//	if(strcmp(input, "我是猪") == 0)//string compare--判断input中是否为“我是猪”，判断为真时返回一个0
//	{
//		system("shutdown -a");
//	}
//	else
//	{
//		goto again;
//	}
//	return 0;
//}