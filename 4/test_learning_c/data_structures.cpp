#include <iostream>
#include <vector>

using namespace std;
 
struct Card {
    int card_id;
    std::vector<int> winning_numbers;
    std::vector<int> card_numbers;
};
 
int main()
{
    //Card   1: 13  4 61 82 80 41 31 53 50  2 | 38 89 26 79 94 50  2 74 31 92 80 41 13 97 61 82 68 45 64 39  4 53 90 84 54
    struct Card card1 = {};
    card1.card_id = 1;
    card1.winning_numbers = { 13, 4, 61, 82, 80, 41, 31, 53, 50, 2 };
    card1.card_numbers = { 38, 89, 26, 79, 94, 50, 2, 74, 31, 92, 80, 41, 13, 97, 61, 82, 68, 45, 64, 39, 4, 53, 90, 84, 54 };
    
    //Card   2: 25 44 86 77 98 91 55 39 63 12 | 84 62 55 28 99 26 19 18 13 57 97 63 20 65 24 31 72 41 77 27 50 30 38  3 88
    struct Card card2 = {};
    card2.card_id = 2;
    card2.winning_numbers = { 25, 44, 86, 77, 98, 91, 55, 39, 63, 12 };
    card2.card_numbers = { 84, 62, 55, 28, 99, 26, 19, 18, 13, 57, 97, 63, 20, 65, 24, 31, 72, 41, 77, 27, 50, 30, 38, 3, 88 };

    // create vector containing structures
    std::vector<Card> cards;
    cards.push_back(card1);
    cards.push_back(card2);

    // print the cards

    cout << "The input file: \n";
    for (int i=0;i < cards.size();i++){
        struct Card card = cards[i];
        cout << "card_id = " << card.card_id << "\n";

        cout << "winning_numbers = " << "\n";
        for (int i=0;i < card.winning_numbers.size();i++){
            cout << card.winning_numbers[i] << " ";
        }
        cout << "\n";

        cout << "card_numbers = " << "\n";
        for (int i=0;i < card.card_numbers.size();i++){
            cout << card.card_numbers[i] << " ";
        }
        cout << "\n\n";
    }
 
    return 0;
}