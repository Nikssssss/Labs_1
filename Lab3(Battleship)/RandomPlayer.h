#pragma once
#include "IPlayer.h"
#include <random>
#include <ctime>

class RandomPlayer : public IPlayer
{
private:
	bool isWinner = false;
	Board myBoard;
	Board enemyBoard;
	std::vector<Ship*> ships;
	char** getMyBoard();
	char** getEnemyBoard();
	std::vector<Ship*> &getShips();
	void setDecks(int numberOfDecks);
	int checkSetting(std::string coordinates, std::string direction, int numberOfDecks);
	int doIfHit(IPlayer *enemy, int xCoord, int yCoord);
public:
	RandomPlayer();
	bool getWinStatus();
	void setShips();
	void attack(IPlayer *enemy);
	~RandomPlayer();
};

