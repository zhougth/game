#pragma once
#include<graphics.h>
#include<string>
#include<stdlib.h>
using namespace std;
struct solidTopic;
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