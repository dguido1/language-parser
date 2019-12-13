# Language Parser

### CPSC 323 Group Project
#### &nbsp;&nbsp;&nbsp;&nbsp;Made by [@dguido1](https://github.com/dguido1), [@TimothyBui](https://github.com/TimothyBui), [@imjoshy](https://github.com/dguido1) & [@BradK14](https://github.com/BradK14)
#### &nbsp;&nbsp;&nbsp;&nbsp;at [***California State University Fullerton***](http://www.fullerton.edu/)<br><br>&nbsp;&nbsp;&nbsp;&nbsp;Fall 19'

---
<br>

## Table of contents
* [Language Parser](#language-parser)
  * [What it does](#what-it-does)  
  * [Instructions](#instructions)
  * [Starter Program](#starter-program)
  * [Steps](#steps)
***
<br>

## What it does
* ***Inputs*** a text file with 'program code'
* ***Removes*** extra white space & comments
* ***Outputs*** an intermediate code translation in the form of a C++ program
---

<br>

## Instructions
* Have a program that
  * ***Reads*** in the text file [`final.txt`](/final.txt)
  * ***Formats*** it properly
  * ***Outputs*** the result to a second text file [`revised.txt`](/revised.txt)
  * ***Command*** *make strip* will take *final.txt* and strip it of whitespace and comments
  
* ***Specifies*** production rules using *Flex/Bison*
* ***Translates*** the program into a *high level* programming language (C++)
* ***Command for Flex/Bison*** *make parse* will take the new *revised.txt* file, parse it, and convert it into working C++ code
* ***Runs*** [`abc13.cpp`](/abc.cpp) using the C++ compiler to the correct output
---

<br>

## Starter Program
#### &nbsp;&nbsp;&nbsp; Suppose that the context of the text file [`final.txt`](/final.txt) is<br>
  
```
	(*  Program Name: Spring 2014
	     Final Project
	     Name: Nathan Reed
	---------------------------------------------------*)
	PROGRAM aba13;
	VAR

	   ab5,  cb  ,  be, eb: INTEGER; (* declare variables *)
	BEGIN
	   ab5   =  5    ;
	   cb  =10;
	   PRINT(‘ab5=’,    ab5);
	(* compute and print the total of a and c  *)
	   eb=  cb + ab5  ;
	   PRINT(‘eb=’   ,eb )  ;

	   be  -  2*abc5 +  eb;
	   PRINT(   be  )   ;
	END.
```

---


<br>

## Steps
#### 1. Remove all *documentation*, *blank lines*, and *extra spaces* from the program
   * You are going to use this program to *check the grammar of each statement*
   
<br>
 
   * The program should look like the *following*
```
  PROGRAM aba13;
  VAR
  ab5, cb, be, eb : INTEGER;
  BEGIN
  ab5 = 5;
  cb = 10;
  PRINT(‘ab5=’, ab5);
  cb = cb + ab5;
  PRINT( cb );
  be = 2 * ab5 + eb;
  PRINT( be );
  END.
```
---

<br>

#### 2. Specify *production rules* in *Flex/Bison*
 * Given the following *CFG* (some rules are in *EBNF* form)

```
<start> →PROGRAM<pname>; VAR ,<dec-list>; BEGIN <stat-list> END.
<pname>     → <id>
<id>        → <letter>{<letter>|<digit>}
<dec-list>  → <dec> : <type>
<dec>       → <id>, <dec> | <id>

<stat-list> → <stat>; | <stat>; <stat-list>
<stat>      → <print> | <assign>
<print>     → PRINT (<output>)
<output>    → [“string”,} <id>
<assign>    → <id> = <expr>

<expr>      → <term> | <expr> + <term> | <expr> - <term>
<term>      → <term> * <factor> | <term> / <factor> | <factor>
<factor>    → <id> | <number> | <( <expr> )
<number>    → <digit>{<digit>}
<type>      → INTEGER
<digit>     → 0|1|2|…|9
<letter>    → a|b|c|d|e|f
```

* Where **PROGRAM**, **VAR**, **BEGIN**, **END**. , **INTEGER**, **PRINT** are *reserved words*, and all *uppercase*.
<br>

* *Flex/bison* should print out the *errors*, but MANUALLY fix the errors
* Your job is to use the given grammar and determine whether the program is *accepted* or *not*
   * i.e. Whether there *are* or *aren’t syntax errors* in the program.
<br>

* Your program should produce *one of the following error messages* as soon as the error is *detected*
```
	PROGRAM is expected (if PROGRAM is missing or spelled wrong)
	VAR     is expected (if VAR is missing or spelled wrong)
	BEGIN   is expected (if BEGIN is missing ir spelled wrong)
	END.    is expected (if END. is missing or spelled wrong)
	UNKNOWN IDENTIFIER if variable is not defined

	;       ; is missing
	‘       ‘ is missing
	.       . is missing
	(       ( is missing
	)       ) is missing
	,       , is missing
	=       = is missing
```
---

<br>

 
#### 3. If there are no errors in the program, *translate* the program into a C++/or another *high level* programming language
  * Store the C++ program as 
  [`abc13.cpp`](/abc.cpp) <br><br>

* Your C++ program should look like *this*
``` c++
#include <iostream>
Using namespace std;
int main()
{
int ab5, cb, be, eb;
ab5 = 5
cout << ”ab5=” << ab5;
eb = cb + ab5;
cout << eb;
be = 2 * ab5 + eb;
cout << be;
return 0;
}
```
---

<br>

#### 4. If you run the [`abc13.cpp`](/abc.cpp) file using the C++ compiler, we should be able to see the correct output

<br>
<br>
