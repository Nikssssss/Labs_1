#include "pch.h"
#include "ConsolePlayer.h"


ConsolePlayer::ConsolePlayer() {
	
}

bool ConsolePlayer::getWinStatus() {
	return isWinner;
}

char** ConsolePlayer::getMyBoard() {
	return myBoard.getBoard();
}

char** ConsolePlayer::getEnemyBoard() {
	return enemyBoard.getBoard();
}

std::vector<Ship*> &ConsolePlayer::getShips() {
	return ships;
}

void ConsolePlayer::setShips() {
	printBoards(myBoard.getBoard(), enemyBoard.getBoard());
	std::cout << "Enter the first coordinates and the direction of your ship (down(d), right(r))." << std::endl;
	std::cout << "For example: enter the first coordinates - A0, enter direction - d" << std::endl << std::endl;
	int numberOfShips = 1;
	char numberOfDecks = '4';
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < numberOfShips; j++) {
			std::cout << "Please, set your " << numberOfDecks << "-deck ship!" << std::endl << std::endl;
			setDecks(numberOfDecks - '0');
		}
		numberOfDecks--;
		numberOfShips++;
	}
	/*for (int i = 0; i < ships.size(); i++) {
		std::vector<std::pair<int, int>> vector = ships[i]->getShipCoords();
		for (int i = 0; i < vector.size(); i++) {
			std::cout << vector.size();
			std::cout << vector[i].first << ' ' << vector[i].second << std::endl;
		}
		std::cout << std::endl;
	}*/
}

void ConsolePlayer::setDecks(int numberOfDecks) {
	std::string coordinates;
	std::string direction;
	bool setIsCorrect = false;

	while (!setIsCorrect) {
		std::cout << "Enter the first coordinates of your ship (first - letter, second - number, e.g.: A0):" << std::endl;
		std::getline(std::cin, coordinates);
		if (numberOfDecks != 1) {
			std::cout << "Enter the direction of your ship (d, r):" << std::endl;
			std::getline(std::cin, direction);
		}

		if (checkSetting(coordinates, direction, numberOfDecks) == -1) {
			system("cls");
			printBoards(myBoard.getBoard(), enemyBoard.getBoard());
			std::cout << "Enter the correct coordinates!" << std::endl << std::endl;
			coordinates.clear();
			direction.clear();
		}
		else
			setIsCorrect = true;
	}

	if (direction == "d" || direction == "D") {
		ships.emplace_back(new Ship);
		for (int i = coordinates[1] - '0'; i < coordinates[1] - '0' + numberOfDecks; i++) {
			myBoard.getBoard()[i][letterToNumber(coordinates)] = '+';
			ships[ships.size() - 1]->getShipCoords().emplace_back(std::make_pair(i, letterToNumber(coordinates)));
		}
	}
	else if (direction == "r" || direction == "R") {
		ships.emplace_back(new Ship);
		for (int i = letterToNumber(coordinates); i < letterToNumber(coordinates) + numberOfDecks; i++) {
			myBoard.getBoard()[coordinates[1] - '0'][i] = '+';
			ships[ships.size() - 1]->getShipCoords().emplace_back(std::make_pair(coordinates[1] - '0', i));
		}
	}
	else {
		myBoard.getBoard()[coordinates[1] - '0'][letterToNumber(coordinates)] = '+';
		ships.emplace_back(new Ship);
		ships[ships.size() - 1]->getShipCoords().emplace_back(std::make_pair(coordinates[1] - '0', letterToNumber(coordinates)));
	}
	system("cls");
	printBoards(myBoard.getBoard(), enemyBoard.getBoard());
}

char ConsolePlayer::letterToNumber(std::string coordinates) {
	char letter;
	coordinates[0] <= 'J' ? letter = coordinates[0] - 'A' : letter = coordinates[0] - 'a';
	return letter;
}

int ConsolePlayer::checkSetting(std::string coordinates, std::string direction, int numberOfDecks) {
	if (direction.size() > 1)
		return -1;
	else if (checkCoordinates(coordinates) == -1)
		return -1;
	else if (numberOfDecks != 1 && direction[0] != 'd' && direction[0] != 'r' && direction[0] != 'D' && direction[0] != 'R')
		return -1;
	else if (checkAround(coordinates, direction, numberOfDecks) == -1)
		return -1;

	return 1;
}

int ConsolePlayer::checkCoordinates(std::string coordinates) {
	if (coordinates.size() > 2)
		return -1;
	else if ((coordinates[0] < 'A' || coordinates[0] > 'J') && (coordinates[0] < 'a' || coordinates[0] > 'j'))
		return -1;
	else if (coordinates[1] < '0' || coordinates[1] > '9')
		return -1;

	return 1;
}

int ConsolePlayer::checkAround(std::string coordinates, std::string direction, int numberOfDecks) {
	char letter = letterToNumber(coordinates);
	char number = coordinates[1] - '0';
	char upperLast, rightLast, leftLast, downLast, downLength, rightLength;

	if (direction == "d" || direction == "D") {
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
	else if (direction == "r" || direction == "R"){
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

void ConsolePlayer::attack(IPlayer *enemy) {
	bool isMissed = false;
	std::string coordinates;

	printBoards(myBoard.getBoard(), enemyBoard.getBoard());
	while (!isMissed && !isWinner) {
		std::cout << "Enter the coordinates you want to attack:" << std::endl;
		std::getline(std::cin, coordinates);
		if (checkCoordinates(coordinates) == -1) {
			system("cls");
			printBoards(myBoard.getBoard(), enemyBoard.getBoard());
			std::cout << "Enter the correct coordinates!" << std::endl << std::endl;
			coordinates.clear();
		}
		else if (checkHit(enemy->getMyBoard(), coordinates[1] - '0', letterToNumber(coordinates)) == 0) {
			system("cls");
			printBoards(myBoard.getBoard(), enemyBoard.getBoard());
			std::cout << "You've already hit this cell. Try again!" << std::endl << std::endl;
			coordinates.clear();
		}
		else if (checkHit(enemy->getMyBoard(), coordinates[1] - '0', letterToNumber(coordinates)) == 1) {
			if (doIfHit(enemy, coordinates[1] - '0', letterToNumber(coordinates)) == 0) {
				isWinner = true;
				system("cls");
				printBoards(myBoard.getBoard(), enemyBoard.getBoard());
			}
			coordinates.clear();
		}
		else {
			enemyBoard.getBoard()[coordinates[1] - '0'][letterToNumber(coordinates)] = 'O';
			enemy->getMyBoard()[coordinates[1] - '0'][letterToNumber(coordinates)] = 'O';
			std::cout << "Missed!" << std::endl << std::endl;
			isMissed = true;
		}
	}
}

int ConsolePlayer::doIfHit(IPlayer *enemy, int xCoord, int yCoord) {
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
					system("cls");
					printBoards(myBoard.getBoard(), enemyBoard.getBoard());
					std::cout << "Hit!" << std::endl << std::endl;
					return 1;
				}
				else if (checkKill == 1) {
					for (int i = 0; i < killedCoords.size(); i++)
						enemyBoard.getBoard()[killedCoords[i].first][killedCoords[i].second] = 'X';
					system("cls");
					printBoards(myBoard.getBoard(), enemyBoard.getBoard());
					std::cout << "Killed!" << std::endl << std::endl;
					return 1;
				}
			}
		}
	}
}

ConsolePlayer::~ConsolePlayer()
{
}
