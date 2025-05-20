#pragma once
#include<iostream>
#include<graphics.h>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<ctime>
#include"solidMode.h"
#include"randomMode.h"
#include"players.h"
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
	friend int mouseMsg(int start,ExMessage* msg, int& n, int** ans, int** realB, int size , int stepNum , int x1, int y1, int x2, int y2);
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
void menu(players& Player);
int timer1();
void timer2(int);
void retreat(int& n, int** ans, int** realB, int size, int stepNum, int x1, int y1, int x2, int y2);
bool checkIn(MOUSEMSG m, int x1, int y1, int x2, int y2);
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
int success(int );
int lose(int);
void showTime(int start);
int showAns(int stepNum, int size, int*** total);