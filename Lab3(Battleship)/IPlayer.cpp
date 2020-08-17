#include "pch.h"
#include "IPlayer.h"

IPlayer::IPlayer() {

}

int IPlayer::checkHit(char **enemyBoard, int xCoord, int yCoord) {
	if (enemyBoard[xCoord][yCoord] == '+')
		return 1;
	else if (enemyBoard[xCoord][yCoord] == 'X' || enemyBoard[xCoord][yCoord] == 'O')
		return 0;
	return -1;
}

int IPlayer::checkKilling(std::vector<std::pair<int, int>> &coordsOfShips, std::vector<Ship*> &ships, int indexOfShip) {
	if (shipIsDead(coordsOfShips)) {
		ships.erase(ships.begin() + indexOfShip);
		if (playerIsLost(ships))
			return 0;
		return 1;
	}
	return -1;
}

bool IPlayer::shipIsDead(std::vector<std::pair<int, int>> &coordsOfShips) {
	if (coordsOfShips.size() == 0)
		return true;
	return false;
}

bool IPlayer::playerIsLost(std::vector<Ship*> &ships) {
	if (ships.size() == 0)
		return true;
	return false;
}

IPlayer::~IPlayer() {

}
