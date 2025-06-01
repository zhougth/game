#pragma once
#include"game.h"
#include"players.h"
class solidTopic {
private:
	int*** total;
public:
	int*** getTopic(int num);
	void freeMemory(int n);
};
void game(int stepNum, int size,int level,players& Player);
void SolidMode(players& Player);
int mouseMsg(int start,ExMessage* msg, int& n, int** ans, int** realB, int size, int stepNum, int x1, int y1, int x2, int y2);
