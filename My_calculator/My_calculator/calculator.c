#include"calculator.h"
int Add(int x, int y)
{
	return x + y;
}

int Sub(int x, int y)
{
	return x - y;
}

int Mul(int x, int y)
{
	return x*y;
}

int Div(int x, int y)
{
	return x / y;
}

cals(int(*p)(int, int))
{
	int x = 0;
	int y = 0;
	printf("请输入两个数\n");
	scanf("%d %d", &x, &y);
	int ret = p(x, y);
	printf("ret=%d\n", ret);
}