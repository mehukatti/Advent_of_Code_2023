//Read input file into a variable and return said variable.

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class LotteryCardsTester
{
public:
    string card_path;
    std::vector<std::vector<char>> card_file_vector;

    void read_cards()
    {
        cout << "Reading the file:"<< card_path << "\n";

        //variables for saving the file contents into a single string
        std::string line;

        std::ifstream MyReadFile(card_path);
        cout << "reading the lines" << "\n";
        while( getline(MyReadFile, line) ){
            card_file_vector.push_back(std::vector<char>(line.begin(), line.end())); //line is broken into vector containing the characters. The line vector is saved in the card_file_vector vector
        }
        MyReadFile.close();

        cout << "The input file: \n";
        for (int i=0;i < card_file_vector.size();i++){
            for (int j=0;j < card_file_vector[i].size();j++){
                cout << card_file_vector[i][j];
            }
            cout << "\n";
        }
        
        return;
    }
};