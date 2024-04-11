//Read input file into a variable and return said variable.

#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
using namespace std;

struct Card {
    int card_id;
    std::vector<int> winning_numbers;
    std::vector<int> card_numbers;
};

class LotteryCards
{
public:
    string card_path;
    std::vector<std::vector<char>> card_file_vector;
    std::vector<Card> card_structure;

    void read_cards()
    {
        cout << "Reading the file:"<< card_path << "\n";

        //variables for saving the file contents into a single string
        std::string line;
        

        std::ifstream MyReadFile(card_path);
        cout << "reading the lines" << "\n";
        while( getline(MyReadFile, line) ){
            card_file_vector.push_back(std::vector<char>(line.begin(), line.end())); //line is broken into vector containing the characters. The line vector is saved in the card_file_vector vector
            struct Card card = create_card_struct(line);
            card_structure.push_back(card);
        }
        MyReadFile.close();
        //test_reading_card_structure(card_structure);
        return;
    }

    void determine_points(){
        int total_points = 0;
        for (int i=0;i < card_structure.size();i++){
            struct Card card_from_vector = card_structure[i];

            cout << "card_id = " << card_from_vector.card_id << "\n";
            int card_points = points_per_card(card_from_vector);
            total_points = total_points + card_points;
            
            cout << "\n\n";
        }
        cout << "Total points: " << total_points << endl;
        return;
    }
    
    int points_per_card(Card& card){
        int card_points = 0;
        cout << "winners: " << "\n";
        for (int j=0;j < card.card_numbers.size();j++){
            for (int z=0;z < card.winning_numbers.size();z++){
                // test if the card number matches the winning number
                if (card.card_numbers[j] != card.winning_numbers[z]){
                    continue;
                }
                cout << card.card_numbers[j] << " ";
                if (card_points==0){
                    card_points=1;
                } else {
                    card_points = card_points*2;
                }
            }
        }
        return card_points;
    }

    void test_reading_card_structure(std::vector<Card>& card_structure){
        cout << "The input file: \n";
        for (int i=0;i < card_structure.size();i++){
            struct Card card_from_vector = card_structure[i];

            cout << "card_id = " << card_from_vector.card_id << "\n";

            cout << "winning_numbers = " << "\n";
            for (int j=0;j < card_from_vector.winning_numbers.size();j++){
                cout << card_from_vector.winning_numbers[j] << " ";
            }
            cout << "\n";

            cout << "card_numbers = " << "\n";
            for (int j=0;j < card_from_vector.card_numbers.size();j++){
                cout << card_from_vector.card_numbers[j] << " ";
            }
            cout << "\n\n";
        }
        return;
    }

private:
    std::vector<int> integers_to_vector(std::string& str)
    {
        std::vector<int> numbers;

        std::regex words_regex("[[:digit:]]+");
        auto words_begin = std::sregex_iterator(str.begin(), str.end(), words_regex);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            int match_int = stoi(match.str());
            numbers.push_back(match_int);
        }
        return numbers;
    }

    Card create_card_struct(std::string& card_string){
        // Assumes the following input type:
        // Card   1: 13  4 61 82 80 41 31 53 50  2 | 38 89 26 79 94 50  2 74 31 92 80 41 13 97 61 82 68 45 64 39  4 53 90 84 54
        // Card   2: 25 44 86 77 98 91 55 39 63 12 | 84 62 55 28 99 26 19 18 13 57 97 63 20 65 24 31 72 41 77 27 50 30 38  3 88

        // Look for the card id
        // It is the number between "Card" and the colon. "Card" is 4 letters long
        int colon_position = card_string.find(":");
        int card_id = stoi( card_string.substr(4, colon_position - 4) );

        // Get the winning numbers from the string
        int vertical_bar_index = card_string.find("|");
        string winning_number_string = card_string.substr(colon_position, vertical_bar_index - colon_position);
        std::vector<int> winning_numbers = integers_to_vector(winning_number_string);

        // get the card numbers from the line
        string card_numbers_string = card_string.substr(vertical_bar_index, card_string.length()-1);
        std::vector<int> card_numbers = integers_to_vector(card_numbers_string);

        // create the structure
        struct Card card = {};
        card.card_id = card_id;
        card.winning_numbers = winning_numbers;
        card.card_numbers = card_numbers;

        return card;
    }
};