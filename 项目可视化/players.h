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
};

struct players {
	string name;
	string filePath;
	bool solid[6];//关卡模式通关情况
	int randomNum;//随机模式次数
	vector<int> succeedNum;//每一次随机模式连续胜利的关卡数
	vector<TIME> totalTime;
	int maxNum;
	TIME maxTime;//不是最多的时间，指的是通关随机关卡最多且最快的时间
	void initial(string Name);//初始化
	void save();//保存数据，目前是删除文件然后重新写一个
};

struct allPlayers {
	int num;//玩家总数量
	vector<players> Players;
	void getData();
	void addPlayers(players player);
	void save();
};

void PlayersMenu();

