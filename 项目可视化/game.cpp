#include"game.h"
#include"solidMode.h"
#include"randomMode.h"
using namespace std;
void button::setColor(COLORREF colorr) {
	color = colorr;
}
void button::setNum(int numm) {
	num = numm;
}
void button::creatButtom(int x, int y, int width, int heigth, COLORREF color, string pText, int num) {
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
void retreat(int& n, int** ans, int** realB, int size, int stepNum, int x1, int y1, int x2, int y2) {
	if (n >= 2) {
		IMAGE off;
		loadimage(&off, _T("off.jpg"), ((x2 - x1) / (size)), ((x2 - x1) / (size)));
		putimage(x1 + ans[n - 2][1] * ((x2 - x1) / (size)), y1 + ((x2 - x1) / (size)) * ans[n - 2][0], &off);
		n--;
	}     
	else return;
}
bool checkIn(MOUSEMSG m,int x1,int y1,int x2,int y2) {
	if (m.x >= x1 && m.x <= x2 && m.y >= y1 && m.y <= y2 && m.uMsg == WM_LBUTTONDOWN) {
		return true;
	}
	return false;
}
void menu() {
	initgraph(1500, 800);
	IMAGE mm;
	loadimage(&mm, _T("脑力航迹.jpg"), 1500, 800);
	//加载背景
	IMAGE Start, Rule,Re;
	loadimage(&Start, _T("开始游戏.png"), 200, 80);
	loadimage(&Rule, _T("游戏规则.png"), 200, 80);
	loadimage(&Re, _T("退出游戏.png"), 200, 80);
	IMAGE Solid, Ra, Bk;
	loadimage(&Solid, _T("关卡模式.png"), 200, 80);
	loadimage(&Ra, _T("随机模式.png"), 200, 80);
	loadimage(&Bk, _T("返回.png"), 200, 80);
	IMAGE mPlay;
	loadimage(&mPlay, _T("脑力航迹.jpg"), 1500, 800);
	IMAGE mPlay2;
	loadimage(&mPlay2, _T("脑力航迹.jpg"), 1500, 800);
	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		putimage(625, 400, &Start);
		putimage(625, 500, &Rule);
		putimage(625, 600, &Re);
		EndBatchDraw();
		MOUSEMSG m = GetMouseMsg();	
		if (checkIn(m,625,400,825,480)) {			
			while(1){		
				putimage(0, 0, &mPlay);
				putimage(0, 0, &mPlay2);
				BeginBatchDraw();
				putimage(625, 400, &Solid);
				putimage(625, 500, &Ra);
				putimage(625, 600, &Bk);
				EndBatchDraw();
				MOUSEMSG m1 = GetMouseMsg();
				if (checkIn(m1, 625, 400, 825, 480)) {
					SolidMode();
				}
				if (checkIn(m1, 625, 500, 825, 580)) {
					Random(5);
				}
				if (checkIn(m1, 625, 600, 825, 680)) {
					break;
				}
			}
		}
		if (checkIn(m,625,500,825,580)) {//规则
			IMAGE rule;
			loadimage(&rule, _T("规则.png"), 1500, 800);
			putimage(0, 0, &rule);
			IMAGE bk;
			loadimage(&bk,_T("返回.png"),180,80);
			putimage(1300, 700, &bk);
			while (1) {
				MOUSEMSG m = GetMouseMsg();
				if (checkIn(m, 1300, 700, 1480, 780)) {
					break;
				}
			};
		}
		if (checkIn(m,625,600,825,680)) {//退出游戏
			return;
		}	
	}
	closegraph();
}
void drawReturn() {
	IMAGE Return;
	loadimage(&Return, _T("on.jpg"), 300, 100);
	putimage(80+400, 550 + 50, &Return);
	settextstyle(40, 0, "楷体");
	outtextxy(600, 620, "退出");
}
bool inReturn(ExMessage m) {
	if (m.x >= 480 && m.x <= 780 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
bool inReturn(MOUSEMSG m) {
	if (m.x >= 480 && m.x <= 780 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
void drawNext() {
	IMAGE Return;
	loadimage(&Return, _T("off.jpg"), 300, 100);
	putimage(80 + 400+400, 550 + 50, &Return);
	settextstyle(40, 0, "楷体");
	outtextxy(500+400, 620, "继续");
}
bool inNext(ExMessage m) {
	if (m.x >= 480+400 && m.x <= 780+400 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
bool inNext(MOUSEMSG m) {
	if (m.x >= 480 + 400 && m.x <= 780 + 400 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
void drawRetreat() {
	IMAGE Retreat;
	loadimage(&Retreat, _T("on.jpg"), 300, 100);
	putimage(1280, 550 + 50, &Retreat);
	settextstyle(40, 0, "楷体");
	outtextxy(1400, 620, "后退");
}
bool inRetreat(MOUSEMSG m) {
	if (m.x >= 1280 && m.x <= 1280 + 300 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
bool inRetreat(ExMessage m) {
	if (m.x >= 1280 && m.x <= 1280 + 300 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
bool ifOpen(int** ans, int step, int i, int j) {
	for (int k = 0; k < step; k++) {
		if (ans[k][0] == i && ans[k][1] == j) {
			return true;
		}
	}
	return false;
}