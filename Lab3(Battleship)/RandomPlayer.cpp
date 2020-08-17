#include "pch.h"
#include "RandomPlayer.h"


RandomPlayer::RandomPlayer() {

}

bool RandomPlayer::getWinStatus() {
	return isWinner;
}

char** RandomPlayer::getMyBoard() {
	return myBoard.getBoard();
}

char** RandomPlayer::getEnemyBoard() {
	return enemyBoard.getBoard();
}

std::vector<Ship*> &RandomPlayer::getShips() {
	return ships;
}

void RandomPlayer::setShips() {
	int numberOfShips = 1;
	int numberOfDecks = 4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < numberOfShips; j++) {
			setDecks(numberOfDecks);
		}
		numberOfDecks--;
		numberOfShips++;
	}
	printBoards(myBoard.getBoard(), enemyBoard.getBoard());
}

void RandomPlayer::setDecks(int numberOfDecks) {
	std::string coordinates, letter, number;
	std::string direction;
	bool setIsCorrect = false;

	while (!setIsCorrect) {
		letter += std::to_string(rand() % 10);
		coordinates += letter;
		number += std::to_string(rand() % 10);
		coordinates += number;
		if (numberOfDecks != 1) {
			if (rand() % 2 == 0)
				direction += "d";
			else
				direction += "r";
		}

		if (checkSetting(coordinates, direction, numberOfDecks) == -1) {
			coordinates.clear();
			letter.clear();
			number.clear();
			direction.clear();
		}
		else
			setIsCorrect = true;
	}

	if (direction == "d") {
		ships.emplace_back(new Ship);
		for (int i = coordinates[1] - '0'; i < coordinates[1] - '0' + numberOfDecks; i++) {
			myBoard.getBoard()[i][coordinates[0] - '0'] = '+';
			ships[ships.size() - 1]->getShipCoords().emplace_back(std::make_pair(i, coordinates[0] - '0'));
		}
	}
	else if (direction == "r") {
		ships.emplace_back(new Ship);
		for (int i = coordinates[0] - '0'; i < coordinates[0] - '0' + numberOfDecks; i++) {
			myBoard.getBoard()[coordinates[1] - '0'][i] = '+';
			ships[ships.size() - 1]->getShipCoords().emplace_back(std::make_pair(coordinates[1] - '0', i));
		}
	}
	else {
		myBoard.getBoard()[coordinates[1] - '0'][coordinates[0] - '0'] = '+';
		ships.emplace_back(new Ship);
		ships[ships.size() - 1]->getShipCoords().emplace_back(std::make_pair(coordinates[1] - '0', coordinates[0] - '0'));
	}
}

int RandomPlayer::checkSetting(std::string coordinates, std::string direction, int numberOfDecks) {
	char letter = coordinates[0] - '0';
	char number = coordinates[1] - '0';
	char upperLast, rightLast, leftLast, downLast, downLength, rightLength;

	if (direction == "d") {
		downLength = (number + numberOfDecks - 1);
		if (downLength > 9)
			return -1;
		if ((upperLast = number - 1) < 0)
			upperLast = 0;
		if ((leftLast = letter - 1) < 0)
			leftLast = 0;
		if ((rightLast = letter + 1) > 9)
			rightLast = 9;
		if ((downLast = number + numberOfDecks) > 9)
			downLast = 9;
	}
	else if (direction == "r") {
		rightLength = (letter + numberOfDecks - 1);
		if (rightLength > 9)
			return -1;
		if ((upperLast = number - 1) < 0)
			upperLast = 0;
		if ((leftLast = letter - 1) < 0)
			leftLast = 0;
		if ((rightLast = letter + numberOfDecks) > 9)
			rightLast = 9;
		if ((downLast = number + 1) > 9)
			downLast = 9;
	}
	else {
		if ((upperLast = number - 1) < 0)
			upperLast = 0;
		if ((leftLast = letter - 1) < 0)
			leftLast = 0;
		if ((rightLast = letter + 1) > 9)
			rightLast = 9;
		if ((downLast = number + 1) > 9)
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

void RandomPlayer::attack(IPlayer *enemy) {
	bool isMissed = false;
	std::string coordinates, letter, number;

	while (!isMissed && !isWinner) {
		letter += std::to_string(rand() % 10);
		coordinates += letter;
		number += std::to_string(rand() % 10);
		coordinates += number;
		if (checkHit(enemy->getMyBoard(), coordinates[1] - '0', coordinates[0] - '0') == 0) {
			coordinates.clear();
			letter.clear();
			number.clear();
		}
		else if (checkHit(enemy->getMyBoard(), coordinates[1] - '0', coordinates[0] - '0') == 1) {
			if (doIfHit(enemy, coordinates[1] - '0', coordinates[0] - '0') == 0) {
				isWinner = true;
				printBoards(myBoard.getBoard(), enemyBoard.getBoard());
			}
			coordinates.clear();
			letter.clear();
			number.clear();
		}
		else {
			enemyBoard.getBoard()[coordinates[1] - '0'][coordinates[0] - '0'] = 'O';
			enemy->getMyBoard()[coordinates[1] - '0'][coordinates[0] - '0'] = 'O';
			isMissed = true;
		}
	}
}

int RandomPlayer::doIfHit(IPlayer *enemy, int xCoord, int yCoord) {
	enemyBoard.getBoard()[xCoord][yCoord] = '+';
	enemy->getMyBoard()[xCoord][yCoord] = 'X';

	std::vector<Ship*> &enemyShips = enemy->getShips();
	for (int i = 0; i < enemyShips.size(); i++) {
		std::vector<std::pair<int, int>> &coordsOfShips = enemyShips[i]->getShipCoords();
		std::vector<std::pair<int, int>> &killedCoords = enemyShips[i]->getKilledCoords();
		for (int j = 0; j < coordsOfShips.size(); j++) {
			if (coordsOfShips[j] == std::make_pair(xCoord, yCoord)) {
				coordsOfShips.erase(coordsOfShips.begin() + j);
				killedCoords.emplace_back(std::make_pair(xCoord, yCoord));

				int checkKill = checkKilling(coordsOfShips, enemyShips, i);
				if (checkKill == 0) {
					for (int i = 0; i < killedCoords.size(); i++)
						enemyBoard.getBoard()[killedCoords[i].first][killedCoords[i].second] = 'X';
					return 0;
				}
				else if (checkKill == -1) {
					return 1;
				}
				else if (checkKill == 1) {
					for (int i = 0; i < killedCoords.size(); i++)
						enemyBoard.getBoard()[killedCoords[i].first][killedCoords[i].second] = 'X';
					return 1;
				}
			}
		}
	}
}

RandomPlayer::~RandomPlayer()
{
}
