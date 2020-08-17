#pragma once
#include <vector>

class Ship
{
private:
	std::vector<std::pair<int, int>> coordsOfShip;
	std::vector<std::pair<int, int>> killedCoords;
public:
	Ship();
	std::vector<std::pair<int, int>> &getShipCoords() {
		return coordsOfShip;
	}
	std::vector<std::pair<int, int>> &getKilledCoords() {
		return killedCoords;
	}
	~Ship();
};

