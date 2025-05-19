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

void PlayersMenu() {
	cout << "1.������ɫ" << endl;
	cout << "2.��ȡ��ɫ" << endl;
	int n;
	cin >> n;
	cout << "�������û�����" << endl;
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
	ofs.open("players/allPlayers.txt", ios::out | ios::trunc);//Ŀǰ�뷨����ɾ���������������������µ����ݣ�Ϊ���޸��û�������
	ofs << this->num << endl;
	for (int i = 0; i < this->num; i++) {
		ofs << Players[i].name << endl;
	}
	ofs.close();
}