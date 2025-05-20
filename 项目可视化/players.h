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
	void initial(int tmpTime);//tmpTime��λ�Ǻ���
	void addTime(TIME other);
};
bool operator> (TIME a,TIME b);

class players {
private:
	string name;
	string filePath;
	bool solid[6];//�ؿ�ģʽͨ�����
	int randomNum;//���ģʽ����
	vector<int> succeedNum;//ÿһ�����ģʽ����ʤ���Ĺؿ���
	vector<TIME> totalTime;
	int maxNum;
	TIME maxTime;//��������ʱ�䣬ָ����ͨ������ؿ����������ʱ��
public:
	void initial(string Name);//��ʼ��
	void save();//�������ݣ�Ŀǰ��ɾ���ļ�Ȼ������дһ��
	void sort();
	int getMaxNum();
	TIME getMaxTime();
	string getName();
	void winSolidMode(int num);
};

class allPlayers {
private:
	int num;//���������
	vector<players> Players;
public:
	void getData();//���ļ��л�ȡ�����������
	void addPlayers(players player);
	void sort();
	void save();
};

players PlayersMenu();

