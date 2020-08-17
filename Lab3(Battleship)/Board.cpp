#include "pch.h"
#include "Board.h"


Board::Board() {
	board = new char*[10];
	for (int i = 0; i < 10; i++) {
		board[i] = new char[10];
		memset(board[i], ' ', 10);
	}
}

char **Board::getBoard() {
	return board;
}

Board::~Board() {
	for (int i = 0; i < 10; i++) {
		delete board[i];
	}
	delete[] board;
}
