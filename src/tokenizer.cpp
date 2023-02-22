#include <string>
#include <iostream>
#include <list>
#include <unordered_set>
#include <ctype.h>

#include "read_bib.hpp"
#include "tokenizer.hpp"

const std::unordered_set<char> LETTERS = {
    u8'a', u8'b', u8'c', u8'd', u8'e', u8'f',
    u8'g', u8'h', u8'i', u8'j', u8'k', u8'l',
    u8'm', u8'n', u8'o', u8'p', u8'q', u8'r',
    u8's', u8't', u8'u', u8'v', u8'x', u8'w',
    u8'y', u8'z',
    
    u8'A', u8'B', u8'C', u8'D', u8'E', u8'F',
    u8'G', u8'H', u8'I', u8'J', u8'K', u8'L',
    u8'M', u8'N', u8'O', u8'P', u8'Q', u8'R',
    u8'S', u8'T', u8'U', u8'V', u8'X', u8'W',
    u8'Y', u8'Z'
};

const std::unordered_set<char> NUMBERS = {
    u8'0', u8'1', u8'2', u8'3', u8'4',
    u8'5', u8'6', u8'7', u8'8', u8'9'
};

const std::unordered_set<char> LINES = {
    u8'-', u8'_'
};


Token buid_token(Tag type_of_token,
                std::string::iterator begin_of_lexeme,
                std::string::iterator end_of_lexeme)
{
    std::string lexeme = std::string(begin_of_lexeme, end_of_lexeme);
    Token token(type_of_token, lexeme);
    return token;
}


std::list<Token> tokenizer(std::string file)
{
    std::list<Token> tokens;

    std::string::iterator forward = file.begin();
    std::string::iterator beginning_of_lexeme = forward;

    while (forward != file.end())
    {
        // Ignore white spaces and go to the next character;
        if (is_white_space(*forward))
        {
            forward++;
            continue;
        }

        if (*forward == '@') 
        {
            forward++;
            beginning_of_lexeme = forward;
            while (is_digit(*forward) | is_letter(*forward)) 
            {
                forward++;
            }
            tokens.emplace_back(buid_token(BIB_TYPE, beginning_of_lexeme, forward));
        }

        forward++;
    }

    return tokens;
}


bool is_white_space(char chr)
{
    if (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\r') 
    {
        return true;
    } 
    else 
    {
        return false;
    }
}

bool is_digit(char chr)
{
    if (NUMBERS.find(chr) != NUMBERS.end())
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
    if (LETTERS.find(chr) != LETTERS.end())
    {
        return true;
    }
    else 
    {
        return false;
    }

}


