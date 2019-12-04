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
    ****************************************************************
    ****************************************************************

    To Do:
    *******

    COMPLETED:
        Strip the extra whitespace, newline, and comments
    INCOMPLETE:
        Insert spaces around the operations
        Case ,'
        Case where the end is a ; and there is a space
        Case where the end is a ';' and there is a space before it

    */

    #include <iostream>   // C++ library imports
    #include <fstream>
    #include <string>

    #include "LanguageParser.hpp"   // Custom class imports

    using namespace std;

    bool FileExists(string inputFileName);   // Declarations
    bool FileContainsContent(string inputFileName);
    void ParseHandler ();

    Parser::LanguageParser langParserInstance;   // Single instance obj, namespace: 'Parser'

    int main()   // Entry point
    {
        if (langParserInstance.OpenFileIn("final.txt"))
        {
            langParserInstance.FormatLanguage();
            langParserInstance.CloseFile();
            langParserInstance.OpenFileOut("revised.txt");
            langParserInstance.WriteFile();
        }

        return 0;   // Exit point
    }
