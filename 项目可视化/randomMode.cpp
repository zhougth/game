#include"randomMode.h"
#include"game.h"
int*** random(int n, int** A, int** realB, int** relativeB, int*** total) {//5的n倍步
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
		for (int j = 0; j < 10; j++) {
			visitA[i][j] = 0;
			visitB[i][j] = 0;
		}
	}
	int startx = (rand() % 5);
	int starty = (rand() % 5);
	A[n * 5 - 1][0] = startx;
	realB[n * 5 - 1][0] = startx;
	A[n * 5 - 1][1] = starty;
	realB[n * 5 - 1][1] = starty;
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
			} while (!judgeIn(10, 10, nextAx, nextAy) || (prevAdir != -1 && (Adir[i] + 2) % 4 == prevAdir));
			// 生成 realB 的方向，排除与上一次相反的方向
			do {
				Bdir[i] = rand() % 4;
				nextBx = realB[i + 1][0] + directionx[Bdir[i]];
				nextBy = realB[i + 1][1] + directiony[Bdir[i]];
			} while (!judgeIn(10, 10, nextBx, nextBy) || (prevBdir != -1 && (Bdir[i] + 2) % 4 == prevBdir));
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
void Random(int n) {//n指的是步数
	settextstyle(35, 0, "楷体");
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	settextcolor(BLACK);
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
	do {
		total = random(n / 5, A, realB, relativeB, total);
		ck = false;
		for (int i = 0; i < n; i++) {
			if (!(judgeIn(10, 10, total[1][i][0], total[1][i][1]))) {
				ck = true;
			}
		}
	} while (ck);
	cout << "A" << endl;
	for (int i = 0; i < n; i++) {
		cout << total[0][i][0] + 1 << "  " << total[0][i][1] + 1 << endl;
	}
	cout << "relativeB" << endl;
	for (int i = 0; i < n; i++) {
		cout << total[1][i][0] + 1 << "  " << total[1][i][1] + 1 << endl;
	}
	cout << "realB" << endl;
	for (int i = 0; i < n; i++) {
		cout << total[2][i][0] + 1 << "  " << total[2][i][1] + 1 << endl;
	}
	//上面是获取题目以及答案
	IMAGE ON, OFF;
	loadimage(&ON, _T("on.jpg"), 40, 40);
	loadimage(&OFF, _T("off.jpg"), 40, 40);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			putimage(40 + 40 + j * 40, 90 + 40 * i, &OFF);
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
		outtextxy(40 + 520 + total[0][i][1] * 40 + 10, 90 + 40 * total[0][i][0] + 10, buffer);//A的实际轨迹
		if (i > 0) {
			if (total[1][i][0] == total[1][i - 1][0] && total[1][i][1] == total[1][i - 1][1]) {
				settextcolor(RED);
			}
		}
		putimage(40 + 60 + 940 + total[1][i][1] * 40, 90 + 40 * total[1][i][0], &ON);
		outtextxy(40 + 60 + 940 + total[1][i][1] * 40 + 10, 90 + 40 * total[1][i][0] + 10, buffer);
		settextcolor(BLACK);
	}
	int** ans = new int* [n];
	for (int i = 0; i < n; i++) {
		ans[i] = new int[2];
	}
	int num = 1;
	int start = timer1();
	drawRetreat();
	while (1) {
		BeginBatchDraw();
		timer2(start);
		settextstyle(20, 0, "楷体");
		settextcolor(BLACK);
		ExMessage msg;
		EndBatchDraw();
		drawReturn();
		while (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN: {
				if (randomMsg(&msg, ans, realB, num, n)) {
					freeMemory(n / 5, A, realB, relativeB, total);
					return;
				}
				else if (inRetreat(msg)) {
					retreat(num, ans, realB, 10, n, 80, 90, 480, 490);
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
bool randomMsg(ExMessage* msg, int** ans, int** realB, int& n, int stepNum) {
	if ((msg->x < 80) || (msg->x) > (40 + 40 + 9 * 40 + 40) || (msg->y) > (90 + 40 * 9 + 40) || (msg->y < 90)) {
		return false;
	}
	cout << msg->x << "  " << msg->y << endl;
	int j = (msg->x - 80) / 40;//列
	int i = (msg->y - 90) / 40;//行
	if (ifOpen(ans, n - 1, i, j))return false;
	cout << "i=" << i << "  " << "j=" << j << endl;
	ans[n - 1][0] = i;
	ans[n - 1][1] = j;
	IMAGE ON;
	loadimage(&ON, _T("on.jpg"), 40, 40);
	putimage(40 + 40 + j * 40, 90 + 40 * i, &ON);
	settextstyle(20, 0, "楷体");
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", n);
	outtextxy(40 + 40 + j * 40 + 10, 90 + 40 * i + 10, buffer);
	n++;
	IMAGE win, lose;
	loadimage(&win, _T("win.png"), 350, 200);
	loadimage(&lose, _T("lose.png"), 350, 200);
	if (check(ans, realB, stepNum)) {
		putimage(180 + 400, 100 + 200, &win);
		settextstyle(40, 0, "楷体");
		drawNext();
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 580 && m.x <= 880 + 50 && m.y >= 300 && m.y <= 500) {
				settextstyle(40, 0, "楷体");
				return true;
			}
			else if (m.uMsg == WM_LBUTTONDOWN && inNext(m)) {
				Random(5);
				return true;
			}
			else if (inReturn(m)) {
				return true;
			}
		}
	}
	else if (n > stepNum) {
		putimage(180 + 400, 100 + 200, &lose);
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 580 && m.x <= 880 + 50 && m.y >= 300 && m.y <= 500) {
				settextstyle(40, 0, "楷体");
				return true;
			}
		}
	}

	else {
		settextstyle(40, 0, "楷体");
		return false;
	}
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
void freeMemory(int n, int** A, int** realB, int** relativeB, int*** total) {
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
bool judgeIn(int x, int y, int i, int j) {//x和y是题目表格大小，i和j是坐标
	if (i <= x && i >= 0 && j <= y && j >= 0) {
		return true;
	}
	else return false;
}
