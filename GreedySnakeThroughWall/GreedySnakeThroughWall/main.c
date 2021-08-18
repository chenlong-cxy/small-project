#include "GreedySnake.h"
int max;
int grade;
int main()
{
#pragma warning (disable:4996)
	max = 0, grade = 0;
	system("title Ã∞≥‘…ﬂ");
	system("mode con cols=84 lines=23");
	HideCursor();
	ReadGrade();
	InitInterface();
	InitSnake();
	srand((unsigned int)time(NULL));
	RandFood();
	DrawSnake(1);
	Game();
	return 0;
}