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
    int copy_num; // For part b of day 4. Does not bother the part a calculations
};

class LotteryCards
{
public:
    string card_path;
    // The following contains data after running read_cards()
    std::vector<Card> card_structure; // structure of cards read from a file

    void read_cards()
    {
        cout << "Reading the file:"<< card_path << "\n";

        //variables for saving the file contents into a single string
        std::string line;
        

        std::ifstream MyReadFile(card_path);
        cout << "reading the lines" << "\n";
        while( getline(MyReadFile, line) ){
            struct Card card = create_card_struct(line);
            card_structure.push_back(card);
        }
        MyReadFile.close();
        //test_reading_card_structure(card_structure);
        return;
    }

    void determine_winned_copies_part_b(){
        // iterate all cards and add number of winned copies to the following cards
        for (int i=0;i < card_structure.size();i++){
            struct Card card_from_vector = card_structure[i];

            cout << "card_id = " << card_from_vector.card_id << "\n";
            int winned_copies = winned_copies_per_card(card_from_vector);
            cout << "winned_copies = " << winned_copies << "\n";

            if (i + winned_copies + 1 > card_structure.size()){
                // If you won more copies than cards left, remove the extra copies to not go over the vector size
                winned_copies = card_structure.size()-i-1;
            }
            // if any copies were winned, add one copy to the following cards in the structure
            for (int index_to_copy=i+1; index_to_copy <= i + winned_copies; index_to_copy++){
                struct Card card_to_copy = card_structure[index_to_copy];
                card_to_copy.copy_num = card_to_copy.copy_num + card_from_vector.copy_num;
                card_structure[index_to_copy] = card_to_copy; // Need to update it back to the vector
            }
            
            cout << "\n\n";
        }
        return;
    }

    int total_copies_part_b(){
        // Run this after running determine_winned_copies_part_b
        int total_copies = 0;
        for (int i=0;i < card_structure.size();i++){
            struct Card card_from_vector = card_structure[i];
            total_copies = total_copies + card_from_vector.copy_num;
        }
        cout << "total copies = " << total_copies << "\n";
        return total_copies;
    }

    void determine_points_for_part_a(){
        // Fort part a of the day 4
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

    void test_reading_card_structure(std::vector<Card>& card_structure){
        // For testing purposes
        // Argument: Card Struct
        // Function: Prints the card structure that
        cout << "The card struct: \n";
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
            cout << "\n";

            cout << "copy_num = " << card_from_vector.copy_num << "\n";
            cout << "\n\n";
        }
        return;
    }

private:
    std::vector<int> integers_to_vector(std::string& str)
    {
        // Arguments: string of numbers separated by spaces
        // Return vector of those numbers as integers
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
        card.copy_num = 1; // You always have one copy at the start.

        return card;
    }

    int winned_copies_per_card(Card& card){
        // Fort part A of the day 4
        int winned_number_of_copies = 0;
        cout << "winners: " << "\n";
        for (int j=0;j < card.card_numbers.size();j++){
            for (int z=0;z < card.winning_numbers.size();z++){
                // test if the card number matches the winning number
                if (card.card_numbers[j] != card.winning_numbers[z]){
                    continue;
                }
                cout << card.card_numbers[j] << " ";
                // If winning card is found, add one winned copy
                winned_number_of_copies++;
            }
        }
        return winned_number_of_copies;
    }

    int points_per_card(Card& card){
        // Fort part A of the day 4
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
};