#pragma once
//迷宫大小
#define MAXROW 13
#define MAXCOL 17
//默认出口
#define EXITROW MAXROW-2
#define EXITCOL MAXCOL-2

typedef struct Offsets
{
	int vert;   //纵向偏移
	int horiz;  //横向偏移
}Offsets;

typedef struct MazePosition
{
	int row;//行号
	int col;//列号
	int dir;//方向号
}MazePosition;

//默认入口为(1,1)，出口为(EXITROW,EXITCOL)
void Path(int Maze[MAXROW][MAXCOL]);