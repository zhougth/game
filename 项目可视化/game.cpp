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
	settextstyle(35, 0, "楷体");
	int durTime = clock() - startTime;
	int min = durTime / 1000 / 60;
	int sec = durTime / 1000 % 60;
	char bufferm[20];
	char buffers[20];
	snprintf(bufferm, sizeof(bufferm), "%d", min);
	snprintf(buffers, sizeof(buffers), "%d", sec);
	IMAGE time;
	loadimage(&time, _T("用时.png"), 300, 100);
	putimage(80, 550+50, &time);
	settextcolor(RGB(136,126,101));
	if (min < 10) {
		outtextxy(200 + 20, 570+60, "0");
	}
	outtextxy(100 + 100+20 + 20, 570 + 50+10, bufferm);
	outtextxy(220+20 + 20, 570 + 50+10, ":");
	if (sec < 10) {
		outtextxy(250 + 20 + 20, 570 + 50 + 10, "0");
		outtextxy(270 + 20 + 20, 570 + 50 + 10, buffers);
	}
	else {
		outtextxy(250 + 20 + 20, 570 + 50 + 10, buffers);
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
		loadimage(&off, _T("off.png"), ((x2 - x1) / (size)), ((x2 - x1) / (size)));
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
					Random(10);
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
	loadimage(&Return, _T("退出.png"), 300, 100);
	putimage(40+400, 550 + 50, &Return);
}
bool inReturn(ExMessage m) {
	if (m.x >= 440 && m.x <= 740 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
bool inReturn(MOUSEMSG m) {
	if (m.x >= 440 && m.x <= 740 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
void drawNext() {
	IMAGE Next;
	loadimage(&Next, _T("继续.png"), 300, 100);
	putimage(600, 500, &Next);
}
bool inNext(ExMessage m) {
	if (m.x >= 600 && m.x <= 900 && m.y >= 500 && m.y <= 600) {
		return true;
	}
	else return false;
}
bool inNext(MOUSEMSG m) {
	if (m.x >= 600 && m.x <= 900 && m.y >= 500 && m.y <= 600) {
		return true;
	}
	else return false;
}
void drawRetreat() {
	IMAGE Retreat;
	loadimage(&Retreat, _T("撤回.png"), 300, 100);
	putimage(800, 550 + 50, &Retreat);
}
bool inRetreat(MOUSEMSG m) {
	if (m.x >= 800 && m.x <= 800 + 300 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
bool inRetreat(ExMessage m) {
	if (m.x >= 800 && m.x <= 800 + 300 && m.y >= 600 && m.y <= 700) {
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
int success(int start) {
	IMAGE win;
	loadimage(&win, _T("挑战成功.jpg"), 1500, 800);
	putimage(0, 0, &win);
	IMAGE Continue, returnMenu;
	loadimage(&Continue, _T("继续.png"), 300, 100);
	loadimage(&returnMenu, _T("返回菜单.png"), 300, 100);
	putimage(600, 500, &Continue);
	putimage(600, 650, &returnMenu);
	showTime(start);
	while (1) {
		MOUSEMSG m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (inNext(m)) {
				return 1;
			}
			if (m.x >= 600 && m.x <= 900 && m.y >= 650 && m.y <= 750) {
				return 2;
			}
		}
	}
}
int lose(int start) {
	IMAGE lose;
	loadimage(&lose, _T("挑战失败.jpg"), 1500, 800);
	putimage(0, 0, &lose);
	IMAGE answer, restreat, returnMenu;
	loadimage(&answer, _T("查看答案.png"), 300, 100);
	loadimage(&restreat, _T("重新开始.png"), 300, 100);
	loadimage(&returnMenu, _T("返回菜单.png"), 300, 100);
	putimage(600, 450, &answer);
	putimage(600, 550, &restreat);
	putimage(600, 650, &returnMenu);
	showTime(start);
	while (1) {
		MOUSEMSG m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 600 && m.x <= 900 && m.y >= 450 && m.y <= 550) {
				return 1;
			}
			if (m.x >= 600 && m.x <= 900 && m.y >= 550 && m.y <= 650) {
				return 2;
			}
			if (m.x >= 600 && m.x <= 900 && m.y >= 650 && m.y <= 750) {
				return 3;
			}
		}
	}
	
}
void showTime(int start) {
	settextstyle(40, 0, "楷体");
	int durTime = clock() - start;
	int min = durTime / 1000 / 60;
	int sec = durTime / 1000 % 60;
	char bufferm[20];
	char buffers[20];
	snprintf(bufferm, sizeof(bufferm), "%d", min);
	snprintf(buffers, sizeof(buffers), "%d", sec);
	IMAGE time;
	loadimage(&time, _T("用时.png"), 300, 100);
	putimage(600,350, &time);
	settextcolor(RGB(136, 126, 101));
	if (min < 10) {
		outtextxy(740, 380, "0");
	}
	outtextxy(740+20, 380, bufferm);
	outtextxy(740 + 20 + 20, 380, ":");
	if (sec < 10) {
		outtextxy(740 + 20 + 20 + 20, 380, "0");
		outtextxy(740 + 20 + 20 + 20+20, 380, buffers);
	}
	else {
		outtextxy(740 + 20 + 20+ 20, 380, buffers);
	}
}
int showAns(int stepNum, int size, int*** total) {
	IMAGE mPlay;
	loadimage(&mPlay, _T("背景.jpg"), 1500, 800);
	putimage(0, 0, &mPlay);
	IMAGE OFF;
	IMAGE ON;
	switch (size) {
	case 3: {	
		loadimage(&ON, _T("on.png"), 100, 100);
		loadimage(&OFF, _T("off.png"), 100, 100);
		int a = 0, b = 0,c=0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				putimage(180 + 400 + j * 100, 100 + 100 * i, &OFF);
				putimage(180 + 300 + 450 + j * 100, 100 + 100 * i, &OFF);
				putimage(180 + 50 + j * 100, 100 + 100 * i, &OFF);
			}
		}
		for (int i = 0; i < stepNum; i++) {
			char buffera[20];
			snprintf(buffera, sizeof(buffera), "%d", a + 1);//答案
			putimage(180 + 400 + total[0][i][1] * 100, 100 + 100 * total[0][i][0], &ON);
			putimage(180 + 300 + 450 + total[1][i][1] * 100, 100 + 100 * total[1][i][0], &ON);
			putimage(180 +50 + total[2][i][1] * 100, 100 + 100 * total[2][i][0], &ON);//答案
			outtextxy(180 + 400 + total[0][i][1] * 100 + 30, 100 + 100 * total[0][i][0] + 30, buffera);
			outtextxy(180 + 300 + 450 + total[1][i][1] * 100 + 30, 100 + 100 * total[1][i][0] + 30, buffera);
			outtextxy(180 + 50 + total[2][i][1] * 100+30, 100 + 100 * total[2][i][0]+30, buffera);
			a++;
		}
		break;
	}
	case 5: {
		loadimage(&ON, _T("on.png"), 60, 60);
		loadimage(&OFF, _T("off.png"), 60, 60);
		int a = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				putimage(150 + j * 60, 100 + 60 * i, &OFF);
				putimage(150 + 400 + j * 60, 100 + 60 * i, &OFF);
				putimage(150 + 400 + 400 + j * 60, 100 + 60 * i, &OFF);
			}
		}
		for (int i = 0; i < stepNum; i++) {
			char buffera[20];
			snprintf(buffera, sizeof(buffera), "%d", a + 1);
			putimage(150 + 400 + total[0][i][1] * 60, 100 + 60 * total[0][i][0], &ON);
			putimage(150 + 400 + 400 + total[1][i][1] * 60, 100 + 60 * total[1][i][0], &ON);
			putimage(150 + total[2][i][1] * 60, 100 + 60 * total[2][i][0], &ON);
			outtextxy(150  + total[2][i][1] * 60 + 10, 100 + 60 * total[2][i][0] + 10, buffera);
			outtextxy(150 + 400 + total[0][i][1] * 60 + 10, 100 + 60 * total[0][i][0] + 10, buffera);
			outtextxy(150 + 400 + 400 + total[1][i][1] * 60 + 10, 100 + 60 * total[1][i][0] + 10, buffera);
			a++;
		}
		break;
	}
	case 10: {
		loadimage(&ON, _T("on.png"), 40, 40);
		loadimage(&OFF, _T("off.png"), 40, 40);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				putimage(40 + 40 + j * 40, 90 + 40 * i, &OFF);
				putimage(40 + 520 + j * 40, 90 + 40 * i, &OFF);
				putimage(40 + 60 + 940 + j * 40, 90 + 40 * i, &OFF);
			}
		}
		int a = 1, b = 1;
		for (int i = 0; i < stepNum; i++) {
			putimage(40 + 40 + total[2][i][1] * 40, 90 + 40 * total[2][i][0], &ON);
			putimage(40 + 520 + total[0][i][1] * 40, 90 + 40 * total[0][i][0], &ON);
			settextstyle(20, 0, "楷体");
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", i + 1);
			outtextxy(40 + 520 + total[0][i][1] * 40 + 10, 90 + 40 * total[0][i][0] + 10, buffer);//A的实际轨迹
			if (i > 0) {
				if (total[1][i][0] == total[1][i - 1][0] && total[1][i][1] == total[1][i - 1][1]) {
					settextcolor(RED);
				}
			}
			putimage(40 + 60 + 940 + total[1][i][1] * 40, 90 + 40 * total[1][i][0], &ON);
			outtextxy(40 + 60 + 940 + total[1][i][1] * 40 + 10, 90 + 40 * total[1][i][0] + 10, buffer);
			settextcolor(BLACK);
			outtextxy(40 + 40 + total[2][i][1] * 40+10, 90 + 40 * total[2][i][0]+10, buffer);
		}
	}
	}
	drawReturn();//退出
	IMAGE reStrat;
	loadimage(&reStrat, _T("重新开始.png"), 300, 100);
	putimage(300 + 480 + 40, 600, &reStrat);
	while (1) {
		MOUSEMSG m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (inReturn(m)) {//退出
				return 1;
			}
			else if (m.x >= 300 + 520 && m.x <= 820 + 300 && m.y >= 600 && m.y <= 700) {//重新开始
				return 2;
			}
		}
	}
}
