#include"players.h"
void TIME::initial(int tmpTime) {
	tmpTime /= 1000;//ת��Ϊ��
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

void players::initial(string Name) {
	this->name = Name;
	filePath = "players/" + Name + ".txt";
	fstream fs;
	fs.open(filePath, ios::in | ios::out);
	if (fs.eof()) {//������ļ������ǿյģ���������true����������ǵ�һ����,�򴴽��ļ��������ʼ��Ϣ
		fs << name << ' ' << filePath << endl;
		fs << 0 << " " << 0 << " "<<0 << " "<<0 << " "<<0 << " "<<0 << endl;//�ؿ�ģʽ��ͨ�����
		fs << 0 << endl;//���ģʽ����
	}
	else {//�ļ�����,���ȡ����
		fs >> name >> filePath;
		for (int i = 0; i < 6; i++) {
			fs >> solid[i];
		}
		fs >> randomNum;
		int tmpTotalNum;
		TIME tmpTime;
		for (int i = 0; i < randomNum; i++) {
			fs >> tmpTotalNum;
			succeedNum[i] = tmpTotalNum;
			fs >> tmpTime.hours >> tmpTime.mins >> tmpTime.second;
			totalTime[i].hours = tmpTime.hours;
			totalTime[i].mins = tmpTime.mins;
			totalTime[i].second= tmpTime.second;
		}
	}
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
	for (int i = 0; i < randomNum; i++) {
		ofs << succeedNum[i] <<' ' << totalTime[i].hours<<' ' << totalTime[i].mins<<' ' << totalTime[i].second << endl;
	}
	ofs.close();
}
void players::sort() {
	for (int i = 0; i < randomNum-1; i++) {
		for (int j = 0; j < randomNum - 1 - i; j++) {//ð������
			if (succeedNum[j] < succeedNum[j + 1]) {
				int tmp1 = succeedNum[j];
				succeedNum[j] = succeedNum[j + 1];
				succeedNum[j + 1] = tmp1;
				TIME tmp2 = totalTime[j];
				totalTime[j] = totalTime[j + 1];
				totalTime[j + 1] = tmp2;
			}//����
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

void allPlayers::getData() {
	ifstream ifs;
	ifs.open("players/allPlayers.txt", ios::in); 
	string tmpName;
	ifs >> this->num;
	while (ifs >> tmpName) {
		players player;
		player.initial(tmpName);
		Players.push_back(player);
	}
	ifs.close();
}
void allPlayers::addPlayers(players player) {
	this->num++;
	this->Players.push_back(player);
}
void allPlayers::sort() {//�����а񣬸��ݸ����û������ͨ������ʱ������
	for (int i = 0; i < num++; i++) {
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
		}
	}
}

void allPlayers::save() {
	ofstream ofs;
	ofs.open("players/allPlayers.txt", ios::out | ios::trunc);//Ŀǰ�뷨����ɾ���������������������µ����ݣ�Ϊ���޸��û�������
	ofs << this->num << endl;
	for (int i = 0; i < this->num; i++) {
		ofs << Players[i].getName() << endl;
	}
	ofs.close();
}

players PlayersMenu() {
	cout << "�������û�����" << endl;
	string tmpName;
	cin >> tmpName;
	players player;
	player.initial(tmpName);
	return player;
}