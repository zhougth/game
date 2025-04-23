#include"game.h"
#include<string>
#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<ctime>
#include<stdlib.h>
using namespace std;
int*** solidTopic:: getTopic(int num) {
		switch (num) {
		case 1: {
			total = new int** [3]; 
			for (int i = 0; i < 3; i++) {
				total[i] = new int* [3]; 
				for (int j = 0; j < 3; j++) {
					total[i][j] = new int[2];
				}
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 2; j++) {
					total[0][i][j] = A1[i][j];
				}
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 2; j++) {
					total[1][i][j] = relativeB1[i][j];
				}
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 2; j++) {
					total[2][i][j] = realB1[i][j];
				}
			}
			return total;
		}
		case 2: {
			total = new int** [3];
			for (int i = 0; i < 3; i++) {
				total[i] = new int* [5];
				for (int j = 0; j < 5; j++) {
					total[i][j] = new int[2];
				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					total[0][i][j] = A2[i][j];
				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					total[1][i][j] = relativeB2[i][j];
				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					total[2][i][j] = realB2[i][j];
				}
			}
			return total;
		}
		case 3: {
			total = new int** [3];
			for (int i = 0; i < 3; i++) {
				total[i] = new int* [5];
				for (int j = 0; j < 5; j++) {
					total[i][j] = new int[2];
				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					total[0][i][j] = A3[i][j];
				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					total[1][i][j] = relativeB3[i][j];
				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					total[2][i][j] = realB3[i][j];
				}
			}
			return total;
		}
		}
	}
void solidTopic::freeMemory(int n) {
		// 释放内存
		int num = 0;
		switch (n) {
		case 1: {
			num = 3;
			break;
		}
		case 2: {
			num = 5;
			break;
		}
		case 3: {
			num = 5;
			break;
		}
		default: {
			num = 10;
			break;
		}
		}
		cout <<"num=="<< num << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < num; j++) {
				delete[] total[i][j];
			}
			delete[] total[i];
		}
		delete[] total;
		total = NULL;
	}
void button::setColor(COLORREF colorr) {
	color = colorr;
}
void button::setNum(int numm) {
	num = numm;
}
void button::creatButtom(int x, int y, int width, int heigth, COLORREF color, string pText="", int num = 0) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->heigth = heigth;
	this->color = color;
	this->pText = pText;
	this->num = num;
}
void button::drawButtom(int size=35) {
	setfillcolor(this->color);
	settextstyle(size, 0, "楷体");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->heigth);
	outtextxy(this->x + 20, this->y + 10, this->pText.c_str());
}
void button::drawGameButtom(int size=35) {//35
	setfillcolor(this->color);
	settextstyle(size, 0, "楷体");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->heigth);
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", num);
	if(num!=0)outtextxy(this->x + this->width/2-size/2, this->y + this->heigth/2-size/2, buffer);
}
void button::drawOverButtom() {
	setfillcolor(this->color);
	settextstyle(40, 0, "楷体");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->heigth);
	outtextxy(this->x + 75, this->y + 60, this->pText.c_str());
	settextstyle(30, 0, "楷体");
	outtextxy(this->x + 20, this->y + 110, "（请按此按钮返回）");
}
int button::mouseInButtom(MOUSEMSG m) {
	if (this->x <= m.x && this->x + this->width >= m.x && this->y <= m.y && this->y + this->heigth >= m.y) {
		this->color = RED;
		return 1;
	}
	this->color = YELLOW;
	return 0;
}
void button::gameButton(MOUSEMSG m, string str) {
	if (this->x <= m.x && this->x + this->width >= m.x && this->y <= m.y && this->y + this->heigth >= m.y && m.uMsg == WM_LBUTTONDOWN) {
		this->color = RED;
		this->pText = str;
		return;
	}
}
int button::clickButtom(MOUSEMSG m) {
	if (mouseInButtom(m) && m.uMsg == WM_LBUTTONDOWN) {
    return 1;
    }
	return 0;
}
int timer1() {
	int startTime = 0;
	startTime = clock();
	return startTime;
}
void timer2(int startTime) {
	int durTime = clock() - startTime;
	int min = durTime / 1000 / 60;
	int sec = durTime / 1000 % 60;
	char bufferm[20];
	char buffers[20];
	snprintf(bufferm, sizeof(bufferm), "%d", min);
	snprintf(buffers, sizeof(buffers), "%d", sec);
	IMAGE time;
	loadimage(&time, _T("off.jpg"), 300, 100);
	putimage(80, 550+50, &time);
	if (min < 10) {
		outtextxy(180, 570+50, "0");
	}
	outtextxy(100 + 100, 570 + 50, bufferm);
	outtextxy(220, 570 + 50, ":");
	if (sec < 10) {
		outtextxy(250, 570 + 50, "0");
		outtextxy(270, 570 + 50, buffers);
	}
	else {
		outtextxy(250, 570 + 50, buffers);
	}

}
bool check(int **a, int **b, int n) {
	for (int i = 0; i < n; i++) {
		if (a[i][0] == b[i][0] && a[i][1] == b[i][1]) {
			continue;
		}
		else return false;
	}
	return true;
}
bool mouseMsg(ExMessage* msg, int& n, int** ans, int** realB, int size , int stepNum ,int x1,int y1,int x2,int y2) {
	if ((msg->x) > (x2) || (msg->y) > (y2)||(msg->x)<x1||(msg->y)<y1) {
		return false;
	}
	cout << "x=" << msg->x << "  " << "y=" << msg->y << endl;
	int j = (msg->x - x1) / ((x2-x1)/(size));//列
	int i = (msg->y - y1) / ((x2 - x1) / (size));//行
	cout << "i=" << i << "  " << "j=" << j << endl;
	ans[n - 1][0] = i;
	ans[n - 1][1] = j;
	IMAGE ON;
	IMAGE win, lose;
	loadimage(&win, _T("win.png"), 350, 200);
	loadimage(&lose, _T("lose.png"), 350, 200);
	loadimage(&ON, _T("on.jpg"), ((x2 - x1) / (size)), ((x2 - x1) / (size)));
	cout << "(x2 - x1) / (size)==" << (x2 - x1) / (size) << endl;
	putimage(x1 + j * ((x2 - x1) / (size)), y1 + ((x2 - x1) / (size)) * i, &ON);
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", n);
	outtextxy(x1 + j * ((x2 - x1) / (size)) + ((x2 - x1) / (size)) / 2 - 18,y1 + ((x2 - x1) / (size)) * i + ((x2 - x1) / (size)) / 2 - 18, buffer);
	n++;

	if (check(ans, realB, stepNum)) {
		putimage(180 + 400, 100 + 200, &win);
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 580 && m.x <= 880+50 && m.y >= 300 && m.y <= 500) {

				return true;
			}
		}
	}
	else if (n > stepNum) {
		putimage(180 + 400, 100 + 200, &lose);
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 580 && m.x <= 880+50 && m.y >= 300 && m.y <= 500) {
				return true;
			}
		}
	}
	else return false;
}
void retreat(int& n, int** ans, int** realB, int size, int stepNum, int x1, int y1, int x2, int y2) {
	if (n >= 2) {
		IMAGE off;
		loadimage(&off, _T("off.jpg"), ((x2 - x1) / (size)), ((x2 - x1) / (size)));
		putimage(x1 + ans[n - 2][1] * ((x2 - x1) / (size)), y1 + ((x2 - x1) / (size)) * ans[n - 2][0], &off);
		n--;
	}     
	else return;
}
void game(int stepNum,int size,int level) {
	IMAGE mPlay;
	loadimage(&mPlay, _T("bk.jpg"), 1920, 900);
	putimage(0, 0, &mPlay);
	solidTopic solidtopic;
	int **ans=new int *[stepNum];
	for (int i = 0; i < stepNum; i++) {
		ans[i] = new int[2];
	}
	int a = 0, b = 0;
	IMAGE OFF;
	IMAGE ON;	
	switch (level) {

	case 0: {
		loadimage(&ON, _T("on.jpg"), 100, 100);
		loadimage(&OFF, _T("off.jpg"), 100, 100);
		int*** total = solidtopic.getTopic(1);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				putimage(180 + 400 + j * 100, 100 + 100 * i, &OFF);
				putimage(180 + 300 + 450 + j * 100, 100 + 100 * i, &OFF);
			}
		}
		for (int i = 0; i < size; i++) {
			char buffera[20];
			char bufferb[20];
			snprintf(buffera, sizeof(buffera), "%d", a + 1);
			snprintf(bufferb, sizeof(bufferb), "%d", b + 1);
			putimage(180 + 400 + total[0][i][1] * 100, 100 + 100 * total[0][i][0], &ON);
			putimage(180 + 300 + 450 + total[1][i][1] * 100, 100 + 100 * total[1][i][0], &ON);
			outtextxy(180 + 400 + total[0][i][1] * 100 + 30, 100 + 100 * total[0][i][0] + 30, buffera);
			outtextxy(180 + 300 + 450 + total[1][i][1] * 100 + 30, 100 + 100 * total[1][i][0] + 30, bufferb);
			a++;
			b++;
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				putimage(180 + 50 + j * 100, 100 + 100 * i, &OFF);
			}
		}
		int num = 1;
		IMAGE back;
		loadimage(&back, _T( "on.jpg"),300,100);
		putimage(810, 600, &back);
		settextstyle(40, 0, "楷体");
		outtextxy(850, 650, "后退");
		int start = timer1();
		
		while (1) {
			BeginBatchDraw();
			timer2(start);
			ExMessage msg;
			int** step = new int* [stepNum];
			for (int i = 0; i < stepNum; i++) {
				step[i] = new int[2];
			}
			EndBatchDraw();
			drawReturn();
			while (peekmessage(&msg, EM_MOUSE)) {
				
				switch (msg.message) {
				case WM_LBUTTONDOWN: {
					if (mouseMsg(&msg, num, ans, total[2], 3, 3, 50 + 180, 100, 180 + 350, 400)) {
						solidtopic.freeMemory(1);
						drawNext();
						drawReturn();
						while (peekmessage(&msg, EM_MOUSE)) {
							
							if (inNext(msg)) {
								game(5, 5, 1);
								return;
							}
							else if (inReturn(msg)) {
								return;
							}
						}
						
						return;
					}
					else if (msg.x >= 810 && msg.x <= 810 + 300 && msg.y >= 600 && msg.y <= 700) {
						retreat(num, ans, total[2], 3, 3, 50 + 180, 100, 180 + 350, 400);
					}
					else if (inReturn(msg)) {
						return;
					}
					break;
				}
				}
				
			}
		
		}
		break;
	}
	case 1: 
	case 2:{
		loadimage(&ON, _T("on.jpg"), 60, 60);
		loadimage(&OFF, _T("off.jpg"), 60, 60);

		int*** total = solidtopic.getTopic(2);
		if (level == 2)total = solidtopic.getTopic(3);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				putimage(150 + 400 + j * 60, 100 + 60 * i, &OFF);
				putimage(150 + 400 + 400 + j * 60, 100 + 60 * i, &OFF);
			}
		}
		for (int i = 0; i < size; i++) {
			char buffera[20];
			char bufferb[20];
			snprintf(buffera, sizeof(buffera), "%d", a + 1);
			snprintf(bufferb, sizeof(bufferb), "%d", b + 1);
			putimage(150 + 400 + total[0][i][1] * 60, 100 + 60 * total[0][i][0], &ON);
			putimage(150 + 400 + 400 + total[1][i][1] * 60, 100 + 60 * total[1][i][0], &ON);
			outtextxy(150 + 400 + total[0][i][1] * 60 + 10, 100 + 60 * total[0][i][0] + 10, buffera);
			outtextxy(150 + 400 + 400 + total[1][i][1] * 60 + 10, 100 + 60 * total[1][i][0] + 10, bufferb);
			a++;
			b++;
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				putimage(150 + j * 60, 100 + 60 * i, &OFF);
			}
		}//答题区域
		int num = 1;
		IMAGE back;
		loadimage(&back, _T("on.jpg"), 300, 100);
		putimage(1000, 700, &back);
		settextstyle(40, 0, "楷体");
		outtextxy(1100, 725, "后退");
		int start = timer1();
		drawReturn();
		while (1) {
			BeginBatchDraw();
			timer2(start);
			ExMessage msg;
			EndBatchDraw();
			while (peekmessage(&msg, EM_MOUSE)) {
				switch (msg.message) {
				case WM_LBUTTONDOWN: {
					if (mouseMsg(&msg, num, ans, total[2], 5, 5, 150, 100, 450, 400)) {
						solidtopic.freeMemory(2);
						return;
					}
					else if (msg.x >= 1000 && msg.x <= 1000 + 300 && msg.y >= 700 && msg.y <= 800) {
						retreat(num, ans, total[2], 5, 5, 150, 100, 450, 400);
					}
					else if (inReturn(msg)) {
						return;
					}
					break;
				}
				}
			}
		}
		break;
	}

	}
	
}
void Random(int n) {//n指的是步数
	IMAGE mPlay;
	loadimage(&mPlay, _T("test.jpg"), 1920, 1000);
	putimage(0, 0, &mPlay);
	int** A = new int* [n * 5];
	int** realB = new int* [n * 5];
	int** relativeB = new int* [n * 5];
	int*** total = new int** [3];
	for (int i = 0; i < 3; i++) {
		total[i] = nullptr;
	}
	bool ck = false;
	do{
		total = random(n / 5, A, realB, relativeB, total);	
		ck = false;
		for (int i = 0; i < n; i++) {
			if (!(judgeIn(10, 10, total[1][i][0], total[1][i][1]))) {
				ck = true;
			}
		}
	} while (ck);
	cout << "A" << endl;
	for (int i = 0; i <  n; i++) {
		cout << total[0][i][0]+1 << "  " << total[0][i][1]+1 << endl;
	}
	cout << "relativeB" << endl;
	for (int i = 0; i < n; i++) {
		cout << total[1][i][0]+1 << "  " << total[1][i][1]+1 << endl;
	}
	cout << "realB" << endl;
	for (int i = 0; i < n; i++) {
		cout << total[2][i][0]+1 << "  " << total[2][i][1]+1 << endl;
	}
	//上面是获取题目以及答案
	IMAGE ON, OFF;
	loadimage(&ON, _T("on.jpg"), 40, 40);
	loadimage(&OFF, _T("off.jpg"), 40, 40);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			putimage(40+40 + j * 40, 90 + 40 * i, &OFF);
			putimage(40 + 520 + j * 40, 90 + 40 * i, &OFF);
			putimage(40 + 60 + 940 + j * 40, 90 + 40 * i, &OFF);
		}
	}
	int a = 1, b = 1;
	for (int i = 0; i < n; i++) {
		putimage(40 + 520 + total[0][i][1] * 40, 90 + 40 * total[0][i][0], &ON);
		settextstyle(20, 0, "楷体");
		char buffer[20];
		snprintf(buffer, sizeof(buffer), "%d", i + 1);
		outtextxy(40 + 520 + total[0][i][1] * 40+10, 90 + 40 * total[0][i][0]+10, buffer);//A的实际轨迹
		if (i >0) {
			if (total[1][i][0] == total[1][i - 1][0] && total[1][i][1] == total[1][i - 1][1]) {
				settextcolor(RED);
			}
		}
		putimage(40 + 60 + 940 + total[1][i][1] * 40, 90 + 40 * total[1][i][0], &ON);
		outtextxy(40 + 60 + 940 + total[1][i][1] * 40+10, 90 + 40 * total[1][i][0]+10, buffer);
		settextcolor(BLACK);
	}
	int** ans = new int* [n];
	for (int i = 0; i < n; i++) {
		ans[i] = new int[2];
	}
	int num = 1;
	IMAGE back;
	loadimage(&back, _T("on.jpg"), 300, 100);
	putimage(1000, 700, &back);
	settextstyle(40, 0, "楷体");
	outtextxy(1100, 725, "后退");
	int start = timer1();
	while (1) {
		BeginBatchDraw();
		timer2(start);
		ExMessage msg;	
		EndBatchDraw();
		drawReturn();
		while (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN: {
				if (randomMsg(&msg,ans,realB,num,n)) {
					freeMemory(n / 5, A, realB, relativeB, total);
					return;
				}
				else if (msg.x >= 1000 && msg.x <= 1000 + 300 && msg.y >= 700 && msg.y <= 800) {
					retreat(num, ans, realB,10, n, 40, 90, 440, 490);
				}
				else if (inReturn(msg)) {
					return;
				}
				break;
			}
			}
		}

	}
}
bool randomMsg(ExMessage *msg,int **ans,int **realB, int& n, int stepNum ) {
	if ((msg->x<80)||(msg->x) > (40 + 40 + 9 * 40+40) || (msg->y) > ( 90 + 40 * 9+40)||(msg->y<90)) {
		return false;
	}
	cout << msg->x << "  " << msg->y << endl;
	int j = (msg->x - 80) / 40;//列
	int i = (msg->y - 90) / 40;//行
	cout << "i=" << i << "  " << "j=" << j << endl;
	ans[n - 1][0] = i;
	ans[n - 1][1] = j;
	IMAGE ON;
	loadimage(&ON, _T("on.jpg"), 40, 40);
	putimage(40 + 40 + j * 40, 90 + 40 * i, &ON);
	settextstyle(20, 0, "楷体");
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", n);
	outtextxy(40 + 40 + j * 40+10, 90 + 40 * i+10, buffer);
	n++;
	IMAGE win, lose;
	loadimage(&win, _T("win.png"), 350, 200);
	loadimage(&lose, _T("lose.png"), 350, 200);
	if (check(ans, realB, stepNum)) {
		putimage(180 + 400, 100 + 200, &win);
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 580 && m.x <= 880 + 50 && m.y >= 300 && m.y <= 500) {
				return true;
			}
		}
	}
	else if (n > stepNum) {
		putimage(180 + 400, 100 + 200, &lose);
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 580 && m.x <= 880 + 50 && m.y >= 300 && m.y <= 500) {
				return true;
			}
		}
	}
	else return false;
}
void menu() {
	initgraph(1820, 800);
	IMAGE mm;
	loadimage(&mm, _T("bk.jpg"), 1820, 800);
	putimage(0, 0, &mm);
	//加载背景
	button* play = new button;
	button* rule = new button;
	button* quit = new button;
	button* solidMode = new button;
	button* randomMode = new button;
	button* Return = new button;
	play->creatButtom(440, 340, 180, 50, YELLOW, "开始游戏");
	rule->creatButtom(440, 395, 180, 50, YELLOW, "游戏规则");
	quit->creatButtom(440, 450, 180, 50, YELLOW, "退出游戏");
	solidMode->creatButtom(440, 340, 180, 50, YELLOW, "关卡模式");
	randomMode->creatButtom(440, 395, 180, 50, YELLOW, "随机模式");
	Return->creatButtom(440, 450, 180, 50, YELLOW, "返回");   
	IMAGE mPlay;
	loadimage(&mPlay, _T("bk.jpg"), 1820, 800);
	IMAGE mPlay2;
	loadimage(&mPlay2, _T("bk.jpg"), 1820, 800);
	while (1) {
		BeginBatchDraw();
		play->drawButtom();
		rule->drawButtom();
		quit->drawButtom();
		EndBatchDraw();
		MOUSEMSG m = GetMouseMsg();	
		if (play->clickButtom(m)) {			
			putimage(0, 0, &mPlay);			
			while(1){	
				putimage(0, 0, &mPlay2);
				BeginBatchDraw();
				solidMode->drawButtom();
				randomMode->drawButtom();
				Return->drawButtom();
				EndBatchDraw();
				MOUSEMSG m1 = GetMouseMsg();
				if (solidMode->clickButtom(m1)) {
					SolidMode();
				}
				if (randomMode->clickButtom(m1)) {
					Random(5);
				}
				if (Return->clickButtom(m1)) {
					break;
				}
				
			}
		}
		if (rule->clickButtom(m)) {

		}
		if (quit->clickButtom(m)) {
			delete play;
			delete rule;
			delete quit;
			delete solidMode;
			delete randomMode;
			delete Return;
			return;
		}	
	}
	delete play;
	delete rule;
	delete quit;
	closegraph();
}
bool judgeIn(int x, int y, int i, int j) {//x和y是题目表格大小，i和j是坐标
	if (i <= x && i >= 0 && j <= y && j >= 0) {
		return true;
	}
	else return false;
}
bool isDeadEnd(int x, int y, int** visited, int directionx[4], int directiony[4]) {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		int nextX = x + directionx[i];
		int nextY = y + directiony[i];
		if (!judgeIn(10, 10, nextX, nextY) || visited[nextX][nextY]) {
			count++;
		}
	}
	return count == 4; // 如果四个方向都被堵死，则是死胡同
}
int*** random(int n,int **A,int**realB,int**relativeB,int***total) {//5的n倍步
	srand((unsigned int)time(NULL));
	int directionx[4] = { -1,0,1,0 };
	int directiony[4] = { 0,1,0,-1 };
	for (int i = 0; i < n * 5; i++) {
		A[i] = new int[2];
		realB[i] = new int[2];
		relativeB[i] = new int[2];
	}//创建航迹
	int** visitA = new int* [10];
	int** visitB = new int* [10];
	for (int i = 0; i < 10; i++) {
		visitA[i] = new int[10];
		visitB[i] = new int[10];
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0;j < 10; j++) {
			visitA[i][j] = 0;
			visitB[i][j] = 0;
		}
	}
	int startx = (rand() % 5);
	int starty = (rand() % 5);
	A[n * 5 - 1][0] = startx ;
	realB[n * 5 - 1][0] = startx ;
	A[n * 5 - 1][1] = starty ;
	realB[n * 5 - 1][1] = starty ;
	int* Adir = new int[n * 5];
	int* Bdir = new int[n * 5];
	visitA[startx][starty] = 1;
	for (int i = n * 5 - 2; i >= 0; i--) {
		int prevAdir = (i == n * 5 - 2) ? -1 : Adir[i + 1]; // 上一次的方向
		int prevBdir = (i == n * 5 - 2) ? -1 : Bdir[i + 1]; // 上一次的方向
		bool foundValidPath = false;
		int nextAx, nextAy, nextBx, nextBy;
		while (!foundValidPath) {
			// 生成 A 的方向，排除与上一次相反的方向
			do {
				Adir[i] = rand() % 4;
				nextAx = A[i + 1][0] + directionx[Adir[i]];
				nextAy = A[i + 1][1] + directiony[Adir[i]];
			} while(!judgeIn(10, 10, nextAx, nextAy) || (prevAdir != -1 && (Adir[i] + 2) % 4 == prevAdir));
			// 生成 realB 的方向，排除与上一次相反的方向
			do {
				Bdir[i] = rand() % 4;
				nextBx = realB[i + 1][0] + directionx[Bdir[i]];
				nextBy = realB[i + 1][1] + directiony[Bdir[i]];
			} while (!judgeIn(10, 10, nextBx, nextBy) ||(prevBdir != -1 && (Bdir[i] + 2) % 4 == prevBdir));
			// 更新 A 的位置
			nextAx = A[i + 1][0] + directionx[Adir[i]];
			nextAy = A[i + 1][1] + directiony[Adir[i]];
			if (judgeIn(10, 10, nextAx, nextAy) && !visitA[nextAx][nextAy]) {
				A[i][0] = nextAx;
				A[i][1] = nextAy;
				visitA[nextAx][nextAy] = 1;
				// 检查是否会走进死胡同
				if (!isDeadEnd(nextAx, nextAy, visitA, directionx, directiony)) {
					foundValidPath = true;
				}
				else {
					// 如果是死胡同，回溯
					visitA[nextAx][nextAy] = 0;
				}
			}
			// 更新 realB 的位置
			int nextBx = realB[i + 1][0] + directionx[Bdir[i]];
			int nextBy = realB[i + 1][1] + directiony[Bdir[i]];
			if (judgeIn(10, 10, nextBx, nextBy) && !visitB[nextBx][nextBy]) {
				realB[i][0] = nextBx;
				realB[i][1] = nextBy;
				visitB[nextBx][nextBy] = 1;
				// 检查是否会走进死胡同
				if (!isDeadEnd(nextBx, nextBy, visitB, directionx, directiony)) {
					foundValidPath = true;
				}
				else {
					// 如果是死胡同，回溯
					visitB[nextBx][nextBy] = 0;
					continue;
				}
			}
			else continue;
		}
	}
	relativeB[0][0] = realB[0][0];
	relativeB[0][1] = realB[0][1];
	for (int i = 1; i < n * 5; i++) {
		relativeB[i][0] = relativeB[i - 1][0] + directionx[Adir[i - 1]] + (-1) * directionx[Bdir[i - 1]];
		relativeB[i][1] = relativeB[i - 1][1] + directiony[Adir[i - 1]] + (-1) * directiony[Bdir[i - 1]];
	}
	total[0] = A;
	total[1] = relativeB;
	total[2] = realB;
	delete[]Adir;
	delete[]Bdir;
	for (int i = 0; i < 10; i++) {
		delete visitA[i];
		delete visitB[i];
	}
	delete[] visitA;
	delete[] visitB;
	return total;
}
void freeMemory(int n,int** A, int** realB, int** relativeB, int*** total) {
	for (int i = 0; i < n * 5; i++) {
		delete[]A[i];
		delete[]realB[i];
		delete[]relativeB[i];
	}
	delete[]A;
	delete[]realB;
	delete[]relativeB;
	delete[]total;
}
void SolidMode() {
	IMAGE mm;
	loadimage(&mm, _T("test.jpg"), 1920, 900);
	putimage(0, 0, &mm);
	button **level=new button*[6];
	for (int i = 0; i < 6; i++) {
		level[i] = new button;
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			level[i * 3 + j]->creatButtom(100 + j * 400, 100 + 400 * i, 250, 250, YELLOW, " ", i * 3 + j + 1);
			level[i * 3 + j]->drawGameButtom(50);
		}
	}
	button* Return = new button;
	Return->creatButtom(1200, 600, 250, 150,RED);
	Return->drawButtom(50);
	outtextxy(1300, 650, "返回");
	while (1) {
		MOUSEMSG m = GetMouseMsg();
		if (level[0]->clickButtom(m)) {
			game(3,3,0);
			break;
		}
		if (level[1]->clickButtom(m)) {
			game(5, 5,1);
			break;
		}
		if (level[2]->clickButtom(m)) {
			game(5, 5,2);
			break;
		}
		if (Return->clickButtom(m)) {
			for (int i = 0; i < 6; i++) {
				delete level[i];
			}
			delete []level;
			delete Return;
			return;
		}
	}
	return;
}
void drawReturn() {
	IMAGE Return;
	loadimage(&Return, _T("on.jpg"), 300, 100);
	putimage(80+400, 550 + 50, &Return);
	outtextxy(500, 620, "退出");
}
bool inReturn(ExMessage m) {
	if (m.x >= 480 && m.x <= 780 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
void drawNext() {
	IMAGE Return;
	loadimage(&Return, _T("off.jpg"), 300, 100);
	putimage(80 + 400+400, 550 + 50, &Return);
	outtextxy(500+400, 620, "继续");
}
bool inNext(ExMessage m) {
	if (m.x >= 480+400 && m.x <= 780+400 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
