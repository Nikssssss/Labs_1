#pragma once
#include "IPlayer.h"

class GameLauncher
{
private:
	IPlayer *player1;
	IPlayer *player2;
public:
	GameLauncher(IPlayer *first, IPlayer *second) 
		: player1(first), player2(second) {
	}
	void launch();
	~GameLauncher();
};

