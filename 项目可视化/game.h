#pragma once
#include<graphics.h>
#include<string>
#include<stdlib.h>
using namespace std;
class button {
public:
	COLORREF& getColor();
	int& getNum();
	void creatButtom(int x, int y, int width, int heigth, COLORREF color, string pText,int num);
	void drawButtom();
	int mouseInButtom(MOUSEMSG m);
	void gameButton(MOUSEMSG m, string str);
	int clickButtom(MOUSEMSG m);
	void drawGameButtom();
	void drawOverButtom();
	friend bool mouseMsg(ExMessage* msg, button block[][3], int& n, int ans[][2], int realB[][2]);
private:
	int x;
	int y;
	int width;
	int heigth;
	COLORREF color;
	string pText;
	int num = 0;
};
bool check(int a[][2], int b[][2], int n);
bool mouseMsg(ExMessage* msg, button block[][3], int& n, int ans[][2], int realB[][2]);
void game();
void menu();
int*** random(int n, int** A, int** realB, int** relativeB, int*** total);
void Random( int n);
void freeMemory(int n, int** A, int** realB, int** relativeB, int*** total);