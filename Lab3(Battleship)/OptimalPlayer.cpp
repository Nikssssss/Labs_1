#include "pch.h"
#include "OptimalPlayer.h"

OptimalPlayer::OptimalPlayer(){
	
}

bool OptimalPlayer::getWinStatus() {
	return isWinner;
}

char **OptimalPlayer::getMyBoard() {
	return myBoard.getBoard();
}

char **OptimalPlayer::getEnemyBoard() {
	return enemyBoard.getBoard();
}

std::vector<Ship*> &OptimalPlayer::getShips() {
	return ships;
}

void OptimalPlayer::setShips() {
	int numberOfShips = 1;
	int numberOfDecks = 4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < numberOfShips; j++) {
			if (i == 0)
				setFourDeckShip();
			else if (i == 3)
				setOneDeckShips();
			else
				setMiddleDeckShips(numberOfDecks);
		}
		numberOfDecks--;
		numberOfShips++;
	}
	printBoards(myBoard.getBoard(), enemyBoard.getBoard());
}

void OptimalPlayer::setFourDeckShip() {
	int firstCoord, secondCoord;
	int direction;
	int coordinates[3] = { 0, 6, 9 };
	firstCoord = coordinates[rand() % 3];
	int tempCoord = coordinates[rand() % 3];
	while (firstCoord != 0 && tempCoord == firstCoord) {
		tempCoord = coordinates[rand() % 3];
	}
	secondCoord = tempCoord;

	if (firstCoord == 0 && secondCoord == 0)
		direction = rand() % 2;
	else if ((secondCoord == 0 || secondCoord == 9) && firstCoord != 9)
		direction = 0;
	else
		direction = 1;

	createShip(firstCoord, secondCoord, direction, 4);
}

void OptimalPlayer::setMiddleDeckShips(int numberOfDecks) {
	std::pair<int, int> corners[4] = { std::make_pair(0, 0), std::make_pair(0, 9), std::make_pair(9, 0), std::make_pair(9, 9) };

	int randomCorner = rand() % 4;
	switch (randomCorner) {
	case 0:
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (i == 0 || i == 9) {
					if (checkSetting(i, j, 1, numberOfDecks) != -1) {
						createShip(i, j, 1, numberOfDecks);
						return;
					}
				}
				else {
					if (checkSetting(i, j, 0, numberOfDecks) != -1) {
						createShip(i, j, 0, numberOfDecks);
						return;
					}
					else if (checkSetting(i, 9, 0, numberOfDecks) != -1) {
						createShip(i, 9, 0, numberOfDecks);
						return;
					}
					break;
				}
			}
		}
		break;
	case 1:
		for (int j = 9; j >= 0; j--) {
			for (int i = 0; i < 10; i++) {
				if (j == 0 || j == 9) {
					if (checkSetting(i, j, 0, numberOfDecks) != -1) {
						createShip(i, j, 0, numberOfDecks);
						return;
					}
				}
				else {
					if (checkSetting(i, j, 1, numberOfDecks) != -1) {
						createShip(i, j, 1, numberOfDecks);
						return;
					}
					else if (checkSetting(9, j, 1, numberOfDecks) != -1) {
						createShip(9, j, 1, numberOfDecks);
						return;
					}
					break;
				}
			}
		}
		break;
	case 2:
		for (int i = 9; i >= 0; i--) {
			for (int j = 9; j >= 0; j--) {
				if (i == 0 || i == 9) {
					if (checkSetting(i, j, 1, numberOfDecks) != -1) {
						createShip(i, j, 1, numberOfDecks);
						return;
					}
				}
				else {
					if (checkSetting(i, j, 0, numberOfDecks) != -1) {
						createShip(i, j, 0, numberOfDecks);
						return;
					}
					else if (checkSetting(i, 0, 0, numberOfDecks) != -1) {
						createShip(i, 0, 0, numberOfDecks);
						return;
					}
					break;
				}
			}
		}
		break;
	case 3:
		for (int j = 0; j < 10; j++) {
			for (int i = 9; i >= 0; i--) {
				if (j == 0 || j == 9) {
					if (checkSetting(i, j, 0, numberOfDecks) != -1) {
						createShip(i, j, 0, numberOfDecks);
						return;
					}
				}
				else {
					if (checkSetting(i, j, 1, numberOfDecks) != -1) {
						createShip(i, j, 1, numberOfDecks);
						return;
					}
					else if (checkSetting(0, j, 1, numberOfDecks) != -1) {
						createShip(0, j, 1, numberOfDecks);
						return;
					}
					break;
				}
			}
		}
		break;
	}
}

void OptimalPlayer::setOneDeckShips() {
	int firstCoord, secondCoord;
	bool setIsCorrect = false;

	while (!setIsCorrect) {
		firstCoord = rand() % 10;
		secondCoord = rand() % 10;

		if (checkSetting(firstCoord, secondCoord, -1, 1) != -1)
			setIsCorrect = true;
	}

	createShip(firstCoord, secondCoord, -1, 1);
}

void OptimalPlayer::createShip(int firstCoord, int secondCoord, int direction, int numberOfDecks) {
	if (direction == 0) {
		ships.emplace_back(new Ship);
		for (int i = firstCoord; i < firstCoord + numberOfDecks; i++) {
			myBoard.getBoard()[i][secondCoord] = '+';
			ships[ships.size() - 1]->getShipCoords().emplace_back(std::make_pair(i, secondCoord));
		}
	}
	else if (direction == 1) {
		ships.emplace_back(new Ship);
		for (int i = secondCoord; i < secondCoord + numberOfDecks; i++) {
			myBoard.getBoard()[firstCoord][i] = '+';
			ships[ships.size() - 1]->getShipCoords().emplace_back(std::make_pair(firstCoord, i));
		}
	}
	else {
		ships.emplace_back(new Ship);
		myBoard.getBoard()[firstCoord][secondCoord] = '+';
		ships[ships.size() - 1]->getShipCoords().emplace_back(std::make_pair(firstCoord, secondCoord));
	}
}

int OptimalPlayer::checkSetting(int firstCoord, int secondCoord, int direction, int numberOfDecks) {
	char upperLast, rightLast, leftLast, downLast, downLength, rightLength;

	if (direction == 0) {
		downLength = (firstCoord + numberOfDecks - 1);
		if (downLength > 9)
			return -1;
		if ((upperLast = firstCoord - 1) < 0)
			upperLast = 0;
		if ((leftLast = secondCoord - 1) < 0)
			leftLast = 0;
		if ((rightLast = secondCoord + 1) > 9)
			rightLast = 9;
		if ((downLast = firstCoord + numberOfDecks) > 9)
			downLast = 9;
	}
	else if (direction == 1) {
		rightLength = (secondCoord + numberOfDecks - 1);
		if (rightLength > 9)
			return -1;
		if ((upperLast = firstCoord - 1) < 0)
			upperLast = 0;
		if ((leftLast = secondCoord - 1) < 0)
			leftLast = 0;
		if ((rightLast = secondCoord + numberOfDecks) > 9)
			rightLast = 9;
		if ((downLast = firstCoord + 1) > 9)
			downLast = 9;
	}
	else {
		if ((upperLast = firstCoord - 1) < 0)
			upperLast = 0;
		if ((leftLast = secondCoord - 1) < 0)
			leftLast = 0;
		if ((rightLast = secondCoord + 1) > 9)
			rightLast = 9;
		if ((downLast = firstCoord + 1) > 9)
			downLast = 9;
	}

	for (int i = upperLast; i <= downLast; i++) {
		for (int j = leftLast; j <= rightLast; j++) {
			if (myBoard.getBoard()[i][j] == '+')
				return -1;
		}
	}

	return 1;
}

void OptimalPlayer::attack(IPlayer *enemy) {

}

OptimalPlayer::~OptimalPlayer(){

}
