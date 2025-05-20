#include<iostream>
#include "game.h"
#include"players.h"
using namespace std;
int main() {
	srand((unsigned int)time(NULL));
	players Player=PlayersMenu();
	menu(Player);
	//Player.sort();
	Player.save();
	return 0;
}
