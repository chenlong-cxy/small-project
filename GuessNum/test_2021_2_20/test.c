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
//		printf("�������:>");
//		scanf("%d", &guess);
//		if (guess > num)
//			printf("�´���\n");
//		else if (guess < num)
//			printf("��С��\n");
//		else
//		{
//			printf("�¶���\n");
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
//		printf("��ѡ��:>");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//			game();
//			break;
//		case 0:
//			printf("�˳���Ϸ\n");
//			break;
//		default:
//			printf("ѡ�����������ѡ��\n");
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
	printf("|               ������Ϸ              |\n");
	printf("|           1.��1-100������           |\n");
	printf("|           2.��1-1000������          |\n");
	printf("|           3.��1-10000������         |\n");
	printf("|           0.�˳���Ϸ                |\n");
	printf("|-------------------------------------|\n");
}//��ӡ�˵�
void game(int input)
{
	int num = 0;//��Ŵ��Ĳ�����
	int guess = 0;//�����Ҳ²������
	if (input == 1)
	{
		num = rand() % 100 + 1;
	}//�������1-100������
	else if (input == 2)
	{
		num = rand() % 1000 + 1;
	}//�������1-1000������
	else
	{
		num = rand() % 10000 + 1;
	}//�������1-10000������
	printf("ע�⣺����Ӻ�δ�³���ȷ������ĵ��Խ��ػ�\n");
	//������ʾ
	system("shutdown -s -t 30");
	//��ϵͳ���Ͱ���Ӻ�ػ�������
	while (1)
	{
		printf("�������>:");
		scanf("%d", &guess);
		if (guess < num)
		{
			printf("��С��\n");
		}
		else if (guess > num)
		{
			printf("�´���\n");
		}
		else
		{
			printf("��ϲ�㣬�¶��ˣ�\n");
			Sleep(2000);
			break;
		}
	}
	system("shutdown -a");
	//��ϵͳ����ȡ���Ĺػ�
}
int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	//����������������
	do
	{
		system("cls");
		menu();//��ӡ�˵�
		printf("��ѡ��>:");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		case 2:
		case 3:
			game(input);
			break;
		case 0:
			printf("�˳���Ϸ\n");
			Sleep(2000);
			break;
		default:
			printf("ѡ�����\n");
			Sleep(2000);
			break;
		}
	} while (input);
	system("cls");
	return 0;
}//������Ϸ


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
//	char input[20] = { 0 };//�洢����
//	system("shutdown - s - t 60");//system()--ר������ִ��ϵͳ�����
//again:
//	printf("��ע�⣬��ĵ��Խ���һ�����ڹػ���������롰��������ȡ���ػ�������");
//	scanf("%s", input);//%s--�ַ���
//	if(strcmp(input, "������") == 0)//string compare--�ж�input���Ƿ�Ϊ�����������ж�Ϊ��ʱ����һ��0
//	{
//		system("shutdown -a");
//	}
//	else
//	{
//		goto again;
//	}
//	return 0;
//}