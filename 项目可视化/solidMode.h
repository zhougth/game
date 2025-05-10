#pragma once
#include"game.h"
class solidTopic {
private:
	int*** total;
	int A1[3][2] = { 2,0,1,0,1,1 };
	int relativeB1[3][2] = { 0,2,2,2,2,0 };
	int realB1[3][2] = { 0,2,1,2,1,1 };
	int A2[5][2] = { 0,1,1,1,1,2,1,3,2,3 };
	int relativeB2[5][2] = { 4,3,2,3,2,1,1,0,0,1 };
	int realB2[5][2] = { 4,3,3,3,3,2,2,2,2,3 };
	int A3[5][2] = { 1,4,2,4,2,3,2,2,2,1 };
	int relativeB3[5][2] = { 4,1,3,0,2,1,2,3,1,4 };
	int realB3[5][2] = { 4,1,4,0,3,0,3,1,2,1 };
	int A4[7][2] = {8,6,7,6,7,5,6,5,6,6,5,6,5,5};
	int relativeB4[7][2] = {3,3,4,4,5,5,7,5,8,4,9,5,8,6};
	int realB4[7][2] = {3,3,3,4,4,4,5,4,6,4,6,5,5,5};
	int A5[7][2] = {3,9,3,8,4,8,5,8,5,7,5,6,5,5};
	int relativeB5[7][2] = {2,2,3,3,2,4,1,5,1,7,2,8,3,9};
	int realB5[7][2] = {2,2,3,2,3,3,3,4,3,5,4,5,5,5};
public:
	int*** getTopic(int num);
	void freeMemory(int n);
};
void game(int stepNum, int size,int level);
void SolidMode();
int mouseMsg(int start,ExMessage* msg, int& n, int** ans, int** realB, int size, int stepNum, int x1, int y1, int x2, int y2);
