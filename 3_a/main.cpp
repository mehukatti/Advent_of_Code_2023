// C++ to solve the day 3 part a of advent of code 2023 https://adventofcode.com/2023/day/3

#include <iostream>
#include<numeric>

#include "h_files/file_reader.h"
#include "h_files/part_numbers.h"
using std::cout;

int main()
{
	cout << "Solving the puzzle of advent of code 2023 day 3 part one. \n";

	// std::vector is an array
	static std::vector<std::vector<char> > svec;
	svec = read_file("input.txt");

	static std::vector<int> part_numbers;
	part_numbers = determine_part_numbers(svec);
	cout << "The numbers: \n";
	for (int i=0;i < part_numbers.size();i++){
		cout << part_numbers[i] << "\n";
	}
	cout << "The sum of parts: " << accumulate(part_numbers.begin(),part_numbers.end(),0);
	return 0;
}
