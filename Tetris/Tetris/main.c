#include "Tetris.h"
int max, grade;
int main()
{
	max = 0, grade = 0;
	system("title ����˹����"); //����cmd���ڵ�����
	system("mode con lines=29 cols=60"); //����cmd���ڵĴ�С
	ReadGrade(); //���ļ���ȡ��߷�
	HideCursor(); //���ع��

	InitInterface(); //��ʼ������
	InitBlockInfo(); //��ʼ��������Ϣ
	srand((unsigned int)time(NULL)); //������������ɵ����

	StartGame(); //��ʼ��Ϸ

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
//		if (_kbhit()){//����а������£���_kbhit()����������
//
//			ch = _getch();//ʹ��_getch()������ȡ���µļ�ֵ
//
//			printf("%d\n", ch);
//
//			if (ch == 27){
//
//				break;
//
//			}//������ESCʱѭ����ESC���ļ�ֵʱ27.
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