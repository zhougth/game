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
	void drawButtom(int);
	int mouseInButtom(MOUSEMSG m);
	void gameButton(MOUSEMSG m, string str);
	int clickButtom(MOUSEMSG m);
	void drawGameButtom(int size);
	void drawOverButtom();
	friend bool mouseMsg(ExMessage* msg, button **block, int& n, int **ans, int realB[][2],int size, int stepNum);
private:
	int x;
	int y;
	int width;
	int heigth;
	COLORREF color;
	string pText;
	int num = 0;
};
bool check(int **a, int b[][2], int n);
void game(int stepNum, int size);
void menu();
int*** random(int n, int** A, int** realB, int** relativeB, int*** total);
void Random( int n);
void freeMemory(int n, int** A, int** realB, int** relativeB, int*** total);
void SolidMode();