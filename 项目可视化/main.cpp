#include<iostream>
#include "game.h"
#include"players.h"
using namespace std;
int main() {
	srand((unsigned int)time(NULL));
	allPlayers allplayers;
	allplayers.getData();
	players Player=PlayersMenu();
	menu(Player);
	Player.sort();
	Player.save();
	allplayers.addPlayers(Player);
	allplayers.sort();
	allplayers.save();
	return 0;
}
