// C++ to solve the day 3 part a of advent of code 2023 https://adventofcode.com/2023/day/3

// Learning test driven development and C++ classes

#include <iostream>

#include "h_files/lottery_card_checker.h"
using std::cout;

int main()
{
	cout << "Solving the puzzle of advent of code 2023 day 4 part one. \n";
	LotteryCards CardsOfElf;

	CardsOfElf.card_path = "input.txt";
	CardsOfElf.read_cards();

	// check points from winning numbers
	CardsOfElf.determine_points();
	return 0;
}
