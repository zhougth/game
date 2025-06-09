#include"game.h"
#include"solidMode.h"
#include"randomMode.h"
#include"players.h"
using namespace std;
int timer1() {
	int startTime = 0;
	startTime = clock();
	return startTime;
}
int timer2(int startTime) {
	settextstyle(35, 0, "楷体");
	int durTime = clock() - startTime;
	int min = durTime / 1000 / 60;
	int sec = durTime / 1000 % 60;
	char bufferm[20];
	char buffers[20];
	snprintf(bufferm, sizeof(bufferm), "%d", min);
	snprintf(buffers, sizeof(buffers), "%d", sec);
	IMAGE time;
	loadimage(&time, _T("picture/用时.png"), 300, 100);
	putimage(80+150, 550+50, &time);
	settextcolor(RGB(136,126,101));
	if (min < 10) {
		outtextxy(200 + 20 + 150, 570+60, "0");
	}
	outtextxy(100 + 100+20 + 20 + 150, 570 + 50+10, bufferm);
	outtextxy(220+20 + 20 + 150, 570 + 50+10, ":");
	if (sec < 10) {
		outtextxy(250 + 20 + 20 + 150, 570 + 50 + 10, "0");
		outtextxy(270 + 20 + 20 + 150, 570 + 50 + 10, buffers);
	}
	else {
		outtextxy(250 + 20 + 20 + 150, 570 + 50 + 10, buffers);
	}
	settextcolor(BLACK);
	return durTime;
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
		loadimage(&off, _T("picture/off.png"), ((x2 - x1) / (size)), ((x2 - x1) / (size)));
		putimage(x1 + ans[n - 2][1] * ((x2 - x1) / (size)), y1 + ((x2 - x1) / (size)) * ans[n - 2][0], &off);
		n--;
	}     
	else return;
}
bool checkIn(MOUSEMSG m,int x1,int y1,int x2,int y2) {
	if (m.x >= x1 && m.x <= x2 && m.y >= y1 && m.y <= y2) {
		return true;
	}
	return false;
}
void menu(players& Player,allPlayers &allplayers) {
	allplayers.addPlayers(Player);
	initgraph(1500, 800);
	IMAGE mm;
	loadimage(&mm, _T("picture/脑力航迹.jpg"), 1500, 800);
	//加载背景
	IMAGE Start, Rule,Re;
	loadimage(&Start, _T("picture/开始游戏.png"), 200, 80);
	loadimage(&Rule, _T("picture/游戏规则.png"), 200, 80);
	loadimage(&Re, _T("picture/退出游戏.png"), 200, 80);
	IMAGE Start2, Rule2, Re2;
	loadimage(&Start2, _T("picture/开始游戏2.png"), 200, 80);
	loadimage(&Rule2, _T("picture/游戏规则2.png"), 200, 80);
	loadimage(&Re2, _T("picture/退出游戏2.png"), 200, 80);

	IMAGE Solid, Ra, Bk;
	loadimage(&Solid, _T("picture/关卡模式.png"), 200, 80);
	loadimage(&Ra, _T("picture/挑战模式.png"), 200, 80);
	loadimage(&Bk, _T("picture/返回.png"), 200, 80);
	IMAGE Solid2, Ra2, Bk2;
	loadimage(&Solid2, _T("picture/关卡模式2.png"), 200, 80);
	loadimage(&Ra2, _T("picture/挑战模式2.png"), 200, 80);
	loadimage(&Bk2, _T("picture/返回2.png"), 200, 80);

	IMAGE mPlay;
	loadimage(&mPlay, _T("picture/脑力航迹.jpg"), 1500, 800);
	IMAGE rank;
	loadimage(&rank, _T("picture/查看排名.png"), 80, 80);
	IMAGE rank2;
	loadimage(&rank2, _T("picture/查看排名2.png"), 80, 80);
	FLAG1:
		BeginBatchDraw();
		putimage(0, 0, &mm);
		putimage(625, 400, &Start);
		putimage(625, 500, &Rule);
		putimage(625, 600, &Re);
		EndBatchDraw();
		while (1) {
			MOUSEMSG m = GetMouseMsg();
			if (checkIn(m,625,400,825,480)) 	
			 {
				putimage(625, 400, &Start2);
				if (m.uMsg == WM_LBUTTONDOWN) {
					FLAG2:	
						BeginBatchDraw();
						putimage(0, 0, &mPlay);//绘制点击开始游戏之后的界面
						putimage(625, 400, &Solid);
						putimage(625, 500, &Ra);
						putimage(625, 600, &Bk);
						putimage(845, 500, &rank);
						EndBatchDraw();
						while (1) {
						MOUSEMSG m1 = GetMouseMsg();
						if (checkIn(m1, 625, 400, 825, 480)) {//关卡模式
							putimage(625, 400, &Solid2);
							if (m1.uMsg == WM_LBUTTONDOWN) {
								SolidMode(Player);
								goto FLAG2;
							}
						}
						else putimage(625, 400, &Solid);
						if (checkIn(m1, 625, 500, 825, 580)) {//挑战模式
							putimage(625, 500, &Ra2);
							if (m1.uMsg == WM_LBUTTONDOWN) {
								Random(Player);
								goto FLAG2;
							}
						}
						else putimage(625, 500, &Ra);
						if (checkIn(m1, 845, 500, 925, 580)) {//查看挑战模式排行榜
							putimage(845, 500, &rank2);
							if (m1.uMsg == WM_LBUTTONDOWN) {
								Player.sort();
								Player.save();
								allplayers.refresh(Player);
								allplayers.sort();
								allplayers.save();
								allplayers.showRank(Player);
								goto FLAG2;
							}
						}
						else putimage(845, 500, &rank);
						if (checkIn(m1, 625, 600, 825, 680)) {//返回
							putimage(625, 600, &Bk2);
							if (m1.uMsg == WM_LBUTTONDOWN) {
								Player.sort();
								Player.save();
								allplayers.refresh(Player);
								allplayers.sort();
								allplayers.save();
								goto FLAG1;
							}
						}
						else putimage(625, 600, &Bk);
					}
				}
			}
			else {
				putimage(625, 400, &Start);
			}
			if (checkIn(m, 625, 500, 825, 580)) {//规则
				putimage(625, 500, &Rule2);
				if (m.uMsg == WM_LBUTTONDOWN) {
					IMAGE rule;
					loadimage(&rule, _T("picture/规则1.png"), 1500, 800);
					putimage(0, 0, &rule);
					IMAGE bk;
					loadimage(&bk, _T("picture/返回.png"), 180, 80);
					putimage(1300, 700, &bk);
					while (1) {
						MOUSEMSG m = GetMouseMsg();
						if (checkIn(m, 1300, 700, 1480, 780)) {
							if(m.uMsg==WM_LBUTTONDOWN)
							goto FLAG1;
						}
					};
				}
			}
			else {
				putimage(625, 500, &Rule);
			}
			if (checkIn(m, 625, 600, 825, 680)) {//退出游戏
				putimage(625, 600, &Re2);
				if (m.uMsg == WM_LBUTTONDOWN) {
					closegraph();
					return;
				}
			}
			else {
				putimage(625, 600, &Re);
			}
		}	
	}
//}
void drawReturn() {
	IMAGE Return;
	loadimage(&Return, _T("picture/退出.png"), 300, 100);
	putimage(40+400 + 150, 550 + 50, &Return);
}
bool inReturn(ExMessage m) {
	if (m.x >= 440 + 150 && m.x <= 740 + 150 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
bool inReturn(MOUSEMSG m) {
	if (m.x >= 440 + 150 && m.x <= 740 + 150 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
void drawNext() {
	IMAGE Next;
	loadimage(&Next, _T("picture/继续.png"), 300, 100);
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
	loadimage(&Retreat, _T("picture/撤回.png"), 300, 100);
	putimage(800 + 150, 550 + 50, &Retreat);
}
bool inRetreat(MOUSEMSG m) {
	if (m.x >= 800 + 150 && m.x <= 800 + 150 + 300 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
bool inRetreat(ExMessage m) {
	if (m.x >= 800 + 150 && m.x <= 800 + 150 + 300 && m.y >= 600 && m.y <= 700) {
		return true;
	}
	else return false;
}
bool ifOpen(int** ans, int step, int i, int j) {//判断该格子是否已经被玩家点击
	for (int k = 0; k < step; k++) {
		if (ans[k][0] == i && ans[k][1] == j) {
			return true;
		}
	}
	return false;
}
int success(int start) {
	IMAGE win;
	loadimage(&win, _T("picture/挑战成功.jpg"), 1500, 800);
	putimage(0, 0, &win);
	IMAGE Continue, returnMenu;
	loadimage(&Continue, _T("picture/继续.png"), 300, 100);
	loadimage(&returnMenu, _T("picture/返回菜单.png"), 300, 100);
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
	loadimage(&lose, _T("picture/挑战失败.jpg"), 1500, 800);
	putimage(0, 0, &lose);
	IMAGE answer, restart, returnMenu;
	loadimage(&answer, _T("picture/查看答案.png"), 300, 100);
	loadimage(&restart, _T("picture/重新开始.png"), 300, 100);
	loadimage(&returnMenu, _T("picture/返回菜单.png"), 300, 100);
	putimage(600, 450+5, &answer);
	putimage(600, 550+10, &restart);
	putimage(600, 650+15, &returnMenu);
	showTime(start);
	while (1) {
		MOUSEMSG m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 600 && m.x <= 900 && m.y >= 450+5 && m.y <= 550+5) {
				return 1;
			}
			if (m.x >= 600 && m.x <= 900 && m.y >= 550+10 && m.y <= 650+10) {
				return 2;
			}
			if (m.x >= 600 && m.x <= 900 && m.y >= 650+15 && m.y <= 750+15) {
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
	loadimage(&time, _T("picture/用时.png"), 300, 100);
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
	settextcolor(BLACK);
}
int showAns(int stepNum, int size, int*** total) {
	IMAGE mPlay;
	loadimage(&mPlay, _T("picture/背景.jpg"), 1500, 800);
	putimage(0, 0, &mPlay);
	IMAGE OFF;
	IMAGE ON;
	switch (size) {
	case 3: {	
		loadimage(&ON, _T("picture/on.png"), 100, 100);
		loadimage(&OFF, _T("picture/off.png"), 100, 100);
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
		loadimage(&ON, _T("picture/on.png"), 60, 60);
		loadimage(&OFF, _T("picture/off.png"), 60, 60);
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
		
		loadimage(&ON, _T("picture/on.png"), 44, 44);
		loadimage(&OFF, _T("picture/off.png"), 44, 44);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				putimage( 40 + j * 44, 90 + 44* i, &OFF);
				putimage( 520 + j * 44, 90 + 44 * i, &OFF);
				putimage( 60 + 940 + j * 44, 90 + 44 * i, &OFF);
			}
		}
		settextcolor(BLACK);
		showRelativeB(total[1], size, stepNum);
		int a = 1, b = 1;
		for (int i = 0; i < stepNum; i++) {
			putimage( 40 + total[2][i][1] * 44, 90 + 44 * total[2][i][0], &ON);
			putimage( 520 + total[0][i][1] * 44, 90 + 44 * total[0][i][0], &ON);
			settextstyle(20, 0, "楷体");
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", i + 1);
			outtextxy( 520 + total[0][i][1] * 44 + 10, 90 + 44 * total[0][i][0] + 10, buffer);//A的实际轨迹
			settextcolor(BLACK);
			outtextxy( 40 + total[2][i][1] * 44+10, 90 + 44 * total[2][i][0]+10, buffer);
		}
	}
	}
	drawReturn();//退出
	IMAGE reStrat;
	loadimage(&reStrat, _T("picture/重新开始.png"), 300, 100);
	putimage(150+300 + 480 + 40, 600, &reStrat);
	while (1) {
		MOUSEMSG m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (inReturn(m)) {//退出
				return 1;
			}
			else if (m.x >= 150 + 300 + 520 && m.x <= 150 + 820 + 300 && m.y >= 600 && m.y <= 700) {//重新开始
				return 2;
			}
		}
	}
}
void game() {
	srand((unsigned int)time(NULL));
	allPlayers allplayers;
	allplayers.getData();
	players Player = PlayersMenu();
	menu(Player, allplayers);
	Player.save();
	allplayers.save();
	return;
}
