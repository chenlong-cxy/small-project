#include "Tetris.h"
int max, grade;
int main()
{
	max = 0, grade = 0;
	system("title 俄罗斯方块"); //设置cmd窗口的名字
	system("mode con lines=29 cols=60"); //设置cmd窗口的大小
	ReadGrade(); //从文件读取最高分
	HideCursor(); //隐藏光标

	InitInterface(); //初始化界面
	InitBlockInfo(); //初始化方块信息
	srand((unsigned int)time(NULL)); //设置随机数生成的起点

	StartGame(); //开始游戏

	return 0;
}

//#include <conio.h>
//
//#include <stdio.h>
//
//int main() {
//
//	int ch;
//
//	while (1){
//
//		if (_kbhit()){//如果有按键按下，则_kbhit()函数返回真
//
//			ch = _getch();//使用_getch()函数获取按下的键值
//
//			printf("%d\n", ch);
//
//			if (ch == 27){
//
//				break;
//
//			}//当按下ESC时循环，ESC键的键值时27.
//
//		}
//
//	}
//
//	system("pause");
//
//}

//#include <stdio.h>
//#include <conio.h>
//int main()
//{
//	char a, b;
//	while (1)
//	{
//		a = getch();
//		b = getch();
//		printf("%d %d\n", a, b);
//	}
//}