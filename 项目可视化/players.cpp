#include"players.h"
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

void players::initial(string Name) {
	this->name = Name;
	filePath = "players/" + Name + ".txt";
	fstream fs;
	fs.open(filePath, ios::in | ios::out);
	if (fs.eof()) {//如果打开文件发现是空的，则这里是true，即该玩家是第一次玩,则创建文件且输入初始信息
		fs << name << ' ' << filePath << endl;
		fs << 0 << " " << 0 << " "<<0 << " "<<0 << " "<<0 << " "<<0 << endl;//关卡模式的通关情况
		fs << 0 << endl;//随机模式次数
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

void PlayersMenu() {
	cout << "1.创建角色" << endl;
	cout << "2.读取角色" << endl;
	int n;
	cin >> n;
	cout << "请输入用户名称" << endl;
	string tmpName;
	cin >> tmpName;
	players* player = new players;
	player->initial(tmpName);
	switch (n) {
	case 1: {
		
		break;
	}
	case 2: {

		break;
	}
	}
	delete player;
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
void allPlayers::save() {
	ofstream ofs;
	ofs.open("players/allPlayers.txt", ios::out | ios::trunc);//目前想法是先删除所有数据再重新输入新的数据（为了修改用户数量）
	ofs << this->num << endl;
	for (int i = 0; i < this->num; i++) {
		ofs << Players[i].name << endl;
	}
	ofs.close();
}