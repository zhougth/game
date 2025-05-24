#include"players.h"
#include<graphics.h>
#include<conio.h>
void TIME::initial(int tmpTime) {
	tmpTime /= 1000;//转化为秒
	this->hours = tmpTime / 3600;
	this->mins = (tmpTime - tmpTime / 3600 * 3600) / 60;
	this->second = tmpTime % 60;
}
void TIME::addTime(TIME other) {
	this->second += other.second;
	this->mins += other.mins;
	this->hours += other.hours;

	this->mins += this->second / 60;
	this->second %= 60;
	this->hours += this->mins / 60;
	this->mins /= 60;
}
bool TIME::ifZero() {
	if (hours + mins + second == 0) {
		return true;
	}
	return false;
}
void TIME::show(int x,int y) {

	settextcolor(RGB(230, 180, 85));
	char bufferm[20];
	char buffers[20];
	snprintf(bufferm, sizeof(bufferm), "%d", mins);
	snprintf(buffers, sizeof(buffers), "%d", second);
	if (mins < 10) {
		outtextxy(x, y, "0");
		outtextxy(x+20, y, bufferm);
	}
	else {
		outtextxy(x , y, bufferm);
	}
	outtextxy(x+40, y, ":");
	if (second < 10) {
		outtextxy(x+60, y, "0");
		outtextxy(x+60+20, y, buffers);
	}
	else {
		outtextxy(x+60, y, buffers);
	}
}
bool operator> (TIME a, TIME b) {
	if (a.hours > b.hours) {
		return true;
	}
	else if (a.hours == b.hours) {
		if (a.mins > b.mins) {
			return true;
		}
		else if (a.mins == b.mins) {
			if (a.second > b.second) {
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}
TIME& operator +=(TIME& a, TIME b) {
	a.hours += b.hours;
	a.mins += b.mins;
	a.second += b.second;
	a.mins += a.second / 60;
	a.second %= 60;
	a.hours += a.mins / 60;
	a.mins %= 60;
	return a;
}

void players::initial(string Name) {
	this->name = Name;
	filePath = "players/" + Name + ".txt";
	fstream fs;
	fs.open(filePath, ios::in | ios::out);
	if (fs.eof()) {//如果打开文件发现是空的，则这里是true，即该玩家是第一次玩,则创建文件且输入初始信息
		fs << name << ' ' << filePath << endl;
		fs << 0 << " " << 0 << " "<<0 << " "<<0 << " "<<0 << " "<<0 << endl;//关卡模式的通关情况
		fs << 0 << endl;//随机模式次数
		for (int i = 0; i < 6; i++) {
			solid[i] = false;
		}
		randomNum = 0;
	}
	else {//文件存在,则读取数据
		fs >> name >> filePath;
		for (int i = 0; i < 6; i++) {
			fs >> solid[i];
		}
		fs >> randomNum;
		int tmpTotalNum;
		TIME tmpTime;
		for (int i = 0; i < randomNum; i++) {
			fs >> tmpTotalNum;
			succeedNum.push_back( tmpTotalNum);
			fs >> tmpTime.hours >> tmpTime.mins >> tmpTime.second;
			totalTime.push_back(tmpTime);
		}
	}
	state = false;
	fs.close();
}
void players::save() {
	ofstream ofs;
	ofs.open(filePath, ios::out|ios::trunc);
	ofs << name << ' ' << filePath << endl;
	for (int i = 0; i < 6; i++) {
		ofs << solid[i] << (i == 5 ? '\n' : ' ');
	}
	ofs << randomNum << endl;
	cout << "randomNum保存成功" << endl;
	for (int i = 0; i < randomNum; i++) {
		ofs << succeedNum[i] <<' ' << totalTime[i].hours<<' ' << totalTime[i].mins<<' ' << totalTime[i].second << endl;
		cout << "第" << i << "次随机模式保存成功" << endl;
	}
	ofs.close();
}
void players::sort() {
	if (succeedNum.size() == 0)return;
	if (this->randomNum == 0)return;
	for (int i = 0; i < succeedNum.size() -1; i++) {
		for (int j = 0; j < succeedNum.size() -1 - i; j++) {//冒泡排序
			if (succeedNum[j] < succeedNum[j + 1]) {
				int tmp1 = succeedNum[j];
				succeedNum[j] = succeedNum[j + 1];
				succeedNum[j + 1] = tmp1;
				TIME tmp2 = totalTime[j];
				totalTime[j] = totalTime[j + 1];
				totalTime[j + 1] = tmp2;
			}//交换
			else if (succeedNum[j] == succeedNum[j + 1]) {
				if (totalTime[j] > totalTime[j + 1]) {
					int tmp1 = succeedNum[j];
					succeedNum[j] = succeedNum[j + 1];
					succeedNum[j + 1] = tmp1;
					TIME tmp2 = totalTime[j];
					totalTime[j] = totalTime[j + 1];
					totalTime[j + 1] = tmp2;
				}
			}
		}
	}
	maxNum = succeedNum[0];
	maxTime = totalTime[0];
}
int players::getMaxNum() {
	return maxNum;
}
TIME players::getMaxTime() {
	return maxTime;
}
string players::getName() {
	return name;
}
void players::winSolidMode(int num) {
	solid[num] = true;
}
void players::startRandom() {
	if (!state) {
		state = true;
		randomTimes = 0;
		TIME tmp;
		tmp.initial(0);
		totalTime.push_back( tmp);
		succeedNum.push_back( 0);
	}
}
void players::winRandom(TIME time) {
	randomTimes++;
	totalTime[randomNum] += time;
}
void players::endRandom(TIME time) {
	succeedNum[randomNum] = randomTimes;
	totalTime[randomNum]+= time;
	randomNum++;
	cout << "randomNum==" << randomNum << endl;
	state = false;//退出这次随机
}
void players::clean() {
	TIME tmp;
	tmp.initial(0);
	totalTime.erase(totalTime.begin()+randomNum);
	succeedNum.erase(succeedNum.begin() + randomNum);
	state = false;
}

void allPlayers::getData() {
	ifstream ifs;
	ifs.open("players/allPlayers.txt", ios::in); 
	if (ifs.eof()) {//如果打开是最后一行，则说明是刚刚创建
		this->num=0;
		return;
	}
	else {
		string tmpName;
		ifs >> this->num;
		while (ifs >> tmpName) {
			players player;
			player.initial(tmpName);
			Players.push_back(player);
		}
	}
	
	ifs.close();
}
void allPlayers::addPlayers(players player) {
	this->num++;
	this->Players.push_back(player);
}
void allPlayers::sort() {//总排行榜，根据各个用户的最多通关数和时间排序
	if (this->num != Players.size()) {
		this->num = Players.size();
	}
	cout << "排序开始" << endl;
	for (int i = 0; i < num-1; i++) {
		for (int j = 0; j < num - 1 - i; j++) {
			if (Players[j].getMaxNum() < Players[j + 1].getMaxNum()) {
				players tmp = Players[j];
				Players[j] = Players[j + 1];
				Players[j + 1] = tmp;
			}
			else if (Players[j].getMaxNum() == Players[j + 1].getMaxNum()) {
				if (Players[j].getMaxTime() > Players[j + 1].getMaxTime()) {
					players tmp = Players[j];
					Players[j] = Players[j + 1];
					Players[j + 1] = tmp;
				}
			}
			cout << "排序中" << i << endl;
		}
	}
	
}

void allPlayers::save() {
	if (this->num != Players.size()) {
		this->num = Players.size();
	}
	ofstream ofs;
	ofs.open("players/allPlayers.txt", ios::out | ios::trunc);//目前想法是先删除所有数据再重新输入新的数据（为了修改用户数量）
	ofs << this->num << endl;
	for (int i = 0; i < this->num; i++) {
		ofs << Players[i].getName() << endl;
	}
	ofs.close();
}
void allPlayers::showRank(players P) {
	this->sort();
	IMAGE rank;
	loadimage(&rank, _T("排行榜.png"), 1500, 800);
	putimage(0, 0, &rank);
	settextcolor(RGB(230, 180, 85));
	settextstyle(25, 0, "楷体");
	setbkmode(TRANSPARENT);
	if (this->num >= 5) {
		//500 360   x710  x870    ywidth60
		for (int i = 0; i < 5; i++) {
			outtextxy(500, 360 + i * 60, Players[i].getName().c_str());
			int tmp = Players[i].getMaxNum();
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", tmp);
			outtextxy(710, 360 + i * 60, buffer);
			Players[i].getMaxTime().show(870, 360 + i * 60);
		}
	}
	else {
		for (int i = 0; i < this->num; i++) {
			outtextxy(500, 360 + i * 60, Players[i].getName().c_str());
			int tmp = Players[i].getMaxNum();
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", tmp);
			outtextxy(710, 360 + i * 60, buffer);
			Players[i].getMaxTime().show(870, 360 + i * 60);
		}
	}
	string tmpName = P.getName() + "(你)";
	outtextxy(500, 360 + 5 * 60, tmpName.c_str());
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", P.getMaxNum());
	outtextxy(710, 360 + 5 * 60, buffer);
	P.getMaxTime().show(870, 360 + 5 * 60);
}

players PlayersMenu() {
	players player;
	initgraph(640, 480);
	char username[256] = { 0 };
	// 调用InputBox函数弹出输入框
	InputBox(username, 256, "请输入用户名：", "用户登录", NULL, 0, 0, false);	
	player.initial(username);
	return player;
}