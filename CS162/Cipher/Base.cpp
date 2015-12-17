#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <cstdlib>
#include <string>
#include <vector>
#include "Base.h"

/***********************************************************************************
Purpose: Base function take characters from input file, filter and place in output
file

In: File objects for input and output files
Out: None

************************************************************************************/

void Base::doFilter(std::ifstream &in, std::ofstream &out)
{
    in.open("inputFile.txt", std::ios::in);
    out.open("outputFile.txt", std::ios::out);

    if(!in)
    //check if input file exists
    {
            cout << "Input File does not exist" << endl;
            exit(1);
    }
    if(!out)
    //check if output file exists
    {
        cout << "Output File does not exist" << endl;
        exit(1);
    }

    char ch, transCh;               //characters to hold file char input and transformed char
    std::vector <char> input;       //vector to hold transformed characters

    ch = in.get();
    //take character from input file

    while(!in.fail())
    //if character remain in file, transform and place in input vector
    {
        transCh = transform(ch);
        input.push_back(transCh);
        in.get(ch);
    }

    for(int i = 0; i < input.size(); i++)
    //store char from input vector to output file
    {
        cout << input[i];
        out << input[i];
    }
    cout << endl;

    in.close();
    //close input file
    out.close();
    //close output file
}

/*********************************************************************************
Purpose: Base function for transforming character

In: Character from file
Out: Returns same character to doFilter
*********************************************************************************/

char BaseCopy::transform(char ch) const
{
    return ch;
}

/*********************************************************************************
Purpose: Change character to upper case

In: Character from file
Out: Returns upper case version of character
**********************************************************************************/

char UpperCase::transform(char ch) const
{
    ch = toupper(ch);
    //change character to uppercase
    return ch;
}

/**********************************************************************************
Purpose: Uses simple encryption to change character to new character based on key
input. Punctuations, numbers and spaces are all changed to new characters as well

In: Character from file
Out: Returns adjusted character based on key

**********************************************************************************/

char Encrypt::transform(char ch) const
{
    int charValue = int(ch);
    //get ascii value of character
    int asciiChange;
    //adjustment for char value based on whether it is upper or lower case

    if (charValue >= 65 && charValue <= 90)
    //check if character is upper case and adjust based on key value
    {
        asciiChange = 65;
        ch = (char)((((charValue - asciiChange) + key) % 26) + asciiChange);
    }
    else if (charValue >= 97 && charValue <= 122)
    //check if character is lower case and adjust based on key value
    {
        asciiChange = 97;
        ch = (char)((((charValue - asciiChange) + key) % 26) + asciiChange);
    }

    else if(isspace(ch))
    //check if character is space and change to m
    {
        ch = 'm';
    }

    else if(isdigit(ch) || ispunct(ch))
    //check if character is punctuation or number and change to s
    {
        ch = 's';
    }

   return ch;
}

/************************************************************************************
Purpose: Function to take characters from input file, encrypt and place in output
file. Output file is different from output file for base class

In: File objects for input and output files
Out: None
************************************************************************************/
/*
void Encrypt::doFilter(std::ifstream &in, std::ofstream &out)
{
    in.open("inputFile.txt", std::ios::in);
    out.open("encryptFile.txt", std::ios::out);
    //open file objects

    if(!in)
    //check if input file exists
    {
        cout << "Input File does not exist" << endl;
        exit(1);
    }
    if(!out)
    //check if output file exists
    {
        cout << "Output File does not exist" << endl;
        exit(1);
    }

    std::vector<char> input;        //vector to hold file inputs
    char ch, encryptCh;             //char to hold ch from input file and encrypted char
    ch = in.get();                  //get character from input file

    while(!in.fail())
    //encrypt character and store to input vector
    {
        encryptCh = encryptFile(ch);
        input.push_back(encryptCh);
        in.get(ch);
    }

    for(int i = 0; i < input.size(); i++)
    //store character from input vector to output file
    {
        cout << input[i];
        out << input[i];
    }
    cout << endl;

    in.close();
    out.close();
    //close file objects
}
*/
/*******************************************************************************************
Purpose: Function to take characters from input file, change to ciphertext and place in
output file. Output file is different from output file for base class and encrypt class

In: File objects for input and output files
Out: None

*******************************************************************************************/

void Ciphertext::cipherFile(std::ifstream &in, std::ofstream &out)
{
    in.open("encryptFile.txt", std::ios::in);
    out.open("cipherFile.txt", std::ios::out);
    //open files

    if(!in)
    //check if input file exists
    {
        cout << "Encrypted Input File does not exist perform encryption first" << endl;
        exit(1);
    }
    if(!out)
    //check if output file exist
    {
        cout << "Output File does not exist" << endl;
        exit(1);
    }

    std::vector<char> input;        //vector to hold char inputs
    char ch, transCh;               //char to hold char from file, encrypted char and uppercase char
    ch = in.get();                  //get char from input file

    while(!in.fail())
    //change to upper case and store to input vector
    {
        transCh = transform(ch);
        input.push_back(transCh);
        in.get(ch);
    }

    int counter = 0;                //counter for counting numbers in a row

    for(int i = 0; i < input.size(); i++)
    {
            if (counter < 5)
            //if less than 5 letters in a row store char from vector to output file and increment counter
            {
                out << input[i];
                cout << input[i];
                counter++;
            }

            else if (counter == 5)
            //if 5th letter in a row place space then output char to file
            {
                out << " " << input[i];
                cout << " " << input[i];
                counter = 1;
            }
    }
    cout << endl;

    in.close();
    out.close();
    //close files
}
