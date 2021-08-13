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
	int data[ROW][COL + 10]; //���ڱ��ָ��λ���Ƿ��з��飨1Ϊ�У�0Ϊ�ޣ�
	int color[ROW][COL + 10]; //���ڼ�¼ָ��λ�õķ�����ɫ����
}face;

struct Block
{
	int space[4][4];
}block[7][4]; //���ڴ洢7�ֻ�����״����ĸ��Ե�4����̬����Ϣ����28

//���ļ���ȡ��߷�
void ReadGrade();
//����߷�д���ļ�
void WriteGrade();
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