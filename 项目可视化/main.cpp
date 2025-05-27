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
	Player.save();
	allplayers.save();
	return 0;
}
