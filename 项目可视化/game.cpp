#include"game.h"
#include<string>
#include<iostream>
#include<cstdio>
COLORREF& button::getColor() {
	return color;
}
int& button::getNum() {
	return num;
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
void button::drawButtom() {
	setfillcolor(this->color);
	settextstyle(35, 0, "楷体");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->heigth);
	outtextxy(this->x + 20, this->y + 10, this->pText.c_str());
}
void button::drawGameButtom() {
	setfillcolor(this->color);
	settextstyle(35, 0, "楷体");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->heigth);
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", num);
	if(num!=0)outtextxy(this->x + 20, this->y + 10, buffer);
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
bool check(int a[][2], int b[][2], int n) {
	for (int i = 0; i < n; i++) {
		if (a[i][0] == b[i][0] && a[i][1] == b[i][1]) {
			continue;
		}
		else return false;
	}
	return true;
}
bool mouseMsg(ExMessage* msg, button block[][3], int& n, int ans[][2], int realB[][2]) {
	if ((msg->x) > (block[0][2].x + block[0][2].width) || (msg->y) > (block[2][0].y + block[2][0].heigth)) {
		return false;
	}
	int j = (msg->x - 50) / 100;//列
	int i = (msg->y - 100) / 100;//行
	ans[n - 1][0] = i;
	ans[n - 1][1] = j;
	block[i][j].getColor() = RED;
	block[i][j].getNum() = n;
	block[i][j].drawGameButtom();
	n++;
	
	if (check(ans, realB, 3)) {
		return true;
	}
	else if (n >= 4) {
		button* End = new button;
		End->creatButtom(400, 200, 304, 204, YELLOW, "游戏失败");
		End->drawOverButtom();
		
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (End->clickButtom(m))return true;
		}
		
	}
	else return false;
}
void game() {
	IMAGE mPlay;
	loadimage(&mPlay, _T("bk.jpg"), 1024, 684);
	putimage(0, 0, &mPlay);
	int A[3][2] = { 2,0,1,0,1,1 };
	int relativeB[3][2] = { 0,2,2,2,2,0 };
	int realB[3][2] = { 0,2,1,2,1,1 };
	int ans[3][2];
	button block[3][3];
	int a = 0, b = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			/*topicA[i][j].creatButtom(400 + j * 102, 100 + 102 * i, 100, 100, BLUE);
			topicA[i][j].drawGameButtom();*/
			setfillcolor(BLUE);
			bar(400 + j * 102, 100 + 102 * i, 400 + j * 102+ 100, 100 + 102 * i+ 100);
			bar(300 + 450 + j * 102, 100 + 102 * i, 100 + 300 + 450 + j * 102, 100 + 100 + 102 * i);
		}
	}
	for (int i = 0; i < 3; i++) {
		/*topicA[A[i][0]][A[i][1]].getNum() = a + 1;
		topicA[A[i][0]][A[i][1]].getColor() = RED;
		topicA[A[i][0]][A[i][1]].drawGameButtom();*/
		char buffera[20];
		char bufferb[20];
		snprintf(buffera, sizeof(buffera), "%d", a+1);
		snprintf(bufferb, sizeof(bufferb), "%d", b + 1);
		setfillcolor(RED);
		bar(400 + A[i][1] * 102, 100 + 102 * A[i][0], 400 + A[i][1] * 102 + 98, 100 + 102 * A[i][0] + 98);
		bar(300 + 450 + relativeB[i][1] * 102, 100 + 102 * relativeB[i][0], 98 + 300 + 450 + relativeB[i][1] * 102, 98 + 100 + 102 * relativeB[i][0]);
		outtextxy(400 + A[i][1] * 102+30, 100 + 102 * A[i][0]+30, buffera);
		outtextxy(300 + 450 + relativeB[i][1] * 102 + 30, 100 + 102 * relativeB[i][0] + 30, bufferb);
		a++;
		b++;

	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			block[i][j].creatButtom(50 + j * 102, 100 + 102 * i, 100, 100, BLUE);
			block[i][j].drawGameButtom();
		}
	}
	int num = 1;
	while (1) {
		ExMessage msg;
		while (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN: {
				if (mouseMsg(&msg, block, num, ans, realB)) {
					return;
				}
				break;
			}
			}
		}
	}
}
void Random(int*** a,int n) {//n指的是步数
	IMAGE mPlay;
	loadimage(&mPlay, _T("bk.jpg"), 1024, 684);
	putimage(0, 0, &mPlay);
	button** answer = new button*[20];
	for (int i = 0; i < 20; i++) {
		answer[i] = new button[20];
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			answer[i][j].creatButtom(30 + j * 32, 30 + i * 32, 30, 30, BLUE);
			answer[i][j].drawButtom();
		}
	}
	for (int i = 0; i < 20; i++) {
		delete[] answer[i];
	}
	delete[]answer;
}
void menu() {
	initgraph(1100, 600);
	IMAGE mm;
	loadimage(&mm, _T("bk.jpg"), 1024, 684);
	putimage(0, 0, &mm);
	//加载背景
	button* play = new button;
	button* rule = new button;
	button* quit = new button;
	play->creatButtom(440, 340, 180, 50, YELLOW, "开始游戏");
	rule->creatButtom(440, 395, 180, 50, YELLOW, "游戏规则");
	quit->creatButtom(440, 450, 180, 50, YELLOW, "退出游戏");
	while (1) {
		play->drawButtom();
		rule->drawButtom();
		quit->drawButtom();
		MOUSEMSG m = GetMouseMsg();
		if (play->clickButtom(m)) {
			IMAGE mPlay;
			loadimage(&mPlay, _T("bk.jpg"), 1024, 684);
			putimage(0, 0, &mPlay);
			button* solidMode = new button;
			button* randomMode = new button;
			solidMode->creatButtom(440, 340, 180, 50, YELLOW, "关卡模式");
			randomMode->creatButtom(440, 395, 180, 50, YELLOW, "随机模式");	
			button* Return = new button;
			Return->creatButtom(440, 450, 180, 50, YELLOW, "返回");
			while(1){
				IMAGE mPlay;
				loadimage(&mPlay, _T("bk.jpg"), 1024, 684);
				putimage(0, 0, &mPlay);
				solidMode->drawButtom();
				randomMode->drawButtom();
				Return->drawButtom();
				MOUSEMSG m1 = GetMouseMsg();
				if (solidMode->clickButtom(m1)) {
					game();
				}
				if (randomMode->clickButtom(m1)) {
					Random(random(2),10);
				}
				if (Return->clickButtom(m1)) {
					break;
				}
			}
		}
		if (rule->clickButtom(m)) {

		}
		if (quit->clickButtom(m)) {
			return;
		}
	}
	closegraph();
}
bool judgeIn(int x, int y, int i, int j) {//x和y是题目表格大小，i和j是坐标
	if (i <= x && i >= 0 && j <= y && y >= 0) {
		return true;
	}
	else return false;
}
int*** random(int n) {//5的n倍步
	int directionx[4] = { -1,0,1,0 };
	int directiony[4] = { 0,1,0,-1 };
	int* ans = new int[n * 5 * 2];
	int** A = new int* [n * 5];
	int** realB = new int* [n * 5];
	int** relativeB = new int* [n * 5];
	int** total[3];
	for (int i = 0; i < n * 5; i++) {
		A[i] = new int[2];
		realB[i] = new int[2];
		relativeB[i] = new int[2];
	}//创建航迹
	int startx = (rand() % 10);
	int starty = (rand() % 10);
	A[n * 5 - 1][0] = startx + 10;
	realB[n * 5 - 1][0] = startx + 10;
	A[n * 5 - 1][1] = starty + 10;
	realB[n * 5 - 1][1] = starty + 10;
	int* Adir = new int[n * 5];
	int* Bdir = new int[n * 5];

	for (int i = n * 5 - 2; i >= 0; i--) {
		Adir[i] = rand() % 4;
		Bdir[i] = rand() % 4;
		if (judgeIn(40, 40, A[i + 1][0] + directionx[Adir[i]], A[i + 1][1] + directiony[Adir[i]])) {
			A[i][0] = A[i + 1][0] + directionx[Adir[i]];
			A[i][1] = A[i + 1][1] + directiony[Adir[i]];
		}
		else {
			i++;
			continue;
		}
		if (judgeIn(40, 40, realB[i + 1][0] + directionx[Bdir[i]], realB[i + 1][1] + directiony[Bdir[i]])) {
			realB[i][0] = realB[i + 1][0] + directionx[Bdir[i]];
			realB[i][1] = realB[i + 1][1] + directiony[Bdir[i]];
		}
		else {
			i++;
			continue;
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
	for (int i = 0; i < n * 5; i++) {
		delete[]A[i];
	}
	delete[]A;
	for (int i = 0; i < n * 5; i++) {
		delete[]realB[i];
	}
	delete[]realB;
	for (int i = 0; i < n * 5; i++) {
		delete[]relativeB[i];
	}

	delete[]relativeB;
	delete[]Adir;
	delete[]Bdir;
	return total;
}