#include <stdio.h>
#include <Windows.h>

#define ROW 29 //��Ϸ������
#define COL 20 //��Ϸ������

struct Block
{
	int space[4][4];
}block[7][4];


//���ع��
void HideCursor();
//�����ת
void CursorJump(int x, int y);
//��ʼ������
void InitInterface();
//��ʼ��������Ϣ
void InitBlockInfo();