#include "solidMode.h"
#include "game.h"
#include "players.h"
using namespace std;
int*** solidTopic::getTopic(int num) {
	total = new int** [3];
	int tmp=0;
	switch (num) {
	case 1: {
		tmp = 3;
		break;
	}
	case 2: {
		tmp = 5;
		break;
	}
	case 3:
	{
		tmp = 5;
		break;
	}
	case 4:
	case 5: {
		tmp = 7;
		break;
	}
	case 6: {
		tmp = 10;
		break;
	}
	}
	
	for (int i = 0; i < 3; i++) {
		total[i] = new int* [tmp];
		for (int j = 0; j < tmp; j++) {
			total[i][j] = new int[2];
		}
	}
	string n = to_string(num);
	string fileName = "topicAndAnswer/"+n + ".txt";
	//cout << fileName << endl;
	ifstream ifs;
	ifs.open(fileName, ios::in);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < tmp; j++) {
			ifs >> total[i][j][0] >> total[i][j][1];
		}
	}
	//cout << "成功提供题目" << endl;
	//if (total == NULL)cout << "题目为空" << endl;
	return total;
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
void game(int stepNum, int size, int level, players& Player) {
	settextstyle(35, 0, "楷体");
	setbkmode(TRANSPARENT);//设置字体背景为透明
	setlinecolor(BLACK);
	settextcolor(BLACK);
	IMAGE mPlay;
	loadimage(&mPlay, _T("背景.jpg"), 1500, 800);
	putimage(0, 0, &mPlay);
	solidTopic solidtopic;
	//存放玩家点击的答案的数组
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
					if (int state = mouseMsg(start, &msg, num, ans, total[2], 3, 3, 50 + 180, 100, 180 + 350, 400)) {

						switch (state) {
						case 1: {
							Player.winSolidMode(level);
							solidtopic.freeMemory(1);
							game(5, 5, 1, Player);
							break;
						}
						case 2: {
							Player.winSolidMode(level);
							solidtopic.freeMemory(1);
							return;
						}
						case 9: {//游戏失败
							int tmpState = lose(start);
							switch (tmpState) {
							case 1: {
								//查看答案
								int tp = showAns(3, 3, total);
								if (tp == 1) {
									//返回菜单
									solidtopic.freeMemory(1);
									return;
								}
								else if (tp == 2) {//重新开始
									solidtopic.freeMemory(1);
									game(3, 3, 0, Player);
									break;
								}
								break;
							}
							case 2: {
								//重新开始
								solidtopic.freeMemory(1);
								game(3, 3, 0, Player);
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
		//绘制三个表格
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				putimage(150 + j * 60, 100 + 60 * i, &OFF);
				putimage(150 + 400 + j * 60, 100 + 60 * i, &OFF);
				putimage(150 + 400 + 400 + j * 60, 100 + 60 * i, &OFF);
			}
		}
		//绘制第二和第三个表格的轨迹
		for (int i = 0; i < stepNum; i++) {
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
		int num = 1;//当前步数
		drawRetreat();//绘制撤回按钮
		int start = timer1();//开始计时
		drawReturn();//绘制返回按钮
		while (1) {
			//游戏主循环
			BeginBatchDraw();
			timer2(start);
			settextcolor(BLACK);
			ExMessage msg;
			EndBatchDraw();
			while (peekmessage(&msg, EM_MOUSE)) {//获取玩家鼠标信息
				switch (msg.message) {
				case WM_LBUTTONDOWN: {
					if (int state = mouseMsg(start, &msg, num, ans, total[2], 5, 5, 150, 100, 450, 400)) {
						switch (state) {
						case 1: {//游戏胜利且选择了继续
							Player.winSolidMode(level);
							solidtopic.freeMemory(2);
							if (level == 1)
								game(5, 5, 2, Player);
							else if (level == 2)
								game(7, 10, 3, Player);
							break;
						}
						case 2: {//游戏胜利后选择退出
							Player.winSolidMode(level);
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
									game(5, 5, level, Player);
									break;
								}
								break;
							}
							case 2: {
								//重新开始
								solidtopic.freeMemory(2);
								game(5, 5, level, Player);
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
	case 4: {
		loadimage(&ON, _T("on.png"), 44, 44);
		loadimage(&OFF, _T("off.png"), 44, 44);
		int*** total = solidtopic.getTopic(level + 1);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				putimage(40 + j * 44, 90 + 44 * i, &OFF);
				putimage(520 + j * 44, 90 + 44 * i, &OFF);
				putimage(60 + 940 + j * 44, 90 + 44 * i, &OFF);
			}
		}
		for (int i = 0; i < stepNum; i++) {
			putimage(520 + total[0][i][1] * 44, 90 + 44 * total[0][i][0], &ON);
			settextstyle(20, 0, "楷体");
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", i + 1);
			outtextxy(520 + total[0][i][1] * 44 + 10, 90 + 44 * total[0][i][0] + 10, buffer);//A的实际轨迹
			putimage(60 + 940 + total[1][i][1] * 44, 90 + 44 * total[1][i][0], &ON);
			outtextxy(60 + 940 + total[1][i][1] * 44 + 10, 90 + 44 * total[1][i][0] + 10, buffer);
			settextcolor(BLACK);
		}
		int num = 1;
		drawRetreat();
		//撤回
		drawReturn();//返回
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
			while (peekmessage(&msg, EM_MOUSE)) {
				switch (msg.message) {
				case WM_LBUTTONDOWN: {
					if (int state = mouseMsg(start, &msg, num, ans, total[2], 10, 7, 40, 90, 480, 530)) {
						switch (state) {
						case 1: {
							Player.winSolidMode(level);
							solidtopic.freeMemory(level + 1);
							if (level == 3)
								game(7, 10, level + 1, Player);
							else if (level == 4)
								game(10, 10, level + 1, Player);
							break;
						}
						case 2: {
							Player.winSolidMode(level);
							solidtopic.freeMemory(level + 1);
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
									solidtopic.freeMemory(level + 1);
									return;
								}
								else if (tp == 2) {//重新开始
									solidtopic.freeMemory(level + 1);
									game(7, 10, level, Player);
									break;
								}
								break;
							}
							case 2: {
								//重新开始
								solidtopic.freeMemory(level + 1);
								game(7, 10, level, Player);
								break;
							}
							case 3: {
								//返回菜单
								solidtopic.freeMemory(level + 1);
								return;
							}
							}
						}
						}
						return;
					}
					else if (inRetreat(msg)) {
						retreat(num, ans, total[2], 10, 7, 40, 90, 480, 530);
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
	case 5: {
		loadimage(&ON, _T("on.png"), 44, 44);
		loadimage(&OFF, _T("off.png"), 44, 44);
		int*** total = solidtopic.getTopic(level + 1);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				putimage(40 + j * 44, 90 + 44 * i, &OFF);
				putimage(520 + j * 44, 90 + 44 * i, &OFF);
				putimage(60 + 940 + j * 44, 90 + 44 * i, &OFF);
			}
		}
		for (int i = 0; i < stepNum; i++) {
			putimage(520 + total[0][i][1] * 44, 90 + 44 * total[0][i][0], &ON);
			settextstyle(20, 0, "楷体");
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", i + 1);
			outtextxy(520 + total[0][i][1] * 44 + 10, 90 + 44 * total[0][i][0] + 10, buffer);//A的实际轨迹
			showRelativeB(total[1], 10, 10);
			settextcolor(BLACK);
		}
		int num = 1;
		drawRetreat();
		//撤回
		drawReturn();
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
			while (peekmessage(&msg, EM_MOUSE)) {
				switch (msg.message) {
				case WM_LBUTTONDOWN: {
					if (int state = mouseMsg(start, &msg, num, ans, total[2], 10, 10, 40, 90, 480, 530)) {
						switch (state) {
						case 1:
						case 2: {
							Player.winSolidMode(level);
							solidtopic.freeMemory(level + 1);
							return;
						}
						case 9: {//游戏失败
							int tmpState = lose(start);
							switch (tmpState) {
							case 1: {
								//查看答案
								int tp = showAns(10, 10, total);
								if (tp == 1) {
									//返回菜单
									solidtopic.freeMemory(level + 1);
									return;
								}
								else if (tp == 2) {//重新开始
									solidtopic.freeMemory(level + 1);
									game(10, 10, level, Player);
									break;
								}
								break;
							}
							case 2: {
								//重新开始
								solidtopic.freeMemory(level + 1);
								game(10, 10, level, Player);
								break;
							}
							case 3: {
								//返回菜单
								solidtopic.freeMemory(level + 1);
								return;
							}
							}
						}
						}
						return;
					}
					else if (inRetreat(msg)) {
						retreat(num, ans, total[2], 10, 10, 40, 90, 480, 530);
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
	if (size == 3) {
		outtextxy(x1 + j * ((x2 - x1) / (size)) + ((x2 - x1) / (size)) / 3+10, y1 + ((x2 - x1) / (size)) * i + ((x2 - x1) / (size)) / 4+5, buffer);
	}
	else {
		outtextxy(x1 + j * ((x2 - x1) / (size)) + ((x2 - x1) / (size)) / 3, y1 + ((x2 - x1) / (size)) * i + ((x2 - x1) / (size)) / 4, buffer);
	}
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
void SolidMode(players& Player) {//关卡模式 选择关卡界面
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
	IMAGE lock;
	loadimage(&lock, _T("off.png"), 200, 200);
	loadimage(&bk, _T("返回.png"), 225, 100);
	
	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &mm);
		//根据用户的通关情况判断是否绘制关卡图标
		putimage(325, 250, &one);
		if (Player.getSolidMode(0)) {
			putimage(625, 250, &two);
		}
		else putimage(625, 250, &lock);

		if (Player.getSolidMode(1)) {
			putimage(925, 250, &three);
		}
		else putimage(925, 250, &lock);

		if (Player.getSolidMode(2)) {
			putimage(325, 550, &four);
		}
		else putimage(325, 550, &lock);

		if (Player.getSolidMode(3)) {
			putimage(625, 550, &five);
		}
		else putimage(625, 550, &lock);

		if (Player.getSolidMode(4)) {
			putimage(925, 550, &six);
		}
		else putimage(925, 550, &lock);

		putimage(1200, 625, &bk);//返回按钮
		EndBatchDraw();
		MOUSEMSG m = GetMouseMsg();
		//获取鼠标信息，进入玩家可以游玩且点击的关卡
		if (checkIn(m,325,250,525,450)) {
			game(3, 3, 0,Player);
		}
		else if (checkIn(m, 625, 250, 825, 450)&&Player.getSolidMode(0)) {
			game(5, 5, 1, Player);
		}
		else if (checkIn(m, 925, 250, 1125, 450) && Player.getSolidMode(1)) {
			game(5, 5, 2, Player);
		}
		else if (checkIn(m, 325, 550, 525, 750) && Player.getSolidMode(2)) {
			game(7, 10, 3, Player);
		}
		else if (checkIn(m, 625, 550, 825, 750) && Player.getSolidMode(3)) {
			game(7, 10, 4, Player);
		}
		else if (checkIn(m, 925, 550, 1125, 750) && Player.getSolidMode(4)) {
			game(10, 10, 5, Player);
		}
		else if (checkIn(m,1200,625,1425,725)) {
			return;
		}
	}
	return;
}
