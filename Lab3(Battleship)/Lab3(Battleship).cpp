#include "pch.h"
#include "GameLauncher.h"
#include "ConsolePlayer.h"
#include "RandomPlayer.h"
#include "OptimalPlayer.h"

int main() {
	/*std::string name1, name2;
	ConsolePlayer player1;
	ConsolePlayer player2;

	std::cout << "Enter the 1 player's name:" << std::endl;
	std::getline(std::cin, name1);
	system("cls");
	std::cout << "Enter the 2 player's name:" << std::endl;
	std::getline(std::cin, name2);
	system("cls");

	std::cout << name1 << ", set your Ships!" << std::endl << std::endl;
	system("pause");
	system("cls");
	player1.setShips();
	system("cls");

	std::cout << name2 << ", set your Ships!" << std::endl << std::endl;
	system("pause");
	system("cls");
	player2.setShips();
	system("cls");

	while (1) {
		std::cout << name1 << "'s turn to attack!" << std::endl << std::endl;
		system("pause");
		system("cls");

		player1.attack(&player2);
		if (player1.getWinStatus()) {
			std::cout << name1 << " won!!! Congratulations! Krasauchik!" << std::endl;
			break;
		}
		system("cls");

		std::cout << name2 << "'s turn to attack!" << std::endl << std::endl;
		system("pause");
		system("cls");

		player2.attack(&player1);
		if (player2.getWinStatus()) {
			std::cout << name2 << " won!!! Congratulations! Krasauchik!" << std::endl;
			break;
		}
		system("cls");
	}*/

	srand(time(0));
	RandomPlayer player1;
	RandomPlayer player2;
	
	GameLauncher launcher(&player1, &player2);
	launcher.launch();

	
	/*srand(time(0));
	ConsolePlayer player;
	RandomPlayer bot;

	std::string name;
	std::cout << "Please, enter your name:" << std::endl;
	std::getline(std::cin, name);
	system("cls");

	std::cout << name << ", set your Ships!" << std::endl << std::endl;
	system("pause");
	system("cls");
	player.setShips();
	system("cls");

	bot.setShips();
	std::cout << "Bot has set his Ships!" << std::endl;
	system("pause");
	system("cls");

	while (1) {
		std::cout << name << ", it's your turn to attack!" << std::endl;
		system("pause");
		system("cls");

		player.attack(&bot);
		if (player.getWinStatus()) {
			std::cout << name << " won!!! Congratulations! Krasauchik!" << std::endl;
			break;
		}
		std::cout << "You missed. It's Bot's turn to attack!" << std::endl;
		system("pause");
		system("cls");

		bot.attack(&player);
		if (bot.getWinStatus()) {
			std::cout << "Bot won! You can try again!" << std::endl;
			break;
		}
		system("cls");
	}*/

	/*srand(time(NULL));
	OptimalPlayer player;
	player.setShips();*/

	return 0;
}