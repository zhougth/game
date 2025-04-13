#pragma once
#include<graphics.h>
#include<string>
#include<stdlib.h>
using namespace std;
class button {
public:
	void setColor(COLORREF);
	void setNum(int);
	void creatButtom(int x, int y, int width, int heigth, COLORREF color, string pText,int num);
	void drawButtom(int);
	int mouseInButtom(MOUSEMSG m);
	void gameButton(MOUSEMSG m, string str);
	int clickButtom(MOUSEMSG m);
	void drawGameButtom(int size);
	void drawOverButtom();
	friend bool mouseMsg(ExMessage* msg, int& n, int** ans, int** realB, int size , int stepNum , int x1, int y1, int x2, int y2);
private:
	int x;
	int y;
	int width;
	int heigth;
	COLORREF color;
	string pText;
	int num = 0;
};
class solidTopic {
private:
	int*** total;
	int A1[3][2] = { 2,0,1,0,1,1 };
	int relativeB1[3][2] = { 0,2,2,2,2,0 };
	int realB1[3][2] = { 0,2,1,2,1,1 };
	int A2[5][2] = { 3,1,3,2,4,2,4,3,3,3 };
	int relativeB2[5][2] = { 4,0,4,0,2,0,2,0,3,1 };
	int realB2[5][2] = { 4,0,4,1,3,1,3,2,3,3 };
public:
	int*** getTopic(int num);
	void freeMemory(int n);
};
bool check(int **a, int **b, int n);
void game(int stepNum, int size);
void menu();
int*** random(int n, int** A, int** realB, int** relativeB, int*** total);
void Random( int n);
void freeMemory(int n, int** A, int** realB, int** relativeB, int*** total);
void SolidMode();
bool isDeadEnd(int x, int y, int** visited, int directionx[4], int directiony[4]);
bool randomMsg(ExMessage* msg, int** ans, int **realB, int& n, int stepNum);
bool judgeIn(int x, int y, int i, int j);