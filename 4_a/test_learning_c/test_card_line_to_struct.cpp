#include <iostream>
#include <vector>
#include <regex>

using namespace std;

std::vector<int> integers_to_vector(std::string& str)
{
    std::vector<int> numbers;

    std::regex words_regex("[[:digit:]]+");
    auto words_begin = std::sregex_iterator(str.begin(), str.end(), words_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        int match_int = stoi(match.str());
        std::cout << match_int << '\n';
        numbers.push_back(match_int);
    }
    return numbers;
}

int main() {
    //Card   1: 13  4 61 82 80 41 31 53 50  2 | 38 89 26 79 94 50  2 74 31 92 80 41 13 97 61 82 68 45 64 39  4 53 90 84 54
    //Card   2: 25 44 86 77 98 91 55 39 63 12 | 84 62 55 28 99 26 19 18 13 57 97 63 20 65 24 31 72 41 77 27 50 30 38  3 88
    string card_string = "Card   1: 13  4 61 82 80 41 31 53 50  2 | 38 89 26 79 94 50  2 74 31 92 80 41 13 97 61 82 68 45 64 39  4 53 90 84 54";

    // Look for the card id
    // It is the number between "Card" and the colon. "Card" is 4 letters long
    int colon_position = card_string.find(":");
    int card_id = stoi( card_string.substr(4, colon_position - 4) );
    cout << "The card_id: " << card_id << "\n";

    // Get the winning numbers from the string
    int vertical_bar_index = card_string.find("|");
    string winning_number_string = card_string.substr(colon_position, vertical_bar_index - colon_position);
    cout << "The winning numbers: " << winning_number_string << "\n";
    std::vector<int> winning_numbers = integers_to_vector(winning_number_string);

    // get the card numbers from the line
    string card_numbers_string = card_string.substr(vertical_bar_index, card_string.length()-1);
    cout << "The card numbers: " << card_numbers_string << "\n";
    std::vector<int> card_numbers = integers_to_vector(card_numbers_string);

    return 0;
}