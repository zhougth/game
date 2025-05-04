#include "solidMode.h"
#include "game.h"
using namespace std;
int*** solidTopic::getTopic(int num) {
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
	cout << "num==" << num << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < num; j++) {
			delete[] total[i][j];
		}
		delete[] total[i];
	}
	delete[] total;
	total = NULL;
}
void game(int stepNum, int size, int level) {
	IMAGE mPlay;
	loadimage(&mPlay, _T("bk.jpg"), 1920, 900);
	putimage(0, 0, &mPlay);
	solidTopic solidtopic;
	int** ans = new int* [stepNum];
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
		loadimage(&back, _T("on.jpg"), 300, 100);
		putimage(810, 600, &back);		
		settextstyle(40, 0, "楷体");
		outtextxy(915, 625, "后退");		
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
	case 2: {
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
		settextstyle(40, 0, "楷体");
		putimage(810, 600, &back);
		outtextxy(915, 625, "后退");
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
bool mouseMsg(ExMessage* msg, int& n, int** ans, int** realB, int size, int stepNum, int x1, int y1, int x2, int y2) {
	if ((msg->x) > (x2) || (msg->y) > (y2) || (msg->x) < x1 || (msg->y) < y1) {
		return false;
	}
	int j = (msg->x - x1) / ((x2 - x1) / (size));//列
	int i = (msg->y - y1) / ((x2 - x1) / (size));//行
	if (ifOpen(ans, n - 1, i, j)) {
		return false;
	}
	IMAGE ON;
	loadimage(&ON, _T("on.jpg"), ((x2 - x1) / (size)), ((x2 - x1) / (size)));
	ans[n - 1][0] = i;
	ans[n - 1][1] = j;
	putimage(x1 + j * ((x2 - x1) / (size)), y1 + ((x2 - x1) / (size)) * i, &ON);
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", n);
	outtextxy(x1 + j * ((x2 - x1) / (size)) + ((x2 - x1) / (size)) / 2 - 18, y1 + ((x2 - x1) / (size)) * i + ((x2 - x1) / (size)) / 2 - 18, buffer);
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
void SolidMode() {
	IMAGE mm;
	loadimage(&mm, _T("test.jpg"), 1920, 900);
	putimage(0, 0, &mm);
	button** level = new button * [6];
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
	Return->creatButtom(1200, 600, 250, 150, RED);
	Return->drawButtom(50);
	outtextxy(1300, 650, "返回");
	while (1) {
		MOUSEMSG m = GetMouseMsg();
		if (level[0]->clickButtom(m)) {
			game(3, 3, 0);
			break;
		}
		if (level[1]->clickButtom(m)) {
			game(5, 5, 1);
			break;
		}
		if (level[2]->clickButtom(m)) {
			game(5, 5, 2);
			break;
		}
		if (Return->clickButtom(m)) {
			for (int i = 0; i < 6; i++) {
				delete level[i];
			}
			delete[]level;
			delete Return;
			return;
		}
	}
	return;
}