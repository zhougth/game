#include"randomMode.h"
#include"game.h"
#include<vector>
int*** random(int n, int** A, int** realB, int** relativeB, int*** total) {//n步
fflag:
	int directionx[4] = { -1,0,1,0 };
	int directiony[4] = { 0,1,0,-1 };
	for (int i = 0; i < n; i++) {
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
	int startx = 3+(rand() % 4);
	int starty =3+ (rand() % 4);
	A[n  - 1][0] = startx;
	realB[n - 1][0] = startx;
	A[n  - 1][1] = starty;
	realB[n  - 1][1] = starty;
	int* Adir = new int[n ];
	int* Bdir = new int[n];
	visitA[startx][starty] = 1;
	visitB[startx][starty] = 1;
	for (int i = n  - 2; i >= 0; i--) {
		int prevAdir = (i == n  - 2) ? -1 : Adir[i + 1]; // 上一次的方向
		int prevBdir = (i == n  - 2) ? -1 : Bdir[i + 1]; // 上一次的方向
		bool foundValidPathA = false;
		bool foundValidPathB = false;
		int nextAx, nextAy, nextBx, nextBy;
		while ((!foundValidPathA)&&(!foundValidPathB)) {
			foundValidPathA = false;
			foundValidPathB = false;
			// 生成 A 的方向，排除与上一次相反的方向
			int countA = 0;
			do {
				countA++;
				if (countA > 30) {
					goto fflag;
				}
				Adir[i] = rand() % 4;
				nextAx = A[i + 1][0] + directionx[Adir[i]];
				nextAy = A[i + 1][1] + directiony[Adir[i]];
			} while (!judgeIn(10, 10, nextAx, nextAy) || (prevAdir != -1 && (Adir[i] + 2) % 4 == prevAdir));
			// 更新 A 的位置	
			if (judgeIn(10, 10, nextAx, nextAy) && !visitA[nextAx][nextAy]) {
				A[i][0] = nextAx;
				A[i][1] = nextAy;
				visitA[nextAx][nextAy] = 1;
				// 检查是否会走进死胡同
				if (!isDeadEnd(nextAx, nextAy, visitA, directionx, directiony)) {
					foundValidPathA = true;
				}
				else {
					// 如果是死胡同，重新随机
					goto fflag;
				}
			}
			// 生成 realB 的方向，排除与上一次相反的方向
			int countB = 0;
			do {
				countB++;
				if (countB > 30) {
					goto fflag;
				}
				Bdir[i] = rand() % 4;
				nextBx = realB[i + 1][0] + directionx[Bdir[i]];
				nextBy = realB[i + 1][1] + directiony[Bdir[i]];
			} while (!judgeIn(10, 10, nextBx, nextBy) || (prevBdir != -1 && (Bdir[i] + 2) % 4 == prevBdir));
					
			// 更新 realB 的位置
			int nextBx = realB[i + 1][0] + directionx[Bdir[i]];
			int nextBy = realB[i + 1][1] + directiony[Bdir[i]];
			if (judgeIn(10, 10, nextBx, nextBy) && !visitB[nextBx][nextBy]) {
				realB[i][0] = nextBx;
				realB[i][1] = nextBy;
				visitB[nextBx][nextBy] = 1;
				// 检查是否会走进死胡同
				if (!isDeadEnd(nextBx, nextBy, visitB, directionx, directiony)) {
					foundValidPathB = true;
				}
				else {
					// 如果是死胡同，重新随机
					goto fflag;
				}
			}
			else continue;
		}
	}
	
	relativeB[0][0] = realB[0][0];
	relativeB[0][1] = realB[0][1];
	for (int i = 1; i < n ; i++) {
		relativeB[i][0] = relativeB[i - 1][0] + directionx[Adir[i - 1]] + (-1) * directionx[Bdir[i - 1]];
		relativeB[i][1] = relativeB[i - 1][1] + directiony[Adir[i - 1]] + (-1) * directiony[Bdir[i - 1]];
	}//创建B的相对航迹

	for (int i = 0; i < n; i++) {
		if (!(judgeIn(10, 10, relativeB[i][0], relativeB[i][1]))) {
			goto fflag;
		}
	}//判断B的相对轨迹是否都在表格内，若不在则重新规划路线

	int check1[10][10] = {0};//用来记录各个点出现的次数
	for (int i = 0; i < n; i++) {
		check1[relativeB[i][0]][relativeB[i][1]]++;
		if (check1[relativeB[i][0]][relativeB[i][1]] > 4) {
			goto fflag;//要是b的相对航迹在同一个点出现4次以上，则重新规划路线，避免出现显示错误
		}
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
	int** A = new int* [n ];
	int** realB = new int* [n ];
	int** relativeB = new int* [n];
	int*** total = new int** [3];
	for (int i = 0; i < 3; i++) {
		total[i] = nullptr;
	}
	total = random(n, A, realB, relativeB, total);
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
flag:
	IMAGE mPlay;
	loadimage(&mPlay, _T("背景.jpg"), 1500, 800);
	putimage(0, 0, &mPlay);
	IMAGE ON, OFF;
	loadimage(&ON, _T("on.png"), 44, 44);
	loadimage(&OFF, _T("off.png"), 44, 44);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			putimage( 40 + j * 44, 90 + 44 * i, &OFF);
			putimage( 520 + j * 44, 90 + 44 * i, &OFF);
			putimage(60 + 940 + j * 44, 90 + 44 * i, &OFF);
		}
	}
	int a = 1, b = 1;
	for (int i = 0; i < n; i++) {
		putimage( 520 + total[0][i][1] * 44, 90 + 44 * total[0][i][0], &ON);
		settextstyle(20, 0, "楷体");
		char buffer[20];
		snprintf(buffer, sizeof(buffer), "%d", i + 1);
		outtextxy( 520 + total[0][i][1] * 44 + 10, 90 + 44 * total[0][i][0] + 10, buffer);//A的实际轨迹
	}
	showRelativeB(total[1], 10, 10);
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
				if (int state=randomMsg(start,&msg, ans, realB, num, n)) {				
					switch (state) {
					case 1: {
						freeMemory(n , A, realB, relativeB, total);
						Random(n);//进行下一个随机关卡
						break;
					}
					case 2: {
						freeMemory(n, A, realB, relativeB, total);
						return;
					}
					case 9: {//失败
						int tmpState=lose(start);
						switch (tmpState) {
						case 1: {
							//查看答案
							int tp=showAns(n, 10, total);
							if (tp == 1) {
								//返回菜单
								freeMemory(n , A, realB, relativeB, total);
								return;
							}
							else if (tp == 2) {//重新开始
								goto flag;
								break;
							}
							break;
						}
						case 2: {
							goto flag;//重新开始当前的随机关卡
							break;
						}
						case 3: {
							freeMemory(n, A, realB, relativeB, total);
							return;
						}
						}
					}
					}
					return;
				}
				else if (inRetreat(msg)) {
					retreat(num, ans, realB, 10, n, 40, 90, 480, 530);
				}
				else if (inReturn(msg)) {
					freeMemory(n , A, realB, relativeB, total);
					return;
				}
				break;
			}
			}
		}
	}
}
int randomMsg(int start,ExMessage* msg, int** ans, int** realB, int& n, int stepNum) {
	if ((msg->x < 40) || (msg->x) > ( 40 + 10 * 44) || (msg->y) > (90 + 44 * 10 ) || (msg->y < 90)) {
		return false;
	}
	cout << msg->x << "  " << msg->y << endl;
	int j = (msg->x -40) / 44;//列
	int i = (msg->y - 90) / 44;//行
	if (ifOpen(ans, n - 1, i, j))return false;
	cout << "i=" << i << "  " << "j=" << j << endl;
	ans[n - 1][0] = i;
	ans[n - 1][1] = j;
	IMAGE ON;
	loadimage(&ON, _T("on.png"), 44, 44);
	putimage( 40 + j * 44, 90 + 44 * i, &ON);
	settextstyle(20, 0, "楷体");
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", n);
	outtextxy( 40 + j * 44 + 10, 90 + 44 * i + 10, buffer);
	n++;
	if (check(ans, realB, stepNum)) {
		int state=success(start);
		return state;
	}
	else if (n > stepNum) {
		return 9;
	}
	else {
		settextstyle(40, 0, "楷体");
		return 0;
	}
}
bool isDeadEnd(int x, int y, int** visited, int directionx[4], int directiony[4]) {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		int nextX = x + directionx[i];
		int nextY = y + directiony[i];
		if (!judgeIn(10, 10, nextX, nextY)) {
			count++;
			continue;
		}
		else {
			if (visited[nextX][nextY]) {
				count++;
				continue;
			}
		}
	}
	return count==4; // 如果四个方向都被堵死，则是死胡同
}
void freeMemory(int n, int** A, int** realB, int** relativeB, int*** total) {
	for (int i = 0; i < n ; i++) {
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
	if (i < x && i >= 0 && j < y && j >= 0) {
		return true;
	}
	else return false;
}
void showRelativeB(int** relativeB, int size, int stepNum) {
	vector <int> uniqueBx;
	vector <int> uniqueBy;
	vector <int> uniqueBn;//经过的次数
	uniqueBn.resize(stepNum, 0);
	vector <vector <int>> numB;
	int tmp = 0;//用来存去重后有多少个坐标
	for (int i = 0; i < stepNum; i++) {//遍历路径
		bool ck = false;
		for (int j = 0; j < tmp; j++) {//寻找是否出现过
			if (relativeB[i][0] == uniqueBx[j] && relativeB[i][1] == uniqueBy[j]) {//之前经过该点
				uniqueBn[j]++;
				ck = true;
				numB[j].push_back(i);
				break;
			}
		}
		if (!ck) {//之前没经过
			uniqueBx.push_back(relativeB[i][0]);
			uniqueBy.push_back(relativeB[i][1]);
			uniqueBn[tmp++] = 1;
			numB.push_back({ i });//
		}
	}
	cout << "去重后共" << tmp << endl;
	for (int i = 0; i < tmp; i++) {
		cout << uniqueBx[i] + 1 << "," << uniqueBy[i] + 1 << "   经过" << uniqueBn[i] << "次" << endl;
		cout << "分别是" << endl;
		for (int j = 0; j < uniqueBn[i]; j++) {
			cout << "i=="<<i<<"    j=="<<j<<"  "<<numB[i][j] << endl;
		}
	}
	IMAGE ON;
	loadimage(&ON, _T("on.png"), 44, 44);
	for (int i = 0; i < tmp; i++) {
		putimage(60 + 940 + uniqueBy[i] * 44, 90 + 44 * uniqueBx[i], &ON);
		switch (uniqueBn[i]) {
		case 1: {
			settextstyle(20, 0, "楷体");
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", numB[i][0]+1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 10, 90 + 44 * uniqueBx[i] + 10, buffer);
			break;
		}
		case 2: {
			settextstyle(18, 0, "楷体");
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", numB[i][0] + 1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 5, 90 + 44 * uniqueBx[i] + 10+5, buffer);
			snprintf(buffer, sizeof(buffer), "%d", numB[i][1] + 1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 9+14, 90 + 44 * uniqueBx[i] + 10+5, buffer);
			break;
		}
		case 3: {
			settextstyle(14, 0, "楷体");
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", numB[i][0] + 1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 5, 90 + 44 * uniqueBx[i] + 5, buffer);
			snprintf(buffer, sizeof(buffer), "%d", numB[i][1] + 1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 44-15, 90 + 44 * uniqueBx[i] + 5, buffer);
			snprintf(buffer, sizeof(buffer), "%d", numB[i][2] + 1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 5, 90 + 44 * uniqueBx[i] +44-15, buffer);
			break;
		}
		case 4: {
			settextstyle(14, 0, "楷体");
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", numB[i][0] + 1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 5, 90 + 44 * uniqueBx[i] + 5, buffer);
			snprintf(buffer, sizeof(buffer), "%d", numB[i][1] + 1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 44 - 15, 90 + 44 * uniqueBx[i] + 5, buffer);
			snprintf(buffer, sizeof(buffer), "%d", numB[i][2] + 1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 5, 90 + 44 * uniqueBx[i] + 44 - 15, buffer);
			snprintf(buffer, sizeof(buffer), "%d", numB[i][3] + 1);
			outtextxy(60 + 940 + uniqueBy[i] * 44 + 44-15, 90 + 44 * uniqueBx[i] + 44 - 15, buffer);
			break;
		}
		}
		
		
	}
}