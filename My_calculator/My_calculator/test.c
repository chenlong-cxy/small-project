#include"calculator.h"
void menu()
{
	printf("|-------------------------|\n");
	printf("|      1.Add   2.Sub      |\n");
	printf("|      3.Mul   4.Div      |\n");
	printf("|         0.exit          |\n");
	printf("|-------------------------|\n");
}

//int main()
//{
//	int input = 0;
//	do
//	{
//		menu();
//		printf("��ѡ��:>\n");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//			cals(Add);
//			break;
//		case 2:
//			cals(Sub);
//			break;
//		case 3:
//			cals(Mul);
//			break;
//		case 4:
//			cals(Div);
//			break;
//		case 0:
//			printf("�˳�������\n");
//			break;
//		default:
//			printf("ѡ�����������ѡ��\n");
//			break;
//		}
//	} while (input);
//	return 0;
//}

int main()
{
	int input = 0;
	int x = 0;
	int y = 0;
	int(*p[])(int, int) = { 0, Add, Sub, Mul, Div };
	do
	{
		menu();
		printf("��ѡ��:>\n");
		scanf("%d", &input);
		if (input == 0)
		{
			printf("�˳�������\n");
			break;
		}
		else if (input<0 || input>4)
		{
			printf("ѡ�����������ѡ��\n");
			continue;
		}
		printf("������������\n");
		scanf("%d %d", &x, &y);
		int ret = p[input](x, y);
		printf("ret=%d\n", ret);
	} while (input);
	return 0;
}