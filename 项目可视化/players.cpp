#include"players.h"
void players:: transform() {
	filePath = "players/" + name + ".txt";
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
	player->name = tmpName;
	player->transform();
	switch (n) {
	case 1: {
		ofstream ofs;
		ofs.open(player->filePath, ios::out);
		ofs << "���� " << player->name << endl;
		break;
	}
	case 2: {
		

		break;
	}
	}
	delete player;
}