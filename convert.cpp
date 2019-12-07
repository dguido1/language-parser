#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>        //std::erase and std::remove
#include <cstdio>           //remove
/*  File that should be converted:
        PROGRAM aba13;
        VAR
        ab5, cb, be, eb : INTEGER;
        BEGIN
        ab5 = 5;
        cb = 10;
        PRINT(‘ab5=’, ab5);
        cb = cb + ab5;
        PRINT( ‘eb=’, eb );
        be = 2 * ab5 + eb;
        PRINT( be );
        END.
    Expected output:
        #include <iostream>
        using namespace std;
        int main()
        {
        int ab5, cb, be, eb;
        ab5 = 5
        cb = 10;
        cout << ”ab5=” << ab5;
        eb = cb + ab5;
        cout << eb;
        be = 2 * ab5 + eb;
        cout << be;
        return 0;
}

*/
bool exists(std::string filename) {
    std::ifstream checkfile(filename);
    bool result;
    result = checkfile ? true : false;
    checkfile.close();
    return result;
}

int main(int argc, const char* argv[]) {
    if(exists("abc13.cpp")) {           //Remove file if it already exists
        remove("abc13.cpp");
    }
    std::ifstream infile(argv[1]);
    std::ofstream outfile;
    std::string word;

    std::string variable_names[10], data_type;
    int i = 0;

    infile >> word;     // PROGRAM
    if(strcmp(word.c_str(), "PROGRAM") == 0) {
        infile >> word;         // abc13;
        word.erase(std::remove(word.begin(), word.end(), ';'), word.end());     //src: https://stackoverflow.com/questions/20326356/how-to-remove-all-the-occurrences-of-a-char-in-c-string
        word.append(".cpp");
        outfile.open(word);     //abc13.cpp

        //Start the .cpp file
        outfile << "#include <iostream>\n\nusing namespace std;\n\n" << "int main(int argc, const char* argv[]) {\n\n";
    }
    else {
        std::cerr << "File must start with the program name!\n";        //Write to cerr
        infile.close();
        exit(1);
    }
    if(!outfile.is_open()) {
        std::cerr << "Error creating file \"abc13.cpp\"!\n";
        infile.close();
        exit(1);
    }
    infile >> word;         //VAR
    if(strcmp(word.c_str(), "VAR") == 0) {

        while(strchr(word.c_str(), ':') == NULL) {
            infile >> word;
            variable_names[i++] = word;
        }
        i--;        //Since the last input from the above loop will be the :
        const int variables = i;
        // for(int j = 0; j <= variables; ++j) {
        //     std::cout << variable_names[j] << " ";
        // }
        infile >> word;
        if(strstr(word.c_str(), "INTEGER") == NULL) {       //Means the next input from file does not include "INTEGER"
            std::cerr << "Error! Current word " << word << " != \"INTEGER;\"!\n";
            infile.close();
            outfile.close();
            exit(1);
        }
        else {
            data_type = "int";
        }
        outfile << data_type;
        int j = 0;
        while(j < variables) {
            outfile << " " << variable_names[j++];
        }
        outfile << ";\n";
    }
    infile >> word;
    if(strcmp(word.c_str(), "BEGIN") != 0) {
        std::cerr << "Error! Current word " << word << " != \"BEGIN\"!\n";
        infile.close();
        outfile.close();
        exit(1);
    }
    while(1) {
        infile >> word;

        //TO DO: buggy asf
        if(strstr(word.c_str(), "PRINT") != NULL) {     //Case 1 is to print
            outfile << "cout << ";
            while(strchr(word.c_str(), ';') == NULL) {
                std::string::iterator sit = word.begin();
                if(*sit != '\'') {
                    ++sit;
                    outfile << "\"";
                    while(*sit != '\'' && sit != word.end()) {
                        outfile << *sit;
                        ++sit;
                    }
                    outfile << "\";";
                }
                infile >> word;
            }
        }
        else if(strstr(word.c_str(), "END.") != NULL) {
            break;
        }
        else {      //Case 2 is assignment operation
            while(strchr(word.c_str(), ';') == NULL) {
                outfile << word << " ";
                infile >> word;
            }
            outfile << word;
        }
        outfile << "\n";
    }

/*
#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {

int ab5, cb, be, eb;ab5=5;

*/
    


    //End the .cpp file
    outfile << "\nreturn 0;\n}";
    infile.close();
    outfile.close();
    return 0;
}