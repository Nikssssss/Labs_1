#include "pch.h"
#include "Printer.h"

namespace {
	void printLetters() {
		for (char i = 'A'; i < 'K'; i++) {
			std::cout << i << std::setw(4);
		}
	}

	void printAllLetters() {
		std::cout << std::setw(9);
		printLetters();
		std::cout << std::setw(29);
		printLetters();
	}

	void printHorizontalLines(char middleEqual, char middleVert) {
		for (int k = 0; k < 41; k++) {
			k % 4 != 0 ? std::cout << middleEqual : std::cout << middleVert;
		}
	}

	void printValues(char vertEqual, int i, char** board) {
		if (i < 10) {
			std::cout << i << std::setw(2);
			for (int j = 0; j < 11; j++) {
				std::cout << vertEqual << std::setw(2);
				if (j < 10)
					std::cout << board[i][j] << std::setw(2);
			}
		}
	}

	void printUpperFrame(char leftUpCorner, char middleEqual, char rightUpCorner) {
		std::cout << std::endl;
		std::cout << std::setw(21) << leftUpCorner;
		for (int i = 0; i < 10; i++) {
			std::cout << middleEqual;
		}
		std::cout << rightUpCorner;

		std::cout << std::setw(53) << leftUpCorner;
		for (int i = 0; i < 13; i++) {
			std::cout << middleEqual;
		}
		std::cout << rightUpCorner;
		std::cout << std::endl;
	}

	void printNamesOfBoard(char vertEqual) {
		std::cout << std::setw(21) << vertEqual;
		std::cout << std::setw(9) << "My Board";
		std::cout << std::setw(2) << vertEqual;
		std::cout << std::setw(53) << vertEqual;
		std::cout << std::setw(12) << "Enemy Board";
		std::cout << std::setw(2) << vertEqual;
		std::cout << std::endl;
	}

	void printLowerFrame(char leftDownCorner, char middleEqual, char rightDownCorner) {
		std::cout << std::setw(21) << leftDownCorner;
		for (int i = 0; i < 10; i++) {
			std::cout << middleEqual;
		}
		std::cout << rightDownCorner;
		std::cout << std::setw(53) << leftDownCorner;
		for (int i = 0; i < 13; i++) {
			std::cout << middleEqual;
		}
		std::cout << rightDownCorner << std::endl;
	}
}

void printBoards(char** myBoard, char** enemyBoard) {
	unsigned char vertEqual = 186;
	unsigned char leftUpCorner = 201;
	unsigned char rightUpCorner = 187;
	unsigned char leftDownCorner = 200;
	unsigned char rightDownCorner = 188;
	unsigned char middleEqual = 205;
	unsigned char middleVert = 206;

	printUpperFrame(leftUpCorner, middleEqual, rightUpCorner);
	printNamesOfBoard(vertEqual);
	printLowerFrame(leftDownCorner, middleEqual, rightDownCorner);

	printAllLetters();
	for (int i = 0; i < 11; i++) {
		std::cout << std::endl << std::setw(7);
		printHorizontalLines(middleEqual, middleVert);
		std::cout << std::setw(25);
		printHorizontalLines(middleEqual, middleVert);

		std::cout << std::setw(0) << std::endl;

		std::cout << std::setw(5);
		printValues(vertEqual, i, myBoard);
		std::cout << std::setw(23);
		printValues(vertEqual, i, enemyBoard);
	}
	std::cout << std::setw(0) << std::endl;
}

