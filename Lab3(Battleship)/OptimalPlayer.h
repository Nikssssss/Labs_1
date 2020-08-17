#pragma once
#include "IPlayer.h"
#include <random>
#include <ctime>

class OptimalPlayer : public IPlayer
{
private:
	bool isWinner = false;
	Board myBoard;
	Board enemyBoard;
	std::vector<Ship*> ships;
	char **getMyBoard();
	char **getEnemyBoard();
	std::vector<Ship*> &getShips();
	void setFourDeckShip();
	void setMiddleDeckShips(int numberOfDecks);
	void setOneDeckShips();
	void createShip(int firstCoord, int secondCoord, int direction, int numberOfDecks);
	int checkSetting(int firstCoord, int secondCoord, int direction, int numberOfDecks);
public:
	OptimalPlayer();
	bool getWinStatus();
	void setShips();
	void attack(IPlayer *enemy);
	~OptimalPlayer();
};

