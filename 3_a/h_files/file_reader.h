//Read input file into a variable and return said variable.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

static std::vector<std::vector<char>> read_file(const std::string& filename)
{
    cout << "Reading the file:"<< filename << "\n";

    //variables for saving the file contents into a single string
    static std::vector<std::vector<char>> svec;
    std::string line;

    std::ifstream MyReadFile(filename);
    cout << "reading the lines" << "\n";
    while( getline(MyReadFile, line) ){
        svec.push_back(std::vector<char>(line.begin(), line.end())); //line is broken into vector containing the characters. The line vector is saved in the svec vector
    }
    MyReadFile.close();
    
    return svec;
}