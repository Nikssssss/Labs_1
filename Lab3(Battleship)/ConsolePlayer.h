#pragma once
#include "IPlayer.h"

class ConsolePlayer : public IPlayer
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
	char letterToNumber(std::string coordinates);
	int checkSetting(std::string coordinates, std::string direction, int numberOfDecks);
	int checkCoordinates(std::string coordinates);
	int checkAround(std::string coordinates, std::string direction, int numberOfDecks);
	int doIfHit(IPlayer *enemy, int xCoord, int yCoord);
public:
	ConsolePlayer();
	bool getWinStatus();
	void setShips();
	void attack(IPlayer *enemy);
	~ConsolePlayer();
};
