// C++ to solve the day 3 part a of advent of code 2023 https://adventofcode.com/2023/day/3

#include <iostream>
#include <numeric>

#include "h_files/file_reader.h"
#include "h_files/part_numbers.h"
using std::cout;

int main()
{
	cout << "Solving the puzzle of advent of code 2023 day 3 part two. \n";

	static std::vector<std::vector<char> > vec;
	vec = read_file("input.txt");

	static std::vector<int> gear_ratio;
	gear_ratio = determine_gear_ratios(vec);

	//This time, you need to find the gear ratio of every gear and add them all up so that the engineer can figure out which gear needs to be replaced.
	cout << "The sum of gear ratios: " << accumulate(gear_ratio.begin(),gear_ratio.end(),0) << "\n";
	return 0;
}
