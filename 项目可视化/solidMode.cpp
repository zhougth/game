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
				total[1][i][j] = relativeB1[i][j];
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
				total[1][i][j] = relativeB2[i][j];
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
				total[1][i][j] = relativeB3[i][j];
				total[2][i][j] = realB3[i][j];
			}
		}
		return total;
	}
	case 4: {
		total = new int** [3];
		for (int i = 0; i < 3; i++) {
			total[i] = new int* [7];
			for (int j = 0; j <7; j++) {
				total[i][j] = new int[2];
			}
		}
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 2; j++) {
				total[0][i][j] = A4[i][j];
				total[1][i][j] = relativeB4[i][j];
				total[2][i][j] = realB4[i][j];
			}
		}
		return total;
	}
	case 5: {
		total = new int** [3];
		for (int i = 0; i < 3; i++) {
			total[i] = new int* [7];
			for (int j = 0; j < 7; j++) {
				total[i][j] = new int[2];
			}
		}
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 2; j++) {
				total[0][i][j] = A5[i][j];
				total[1][i][j] = relativeB5[i][j];
				total[2][i][j] = realB5[i][j];
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
	case 2:
	case 3: {
		num = 5;
		break;
	}
	case 4:
	case 5: {
		num = 7;
		break;
	}
	default: {
		num = 10;
		break;
	}
	}
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
	settextstyle(35, 0, "楷体"); 
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	IMAGE mPlay;
	loadimage(&mPlay, _T("背景.jpg"), 1500, 800);
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
		loadimage(&ON, _T("on.png"), 100, 100);
		loadimage(&OFF, _T("off.png"), 100, 100);
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
		drawRetreat();
		//撤回
		int start = timer1();
		while (1) {
			BeginBatchDraw();
			timer2(start);
			settextcolor(BLACK);
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
					if (int state=mouseMsg(start,&msg, num, ans, total[2], 3, 3, 50 + 180, 100, 180 + 350, 400)) {
						
						switch (state) {
						case 1: {
							solidtopic.freeMemory(1);
							game(5, 5, 1);
							break;
						}
						case 2: {
							solidtopic.freeMemory(1);
							return;
						}
						case 9: {//游戏失败
							int tmpState = lose(start);
							switch (tmpState) {
							case 1: {
								//查看答案
								int tp=showAns(3, 3, total);
								if (tp == 1) {
									//返回菜单
									solidtopic.freeMemory(1);
									return;
								}
								else if (tp == 2) {//重新开始
									solidtopic.freeMemory(1);
									game(3, 3, 0);
									break;
								}
								break;
							}
							case 2: {
								//重新开始
								solidtopic.freeMemory(1);
								game(3, 3, 0);
								break;
							}
							case 3: {
								//返回菜单
								solidtopic.freeMemory(1);
								return;
							}
							}
						}
						}
						return;
					}
					else if (inRetreat(msg)) {
						retreat(num, ans, total[2], 3, 3, 50 + 180, 100, 180 + 350, 400);
					}
					else if (inReturn(msg)) {
						solidtopic.freeMemory(1);
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
		loadimage(&ON, _T("on.png"), 60, 60);
		loadimage(&OFF, _T("off.png"), 60, 60);
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
		drawRetreat();
		int start = timer1();
		drawReturn();
		while (1) {
			BeginBatchDraw();
			timer2(start);
			settextcolor(BLACK);
			ExMessage msg;
			EndBatchDraw();
			while (peekmessage(&msg, EM_MOUSE)) {
				switch (msg.message) {
				case WM_LBUTTONDOWN: {
					if (int state=mouseMsg(start,&msg, num, ans, total[2], 5, 5, 150, 100, 450, 400)) {
						
						switch (state) {
						case 1: {
							solidtopic.freeMemory(2);
							if (level == 1)
								game(5, 5, 2);
							else if (level == 2)
								game(7, 10, 3);
							break;
						}
						case 2: {
							solidtopic.freeMemory(2);
							return;
						}
						case 9: {//游戏失败
							int tmpState = lose(start);
							switch (tmpState) {
							case 1: {
								//查看答案
								int tp = showAns(5, 5, total);
								if (tp == 1) {
									//返回菜单
									solidtopic.freeMemory(2);
									return;
								}
								else if (tp == 2) {//重新开始
									solidtopic.freeMemory(2);
									game(5, 5, level);
									break;
								}
								break;
							}
							case 2: {
								//重新开始
								solidtopic.freeMemory(2);
								game(5, 5, level);
								break;
							}
							case 3: {
								//返回菜单
								solidtopic.freeMemory(2);
								return;
							}
							}
						}
						}
						return;
					}
					else if (inRetreat(msg)) {
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
	case 3:
	case 4:{
		loadimage(&ON, _T("on.png"), 40, 40);
		loadimage(&OFF, _T("off.png"), 40, 40);
		int*** total = solidtopic.getTopic(level+1);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				putimage(40 + 40 + j * 40, 90 + 40 * i, &OFF);
				putimage(40 + 520 + j * 40, 90 + 40 * i, &OFF);
				putimage(40 + 60 + 940 + j * 40, 90 + 40 * i, &OFF);
			}
		}
		for (int i = 0; i < stepNum; i++) {
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
		int num = 1;
		drawRetreat();
		//撤回
		int start = timer1();
		while (1) {
			BeginBatchDraw();
			timer2(start);
			settextstyle(20, 0, "楷体");
			settextcolor(BLACK);
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
					if (int state = mouseMsg(start, &msg, num, ans, total[2], 10, 7, 80, 90, 480, 490)) {
						switch (state) {
						case 1: {
							solidtopic.freeMemory(level+1);
							game(7, 10, level+1);
							break;
						}
						case 2: {
							solidtopic.freeMemory(level+1);
							return;
						}
						case 9: {//游戏失败
							int tmpState = lose(start);
							switch (tmpState) {
							case 1: {
								//查看答案
								int tp = showAns(7, 10, total);
								if (tp == 1) {
									//返回菜单
									solidtopic.freeMemory(level+1);
									return;
								}
								else if (tp == 2) {//重新开始
									solidtopic.freeMemory(level+1);
									game(7, 10, level);
									break;
								}
								break;
							}
							case 2: {
								//重新开始
								solidtopic.freeMemory(level+1);
								game(7, 10, level);
								break;
							}
							case 3: {
								//返回菜单
								solidtopic.freeMemory(level+1);
								return;
							}
							}
						}
						}
						return;
					}
					else if (inRetreat(msg)) {
						retreat(num, ans, total[2], 10, 7, 80, 90, 480, 490);
					}
					else if (inReturn(msg)) {
						solidtopic.freeMemory(level + 1);
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
int mouseMsg(int start,ExMessage* msg, int& n, int** ans, int** realB, int size, int stepNum, int x1, int y1, int x2, int y2) {
	if ((msg->x) > (x2) || (msg->y) > (y2) || (msg->x) < x1 || (msg->y) < y1) {
		return 0;
	}
	int j = (msg->x - x1) / ((x2 - x1) / (size));//列
	int i = (msg->y - y1) / ((x2 - x1) / (size));//行
	if (ifOpen(ans, n - 1, i, j)) {
		return 0;
	}
	IMAGE ON;
	loadimage(&ON, _T("on.png"), ((x2 - x1) / (size)), ((x2 - x1) / (size)));
	ans[n - 1][0] = i;
	ans[n - 1][1] = j;
	putimage(x1 + j * ((x2 - x1) / (size)), y1 + ((x2 - x1) / (size)) * i, &ON);
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", n);
	outtextxy(x1 + j * ((x2 - x1) / (size)) + ((x2 - x1) / (size)) / 2 - 18, y1 + ((x2 - x1) / (size)) * i + ((x2 - x1) / (size)) / 2 - 18, buffer);
	n++;
	if (check(ans, realB, stepNum)) {
		int state = success(start);
		return state;
	}
	else if (n > stepNum) {//失败
		return 9;
	}
	else return 0;
}
void SolidMode() {
	IMAGE mm;
	loadimage(&mm, _T("关卡模式背景.jpg"), 1500, 800);
	IMAGE one, two, three, four, five, six;
	loadimage(&one, _T("1.png"), 200, 200);
	loadimage(&two, _T("2.png"), 200, 200);
	loadimage(&three, _T("3.png"), 200, 200);
	loadimage(&four, _T("4.png"), 200, 200);
	loadimage(&five, _T("5.png"), 200, 200);
	loadimage(&six, _T("6.png"), 200, 200);
	IMAGE bk;
	loadimage(&bk, _T("返回.png"), 225, 100);
	
	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		putimage(325, 250, &one);
		putimage(625, 250, &two);
		putimage(925, 250, &three);
		putimage(325, 550, &four);
		putimage(625, 550, &five);
		putimage(925, 550, &six);
		putimage(1200, 625, &bk);
		EndBatchDraw();
		MOUSEMSG m = GetMouseMsg();
		if (checkIn(m,325,250,525,450)) {
			game(3, 3, 0);
			
		}
		if (checkIn(m, 625, 250, 825, 450)) {
			game(5, 5, 1);
			
		}
		if (checkIn(m, 925, 250, 1125, 450)) {
			game(5, 5, 2);
		}
		if (checkIn(m, 325, 550, 525, 750)) {
			game(7, 10, 3);
		}
		if (checkIn(m, 625, 550, 825, 750)) {
			game(7, 10, 4);
		}
		if (checkIn(m,1200,625,1425,725)) {
			return;
		}
	}
	return;
}
