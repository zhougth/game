#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct TIME {
	int hours;
	int mins;
	int second;
	void initial(int tmpTime);//tmpTime单位是毫秒
	void addTime(TIME other);
	bool ifZero();
	void show(int x,int y);
};
bool operator> (TIME a,TIME b);
TIME& operator +=(TIME &a, TIME b);

class players {
private:
	string name;
	string filePath;
	bool solid[6];//关卡模式通关情况
	int randomNum;//随机模式次数
	vector<int> succeedNum;//每一次随机模式连续胜利的关卡数
	vector<TIME> totalTime;
	int maxNum;
	TIME maxTime;//不是最多的时间，指的是通关随机关卡最多且最快的时间
	int randomTimes;//保存当次随机模式连续获胜的次数
	bool state;//用来保存当前状态，是否在随机模式
public:
	void initial(string Name);//初始化
	void save();//保存数据，目前是删除文件然后重新写一个
	void sort();
	int getMaxNum();
	TIME getMaxTime();
	string getName();
	void winSolidMode(int num);
	void startRandom();
	void winRandom(TIME time);
	void endRandom(TIME time);
	void clean();
};

class allPlayers {
private:
	int num;//玩家总数量
	vector<players> Players;
public:
	void getData();//从文件中获取所有玩家名字
	void addPlayers(players player);
	void sort();
	void save();
	void showRank(players);
};

players PlayersMenu();

