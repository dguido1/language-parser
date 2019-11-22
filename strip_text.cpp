/*
    strip_text.cpp:
        Receive input file ("final.txt")
        Parse through, removing excess white space and comments
        Output the edited text into a new file ("revised.txt")

    COMPLETED:
        Strip the extra whitespace, newline, and comments
    INCOMPLETE:
        Insert spaces around the operations
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

std::ifstream inFile;
std::string input = "";
std::string ops [] = {'+', '-', '*', '/'};
bool exist(std::string filename) {        //Function to check if file exists
    bool result;
    std::ifstream infile;
    infile.open(filename);
    result = (infile ? true : false);       //If infile could be opened, it exists so RETURN TRUE, else RETURN FALSE
    infile.close();
    return result;
}

void parse() {
    char c, d;
    int i = 0;

    if(inFile.get(c)) {
        input += c;
        ++i;
    }
    else {
        std::cout << "ERROR! File empty!\n";
        return;
    }

    while(inFile.get(c)) {
        if(c == ' ') {
            if(input[i - 1] == ' ') {
                continue;
            }
            else {
                input += c;
                ++i;
                continue;
            }
        }
        else if(c == '\n') {
            if(input[i - 1] == '\n') {
                continue;
            }
            else {
                input += c;
                ++i;
                continue;
            }
        }
        else if(c == '(') {
            inFile.get(d);
            if(d == '*') {
                d = c;
                inFile.get(c);
                while(c != ')' && d != '*') {
                    d = c;
                    inFile.get(c);
                }
            }
            else {
                input += c;
                ++i;
                input += d;
                ++i;
            }
        }

        else if(c == )

        else {
            input += c;
            ++i;
        }
    }

    inFile.close();
}

int main(int argc, const char* argv[]) {
    inFile.open("final.txt");

    parse();

    if(exist("revised.txt")) {
        remove("revised.txt");
    }

    std::ofstream outFile("revised.txt");
    outFile << input;


    outFile.close();
    return 0;
}
