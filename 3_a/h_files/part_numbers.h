// Determine which numbers are part numbers.
// Any number adjacent to a symbol, even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not count as a symbol.)

#include <iostream>

using std::cout;

bool is_char_integer(char character){
    int ia = character - '0';
    if (ia > -1 && ia < 10){
        return true;
    }
    return false;
}

int char_to_int(char character){
    int ia = character - '0';
    return ia;
}

bool is_acceptable_char(char character){
    // return true if the character is either not dot or not a digit.
    char dot = '.';
    if ((character==dot)  || (is_char_integer(character))){
        //cout << " the character is dot or digit: " << character << "\n";
        return false;
    } else {
        //cout << " the character is ok: " << character << "\n";
        return true;
    }
}

bool is_this_part(const std::vector<std::vector<char> >& svec, int i, int j){
    for (int row = i - 1; row <= i + 1; row++){
        for (int column = j - 1; column <= j + 1; column++) {
            if ((row > 0)  && (column > 0)  && (row < svec.size()) && (column < svec[i].size())){
                char dot = '.';
                if (is_acceptable_char(svec[row][column])){
                    return true;
                }
            }
        }
    }
    return false;
}

static std::vector<int> determine_part_numbers(const std::vector<std::vector<char> >& svec)
{
	cout << "Determine part numbers" << "\n";

    //create empty array for part numbers
    static std::vector<int> part_numbers;
    
    //iterate the vector to find out part numbers aka numbers adjagent to suitable characters
    for (int i = 0;i < svec.size(); i++)
    { // by rows
        int j = 0;
        while (j < svec[i].size())
        { // by characters in the row
        char character = svec[i][j];
            if (!(is_char_integer(svec[i][j]))){
                j++;
                continue;
            }

            // create necessary variables for memorizing values
            static bool is_part = false;
            const int start_column = j;
            //char is integer
            while (is_char_integer(svec[i][j])){

                // check if it is a part number.
                if (is_part == false && is_this_part(svec, i, j)){
                    is_part = true;
                }
                j++;
            }
            // add the number into the vector
            if (is_part){
                static int number = 0;
                for (int col = start_column; col <j;col++){
                    number = number*10 + char_to_int(svec[i][col]);
                }
                part_numbers.push_back(number);
                cout << "The part number:" << number << "\n";

                // reset for next round
                number = 0;
                is_part = false;
            }
        }
        cout << "\n";
    } 
	return part_numbers;
}