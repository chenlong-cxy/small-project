#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define ROW 29 //��Ϸ������
#define COL 20 //��Ϸ������

#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //���������

#define SPACE 32 //�ո��
#define ESC 27 //Esc��

struct Face
{
	int data[ROW][COL + 10];
	int color[ROW][COL + 10];
}face;

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
//��ʼ��Ϸ
void StartGame();
//��ɫ����
void color(int num);
//��������
void DrawBlock(int shape, int form, int x, int y);
//�ո񸲸�
void DrawSpace(int shape, int form, int x, int y);
//�жϸ÷����䵽(x, y)���Ƿ�Ϸ�
int IsLegal(int shape, int form, int x, int y);
//�жϺ���
int JudeFunc();