#pragma once
#include "Ship.h"
#include "Printer.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

class IPlayer
{
public:
	IPlayer();
	virtual bool getWinStatus() = 0;
	virtual char **getMyBoard() = 0;
	virtual char **getEnemyBoard() = 0;
	virtual std::vector<Ship*> &getShips() = 0;
	virtual void setShips() = 0;
	virtual void attack(IPlayer *enemy) = 0;
	int checkHit(char **enemyBoard, int xCoord, int yCoord);
	int checkKilling(std::vector<std::pair<int, int>> &coordsOfShip, std::vector<Ship*> &ships, int indexOfShip);
	bool shipIsDead(std::vector<std::pair<int, int>> &coordsOfShips);
	bool playerIsLost(std::vector<Ship*> &ships);
	~IPlayer();
};

