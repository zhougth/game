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

struct players {
	string name;
	string filePath;
	bool solid[6];//�ؿ�ģʽͨ�����
	int randomNum;//���ģʽ����
	vector<int> succeedNum;//ÿһ�����ģʽ����ʤ���Ĺؿ���
	vector<TIME> totalTime;
	int maxNum;
	TIME maxTime;//��������ʱ�䣬ָ����ͨ������ؿ����������ʱ��
	void initial(string Name);//��ʼ��
	void save();//�������ݣ�Ŀǰ��ɾ���ļ�Ȼ������дһ��
};

struct allPlayers {
	int num;//���������
	vector<players> Players;
	void getData();
	void addPlayers(players player);
	void save();
};

void PlayersMenu();

