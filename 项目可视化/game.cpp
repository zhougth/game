#include"game.h"
#include<string>
#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<ctime>
using namespace std;
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
	loadimage(&ON, _T("on.jpg"), ((x2 - x1) / (size)), ((x2 - x1) / (size)));
	putimage(x1 + j * ((x2 - x1) / (size)), y1 + ((x2 - x1) / (size)) * i, &ON);
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", n);
	outtextxy(x1 + j * ((x2 - x1) / (size)) + ((x2 - x1) / (size)) / 2 - 18,y1 + ((x2 - x1) / (size)) * i + ((x2 - x1) / (size)) / 2 - 18, buffer);
	n++;

	if (check(ans, realB, stepNum)) {
		return true;
	}
	else if (n > stepNum) {
		button* End = new button;
		End->creatButtom(180+400, 100+200, 300, 200, YELLOW, "游戏失败");
		End->drawOverButtom();
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (End->clickButtom(m)) {
				delete End;
				return true;
			}
		}

	}
	else return false;
}
void game(int stepNum,int size) {
	IMAGE mPlay;
	loadimage(&mPlay, _T("bk.jpg"), 1920, 900);
	putimage(0, 0, &mPlay);
	int A[3][2] = { 2,0,1,0,1,1 };
	int relativeB[3][2] = { 0,2,2,2,2,0 };
	int** realB = new int* [stepNum];
	for (int i = 0; i < stepNum; i++) {
		realB[i] = new int[2];
	}
	realB[0][0] = 0;
	realB[0][1] = 2;
	realB[1][0] = 1;
	realB[1][1] = 2;
	realB[2][0] = 1;
	realB[2][1] = 1;
	int **ans=new int *[stepNum];
	for (int i = 0; i < stepNum; i++) {
		ans[i] = new int[2];
	}
	button** block = new button * [size];
	for (int i = 0; i < size; i++) {
		block[i] = new button[size];
	}
	int a = 0, b = 0;
	IMAGE OFF;
	IMAGE ON;
	loadimage(&ON, _T("on.jpg"), 100, 100);
	loadimage(&OFF, _T("off.jpg"),100,100);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			/*setfillcolor(BLUE);
			bar(400 + j * 102, 100 + 102 * i, 400 + j * 102+ 100, 100 + 102 * i+ 100);
			bar(300 + 450 + j * 102, 100 + 102 * i, 100 + 300 + 450 + j * 102, 100 + 100 + 102 * i);*/
			putimage(180+400 + j * 100, 100 + 100 * i, &OFF);
			putimage(180+300 + 450 + j * 100, 100 + 100 * i, &OFF);
		}
	}
	for (int i = 0; i < 3; i++) {
		char buffera[20];
		char bufferb[20];
		snprintf(buffera, sizeof(buffera), "%d", a+1);
		snprintf(bufferb, sizeof(bufferb), "%d", b + 1);
		/*setfillcolor(RED);
		bar(400 + A[i][1] * 102, 100 + 102 * A[i][0], 400 + A[i][1] * 102 + 98, 100 + 102 * A[i][0] + 98);
		bar(300 + 450 + relativeB[i][1] * 102, 100 + 102 * relativeB[i][0], 98 + 300 + 450 + relativeB[i][1] * 102, 98 + 100 + 102 * relativeB[i][0]);*/
		putimage(180+400 + A[i][1] * 100, 100 + 100 * A[i][0], &ON);
		putimage(180+300 + 450 + relativeB[i][1] * 100, 100 + 100 * relativeB[i][0], &ON);
		outtextxy(180+400 + A[i][1] * 100+30, 100 + 100 * A[i][0]+30, buffera);
		outtextxy(180+300 + 450 + relativeB[i][1] * 100 + 30, 100 + 100 * relativeB[i][0] + 30, bufferb);
		a++;
		b++;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			/*block[i][j].creatButtom(50 + j * 102, 100 + 102 * i, 100, 100, BLUE);
			block[i][j].drawGameButtom();*/
			putimage(180+50 + j * 100, 100 + 100 * i, &OFF);
		}
	}
	int num = 1;
	while (1) {
		ExMessage msg;
		while (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN: {
				if (mouseMsg(&msg,  num, ans, realB,3,3,50+180,100,180+350,400)) {
					for (int i = 0; i < stepNum; i++) {
						delete realB[i];
					}
					delete[] realB;
					return;
				}
				break;
			}
			}
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
			/*setfillcolor(BLUE);
			bar(40 + j * 43, 90 + 43 * i, 40 + j * 43 + 40, 90 + 43 * i + 40);
			bar(520 + j * 43, 90 + 43 * i, 520  + j * 43+40, 90 +43 * i+40);
			bar(60+940 + j * 43, 90 + 43 * i, 940+60 + j * 43 + 40, 90 + 43 * i + 40);*/
			putimage(40 + j * 40, 90 + 40 * i, &OFF);
			putimage(520 + j * 40, 90 + 40 * i, &OFF);
			putimage(60 + 940 + j * 40, 90 + 40 * i, &OFF);
		}
	}
	int a = 1, b = 1;
	for (int i = 0; i < n; i++) {
		/*setfillcolor(RED);
		bar(520 + total[0][i][1] * 43, 90 + 43 * total[0][i][0], 520 + total[0][i][1] * 43 +40, 90 + 43 * total[0][i][0] + 40);
		*/
		
		putimage(520 + total[0][i][1] * 40, 90 + 40 * total[0][i][0], &ON);
		settextstyle(20, 0, "楷体");
		char buffer[20];
		snprintf(buffer, sizeof(buffer), "%d", i + 1);
		outtextxy(520 + total[0][i][1] * 40+10, 90 + 40 * total[0][i][0]+10, buffer);//A的实际轨迹
		if (i >0) {
			if (total[1][i][0] == total[1][i - 1][0] && total[1][i][1] == total[1][i - 1][1]) {
				settextcolor(RED);
			}
		}
		putimage(60 + 940 + total[1][i][1] * 40, 90 + 40 * total[1][i][0], &ON);
		outtextxy(60 + 940 + total[1][i][1] * 40+10, 90 + 40 * total[1][i][0]+10, buffer);
		settextcolor(BLACK);
	}
	int** ans = new int* [n];
	for (int i = 0; i < n; i++) {
		ans[i] = new int[2];
	}
	int num = 1;
	while (1) {
		ExMessage msg;
		while (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN: {
				if (randomMsg(&msg,ans,realB,num,n)) {
					return;
				}
				break;
			}
			}
		}
	}
	freeMemory(n / 5, A, realB, relativeB, total);
	while (1);
}
bool randomMsg(ExMessage *msg,int **ans,int **realB, int& n, int stepNum ) {
	if ((msg->x) > (40 + 9 * 40+40) || (msg->y) > (90 + 40 * 9+40)) {
		return false;
	}
	cout << msg->x << "  " << msg->y << endl;
	int j = (msg->x - 40) / 40;//列
	int i = (msg->y - 90) / 40;//行
	cout << "i=" << i << "  " << "j=" << j << endl;
	ans[n - 1][0] = i;
	ans[n - 1][1] = j;
	/*setfillcolor(RED);
	bar(40 + j * 43, 90 + 43 * i, 40 + j * 43 + 40, 90 + 43 * i + 40);*/
	IMAGE ON;
	loadimage(&ON, _T("on.jpg"), 40, 40);
	putimage(40 + j * 40, 90 + 40 * i, &ON);
	settextstyle(20, 0, "楷体");
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", n);
	outtextxy(40 + j * 40+10, 90 + 40 * i+10, buffer);
	n++;
	if (check(ans, realB, stepNum)) {
		return true;
	}
	else if (n > stepNum) {
		button* End = new button;
		End->creatButtom(400+200, 200+100, 304, 204, YELLOW, "游戏失败");
		End->drawOverButtom();
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (End->clickButtom(m)) {
				delete End;
				return true;
			}
		}

	}
	else return false;
}
void menu() {
	initgraph(1920, 900);
	IMAGE mm;
	loadimage(&mm, _T("bk.jpg"), 1920, 900);
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
	loadimage(&mPlay, _T("bk.jpg"), 1920, 900);
	IMAGE mPlay2;
	loadimage(&mPlay2, _T("bk.jpg"), 1920, 900);
	while (1) {
		play->drawButtom();
		rule->drawButtom();
		quit->drawButtom();
		MOUSEMSG m = GetMouseMsg();	
		if (play->clickButtom(m)) {			
			putimage(0, 0, &mPlay);			
			while(1){				
				putimage(0, 0, &mPlay2);
				solidMode->drawButtom();
				randomMode->drawButtom();
				Return->drawButtom();
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
			game(3,3);
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