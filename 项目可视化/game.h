#pragma once
#include<iostream>
#include<graphics.h>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<ctime>
#include"solidMode.h"
#include"randomMode.h"
using namespace std;
class button {
public:
	void setColor(COLORREF);
	void setNum(int);
	void creatButtom(int x, int y, int width, int heigth, COLORREF color, string pText = "", int num = 0);
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
void menu();
int timer1();
void timer2(int);
void retreat(int& n, int** ans, int** realB, int size, int stepNum, int x1, int y1, int x2, int y2);
void drawReturn();
bool inReturn(ExMessage m);
bool inReturn(MOUSEMSG m);
void drawNext();
bool inNext(ExMessage m);
bool inNext(MOUSEMSG m);
void drawRetreat();
bool inRetreat(MOUSEMSG m);
bool inRetreat(ExMessage m);
bool ifOpen(int** ans, int step,int i, int j);