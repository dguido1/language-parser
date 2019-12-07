    /*
     Group Members:      David Guido, Tim, Bradley, Josh
     
     Course:             CPSC 323, Compilers and Languages
     Meeting Times:      T/TH 4:00pm - 5:15pm
     Due Date:           December 15, 2019
     Semester:           Fall 19'
     
     Assignment:         Group Project (Language Parser)
     
     Files Included:     1.) LanguageParser.cpp
                         2.) LanguageParser.h
                         3.) LanguageParserControl.cpp
     ****************************************************************/

    #include <iostream>   // C++ library imports
    #include <fstream>
    #include <string>

    #include "LanguageParser.hpp"   // Custom class imports

    using namespace std;

    bool FileExists(string inputFileName);   // Declarations
    bool FileContainsContent(string inputFileName);
    void ParseHandler ();
    bool exist(std::string filename) ;   //Function to check if file exists


    LanguageParser langParserInstance;   // Single instance obj, namespace: 'Parser'

    int main()   // Entry point
    {
        if(exist("revised.txt"))
            remove("revised.txt");
        
        if (langParserInstance.OpenFileIn("final.txt"))
        {
            langParserInstance.HandleInput();
            
            langParserInstance.CloseFile();
            langParserInstance.OpenFileOut("revised.txt");
            langParserInstance.WriteFile();
        }
        
        return 0;   // Exit point
    }

    bool exist(std::string filename)
    {
        bool result;
        std::ifstream infile;
        infile.open(filename);
        result = (infile ? true : false);   //If infile could be opened, it exists so RETURN TRUE, else RETURN FALSE
        infile.close();
        return result;
    }
