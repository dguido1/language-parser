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
*/

#ifndef LanguageParser_hpp
#define LanguageParser_hpp

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
using namespace std;
    class LanguageParser
    {
        public:

            string rawData;
            string formattedInput;
            fstream dataFile;                     // FStream Obj, used for input/output of file
        
            LanguageParser();                     // Default Constructor
            
            void HandleInput();                   // Just calls following 4 functions
        
            void ReadFile();
            void RemoveComments();
            void RemoveWhitespace();
            void AddSpacing();

            bool OpenFileIn(string fileName);     // Open fstream obj for input
            bool OpenFileOut(string fileName);    // Open fstream obj for output (append mode)

            void CloseFile();                     // Close current fstream obj for input/output
            void WriteFile();                     // Write to file, if it isn't found, create it
            void FlushFile();                     // Flush file, causing stream buffer
                                                  // to flush its output buffer
            ~LanguageParser();                    // Destructor
    };


#endif
