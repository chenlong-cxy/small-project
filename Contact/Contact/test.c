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
	//����ͨѶ¼
	struct Contact con;//con����ͨѶ¼���������1000��Ԫ�ص������size
	//��ʼ��ͨѶ¼
	InitContact(&con);
	do
	{
		menu();
		printf("��ѡ��:>");
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
			printf("�˳�ͨѶ¼\n");
			break;
		default:
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while (input);
	return 0;
}