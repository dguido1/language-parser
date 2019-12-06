
    /*
     Group Members:      David Guido, Tim, Bradley, Josh
     
     Course:             CPSC 323, Compilers and Languages
     Meeting Times:      T/TH 4:00pm - 5:15pm
     Due Date:           December 10, 2019 ??**
     Semester:           Fall 19'
     
     Assignment:         Group Project (Language Parser)
     
     Files Included:     1.) LanguageParser.cpp
     2.) LanguageParser.h
     3.) LanguageParserControl.cpp
     ****************************************************************
     */

    #include "LanguageParser.hpp"
    #include <fstream>
    #include <iostream>
    #include <cstdlib>
    #include <ctime>

    using namespace std;

    // Default Constructor
    // -> Namespace::Class
    LanguageParser::LanguageParser(){}

    void LanguageParser::FormatLanguage()
    {
        char current;  // value of current parse location
        int index = 0; // element number of current parse location
        
        while (dataFile.get(current)){
            switch(current)
            {
                case '\n':
                    
                    if (index == 0)   // Case: First parse
                    {
                        formattedInput = formattedInput + ' ' + ' ';
                        index += 2;
                        break;        // --> Remove single blank line on line 1, top of file
                    }
                    else if (formattedInput[index - 1] == '\n')   // Case: Double new line
                    {
                        //dataFile.get(current);   // Read in first char of new line
                        break;
                    }
                    else   // Case: Single newline
                    {
                        formattedInput += current;
                        ++index;
                        
                        dataFile.get(current);   // Read in first char of new line
                        
                        if (current != ' ')   // Case: First char of new line is not already a space
                        {
                            formattedInput += "  ";
                            index += 2;
                            break;
                        }
                        
                        break;
                        
                        
                        // Case: First char of new line is already a space, no need for else
                    }
                    
                case '\t':   // Case: Tab
                    break;
                    
                case ';':
                    if (formattedInput[index-1] == ' ')   // Case: Space before SC
                        formattedInput[index-1] = current;
                    else
                    {
                        formattedInput += current;   // Case: No space before SC
                        ++index;
                    }
                    break;
                    
                case '-':
                case '*':
                case '/':
                case '=':
                    
                    if (!(formattedInput[index - 1] == ' '))   // Case: Prev elem not a space
                    {
                        formattedInput += ' ';
                        ++index;
                        formattedInput += current;
                        ++index;
                        formattedInput += " ";
                        ++index;
                        break;
                    }
                    
                case '(':
                    dataFile.get(current);          // move forward to check for '*', the start of a comment
                    if (current != '*'){            // not a comment
                        dataFile.unget().unget();   // move parser back twice
                        dataFile.get(current);      // get the '(' value we just passed by
                        formattedInput +=  current; // append the '(' value
                        ++index;
                    }
                    else {                          // start of comment | move forward until comment close: '*)'
                        while (!(current == '*'))   // check for 1st of 2 symbols that represent the closing comment
                            dataFile.get(current);
                        while (!(current == ')'))   // check for 2nd of 2 symbols that represent the closing comment
                            dataFile.get(current);
                    }
                    break;
                case ' ':
                    if (formattedInput[index - 1] == ' ' ||
                        formattedInput[index - 1] == ';')
                    { break; }
                    /*case '\n':
                     if (formattedInput[index - 1] == '\n'){
                     if (formattedInput[index - 2] == '\n')
                     --index;
                     break;
                     }*/
                default:
                    if (formattedInput[index - 1] == '+' ||
                        formattedInput[index - 1] == '-' ||
                        formattedInput[index - 1] == '*' ||
                        formattedInput[index - 1] == '/' ||
                        formattedInput[index - 1] == '='){
                        formattedInput += ' ';
                        ++index;
                    }
                    formattedInput += current;
                    ++index;
                    break;
            }
        }
    }

    // Open File for input
    bool LanguageParser::OpenFileIn(string fileName){
        dataFile.open(fileName, ios::in);  // open fstream object for input
        return (!dataFile.fail());  // check if file is ready for input
    }

    // open File for output
    bool LanguageParser::OpenFileOut(string fileName){
        dataFile.open(fileName, std::ios_base::app);  // Open fstream obj for output (append mode)
        return (!dataFile.fail());  // Check if file is ready for output
    }

    // Write to file. If file isn't found, create it
    void LanguageParser::WriteFile(){
        if (dataFile)  // check if data file is open
            dataFile << formattedInput;
    }

    // Close file
    void LanguageParser::CloseFile(){
        dataFile.close();  // close current fstream object for input/output
    }

    // Flush file, causing stream buffer to flush its output buffer
    void LanguageParser::FlushFile(){
        dataFile.flush();
    }

    // Destructor
    LanguageParser::~LanguageParser(){}







    /*
     
     #include "LanguageParser.hpp"
     
     #include <fstream>
     #include <iostream>
     #include <cstdlib>
     #include <ctime>
     
     using namespace std;
     
     // Default Constructor
     // -> Namespace::Class
     LanguageParser::LanguageParser(){}
     
     void LanguageParser::FormatLanguage()
     {
     char current;    // Value of current parse location
     int index = 0;   // Element number of current parse location
     
     while (dataFile.get(current))
     {
     switch (current)
     {
     case '\t':
     break;
     
     
     case '-':
     case '*':
     case '/':
     case '=':
     
     if (!(formattedInput[index - 1] == ' '))   // If the prev elem is not a space
     {
     formattedInput += ' ';
     ++index;
     formattedInput += current;
     ++index;
     formattedInput += " ";
     ++index;
     
     break;
     }
     
     case ';':
     if (formattedInput[index-1] == ' ')
     {
     formattedInput[index-1] = current;
     }
     //else if (formattedInput[index+1] == ' ')
     //{
     
     //}
     else{
     formattedInput += current;
     ++index;
     }
     break;
     
     case '(':
     dataFile.get(current);   // Move foward to check for '*', the start of a comment
     
     if (current != '*')                 // Not a comment
     {
     dataFile.unget().unget();       // Move parser back twice
     dataFile.get(current);          // Get the '(' value we just passed by
     formattedInput +=  current;     // Appened the '(' value
     ++index;
     }
     else                                // Start of comment
     {                                   // Move forward until comment close: '*)'
     while (!(current == '*'))       // Check for 1st of 2 symbols that represent the closing comment
     dataFile.get(current);
     while (!(current == ')'))       // Check for 2nd of 2 symbols that represent the closing comment
     dataFile.get(current);
     }
     break;
     
     case ' ':
     if (formattedInput[index - 1] == ' ' || formattedInput[index - 1] == ';')
     break;
     
     case '\n':
     if (formattedInput[index - 1] == '\n')
     {
     if (formattedInput[index - 2] == '\n')
     --index;
     break;
     }
     
     default:
     
     if (formattedInput[index - 1] == '+' ||
     formattedInput[index - 1] == '-' ||
     formattedInput[index - 1] == '*' ||
     formattedInput[index - 1] == '/' ||
     formattedInput[index - 1] == '=')
     {
     formattedInput += ' ';
     ++index;
     
     }
     
     formattedInput += current;
     ++index;
     break;
     }
     
     
     
     }
     }
     
     
     // Open File for input
     bool LanguageParser::OpenFileIn(string fileName)
     {
     dataFile.open(fileName, ios::in);  // Open fstream obj for input
     
     return (!dataFile.fail());  // Check if file is ready for input
     }
     
     // Open File for output
     bool LanguageParser::OpenFileOut(string fileName)
     {
     dataFile.open(fileName, std::ios_base::app);  // Open fstream obj for output (append mode)
     
     return (!dataFile.fail());  // Check if file is ready for output
     }
     
     // Write to file. If file isn't found, create it
     void LanguageParser::WriteFile()
     {
     if (dataFile)  // Check if data file is open
     dataFile << formattedInput;
     }
     
     // Close file
     void LanguageParser::CloseFile()
     {
     dataFile.close();  // Close current fstream obj for input/output
     }
     
     // Flush file, causing stream buffer to flush its output buffer
     void LanguageParser::FlushFile()
     {
     dataFile.flush();
     }
     
     // Destructor
     LanguageParser::~LanguageParser(){}
     
     */
