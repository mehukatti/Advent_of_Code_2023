// Determine which numbers are gear ratios.
// Any number adjacent to a symbol, even diagonally, is a "gear ratio" and should be included in your sum. (Periods (.) do not count as a symbol.)

#include <iostream>
#include <cmath>

using std::cout;

bool is_char_integer(char character){
    int ia = character - '0';
    if (ia > -1 && ia < 10){
        return true;
    }
    return false;
}

bool is_char_gear(char character){
    char gear = '*';
    if (character == gear){
        return true;
    }
    return false;
}

int char_to_int(char character){
    int ia = character - '0';
    return ia;
}

bool pass_factor_check(int factor){
    if (!(factor == 1 || factor ==(-1))){
        cout << "Why the check is not passed? \n";
        cout << "factor: " << factor << ". factor != 1: " << (factor != 1) << ". factor !=(-1): " << (factor !=(-1)) <<"\n";
        throw 505;
    }
    return true;
}

bool pass_col_logic_test(int col){
    if (col>=0){
        return true;
    }
    cout << "Negative column \n";
    throw 505;
}

int get_furthest_column(const std::vector<char>& line_vec, int original_col, int factor){

    int column_number = original_col;
    while (is_char_integer(line_vec[column_number])){
        if ((column_number<0) || column_number>=line_vec.size()){
            break;
        }
        column_number = column_number + factor;
    }

    //take one out as while loop was true the previous number ago.
    column_number = column_number - factor;
    return column_number;
}

static std::vector<int> part_numbers_of_a_row(const std::vector<char>& line_vec, int gear_column){
    /*
    If there is part numbers in the row, there is one or two. No more. Get those in the row nearest to the gear.
    One row at a time.*/
    std::vector<int> adjacent_part_numbers_in_row;

    int number = 0;
    if (gear_column-1 >=0 && is_char_integer(line_vec[gear_column-1])){
        int start_column = get_furthest_column(line_vec, gear_column-1, -1);
        for (int a = start_column; a < gear_column;a++){
            number = number*10 + char_to_int(line_vec[a]);
        }
    }
    
    if (is_char_integer(line_vec[gear_column])){
        number = number*10 + char_to_int(line_vec[gear_column]);
    } else if (number>0){
        adjacent_part_numbers_in_row.push_back(number);
        number = 0;
    }


    if (gear_column+1<line_vec.size() && is_char_integer(line_vec[gear_column+1])){
        int end_column = get_furthest_column(line_vec, gear_column+1, 1);
        for (int a = gear_column+1; a <= end_column;a++){
            number = number*10 + char_to_int(line_vec[a]);
        }
        adjacent_part_numbers_in_row.push_back(number);
    } else if (number>0){
        adjacent_part_numbers_in_row.push_back(number);
    }

    return adjacent_part_numbers_in_row;
}

static std::vector<int> find_adjacent_part_numbers(const std::vector<std::vector<char> >& vec, int gear_row, int column){
    // find adjacent part numbers
    std::vector<int> adjacent_part_numbers;

    for (int row = gear_row - 1; row <= gear_row + 1; row++){
        if ((row < 0)  && (row < vec.size())){
            continue; // out of bounds
        }

        // determine the part numbers
        std::vector<int> adjacent_part_numbers_in_row;
        adjacent_part_numbers_in_row = part_numbers_of_a_row(vec[row], column);
        for (int i=0;i < adjacent_part_numbers_in_row.size();i++){
            adjacent_part_numbers.push_back(adjacent_part_numbers_in_row[i]);
        }
    }
    return adjacent_part_numbers;
}

static std::vector<int> determine_gear_ratios(const std::vector<std::vector<char> >& vec)
{
	cout << "Determine gear ratios" << "\n";

    //create empty array for gear ratios
    static std::vector<int> gear_ratios;
    int gear_counter = 0;
    
    //iterate the vector to find out gear ratios aka numbers adjagent to suitable characters
    for (int i = 0;i < vec.size(); i++)
    { // by rows
        for (int j = 0;j < vec.size(); j++)
        { // by characters in the row
            if (!(is_char_gear(vec[i][j]))){
                continue; // continue until gear encountered
            }
            gear_counter++;

            // create necessary variables for memorizing values
            std::vector<int> adjacent_part_numbers{};

            // find all adjacent part numbers for this gear
            adjacent_part_numbers = find_adjacent_part_numbers(vec, i, j);

            // is there only two part numbers?
            if (adjacent_part_numbers.size()!=2){
                continue;
            }
            
            // if yes, multiply and add the gear ratio to gear ratios.
            gear_ratios.push_back(adjacent_part_numbers[0]*adjacent_part_numbers[1]);
            
        }
    }
	return gear_ratios;
}