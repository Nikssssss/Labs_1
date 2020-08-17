#pragma once
#include <cstring>

class Board
{
private:
	char **board;
public:
	Board();
	char **getBoard();
	~Board();
};

