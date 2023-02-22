#include <string>
#include <iostream>
#include <ctype.h>


#include "read_bib.hpp"
#include "tokenizer.hpp"

enum TAG
{
    BIB_IDENTIFIER = 5234,
    BIB_TYPE = 5233,
    BIB_ATTRIBUTE = 5235
};



void tokenizer(void)
{
    std::string::iterator forward = bibparser::bib_file.begin();
    std::string::iterator beginning_of_lexeme = forward;

    while (forward != bibparser::bib_file.end())
    {
        // Ignore white spaces and go to the next character;
        if (is_white_space(*forward))
        {
            forward++;
            continue;
        }

        if (*forward == '@') {
            beginning_of_lexeme = forward++;
            while (is_digit(*forward) | is_letter(*forward)) {
                forward++;
            }
        }

        forward++;
    }
}


bool is_white_space(char chr)
{
    if (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\r') {
        return true;
    } 
    else 
    {
        return false;
    }
}

bool is_digit(char chr)
{
    if (isdigit(chr))
    {
        return true;
    } 
    else 
    {
        return false;
    }
}

bool is_letter(char chr)
{
    

}