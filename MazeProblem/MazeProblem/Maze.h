#pragma once
//�Թ���С
#define MAXROW 13
#define MAXCOL 17
//Ĭ�ϳ���
#define EXITROW MAXROW-2
#define EXITCOL MAXCOL-2

typedef struct Offsets
{
	int vert;   //����ƫ��
	int horiz;  //����ƫ��
}Offsets;

typedef struct MazePosition
{
	int row;//�к�
	int col;//�к�
	int dir;//�����
}MazePosition;

//Ĭ�����Ϊ(1,1)������Ϊ(EXITROW,EXITCOL)
void Path(int Maze[MAXROW][MAXCOL]);