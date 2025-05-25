#include<iostream>
#include "game.h"
#include"players.h"
#include<conio.h>
using namespace std;
int main() {
	srand((unsigned int)time(NULL));
	allPlayers allplayers;
	allplayers.getData();
	players Player=PlayersMenu();
	menu(Player,allplayers);
	Player.sort();
	Player.save();
	allplayers.addPlayers(Player);
	allplayers.sort();
	allplayers.save();
	allplayers.showRank(Player);
	return 0;
}
