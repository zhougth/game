#pragma once
#include"game.h"
#include"players.h"
int*** random(int n, int** A, int** realB, int** relativeB, int*** total);
void Random(int n,players& player);
int randomMsg(int start,ExMessage* msg, int** ans, int** realB, int& n, int stepNum);
bool isDeadEnd(int x, int y, int** visited, int directionx[4], int directiony[4]);
void freeMemory(int n, int** A, int** realB, int** relativeB, int*** total);
bool judgeIn(int x, int y, int i, int j);
void showRelativeB(int** relativeB, int size, int stepNum);