#include "contact.h"
void menu()
{
	printf("|-----------------------|\n");
	printf("|        contact        |\n");
	printf("|   1.Add     2.Delete  |\n");
	printf("|   3.Search  4.Modify  |\n");
	printf("|   5.Show    6.Sort    |\n");
	printf("|        0.exit         |\n");
	printf("|-----------------------|\n");
}
int main()
{
	int input = 0;
	//创建通讯录
	struct Contact con;//con就是通讯录，里面包含1000个元素的数组和size
	//初始化通讯录
	InitContact(&con);
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case Add:
			AddContact(&con);
			break;
		case Delete:
			break;
		case Sreach:
			break;
		case Modify:
			break;
		case Show:
			ShowContact(&con);
			break;
		case Sort:
			break;
		case exit:
			printf("退出通讯录\n");
			break;
		default:
			printf("选择错误，请重新选择\n");
			break;
		}
	} while (input);
	return 0;
}