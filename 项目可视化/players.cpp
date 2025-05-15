#include"players.h"
void players:: transform() {
	filePath = "players/" + name + ".txt";
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
	player->name = tmpName;
	player->transform();
	switch (n) {
	case 1: {
		ofstream ofs;
		ofs.open(player->filePath, ios::out);
		ofs << "姓名 " << player->name << endl;
		break;
	}
	case 2: {
		

		break;
	}
	}
	delete player;
}