#include "pch.h"
#include "GameLauncher.h"


void GameLauncher::launch() {
	player1->setShips();
	player2->setShips();

	while (1) {
		player1->attack(player2);
		if (player1->getWinStatus()) {
			std::cout << "Player1 won!" << std::endl;
			break;
		}
		player2->attack(player1);
		if (player2->getWinStatus()) {
			std::cout << "Player2 won!" << std::endl;
			break;
		}
	}
}

GameLauncher::~GameLauncher() {

}
