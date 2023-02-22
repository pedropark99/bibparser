#include <string>
#include <iostream>
#include <list>
#include <unordered_set>
#include <ctype.h>


#include "global_variables.hpp"
#include "read_bib.hpp"
#include "tokenizer.hpp"


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
    size_t line_in_file = 1;
    size_t scope_level = 0;
    std::string::iterator forward = file.begin();
    std::string::iterator beginning_of_lexeme = forward;

    while (forward != file.end())
    {
        if (*forward == '\n') {
            line_in_file++;
            forward++;
            continue;
        }
        // Ignore white spaces and go to the next character;
        if (is_white_space(*forward))
        {
            forward++;
            continue;
        }

        switch (*forward)
        {
        case '@':
            forward++;
            beginning_of_lexeme = forward;
            while (is_digit(*forward) | is_letter(*forward)) 
            {
                forward++;
            }
            tokens.emplace_back(buid_token(BIB_TYPE, beginning_of_lexeme, forward));
            break;

        case '{':
            scope_level++;
            forward++;
            if (scope_level == 1)
            {
                get_bib_identifier(beginning_of_lexeme, forward);
            }
            // If scope_level > 1, is probably a attribute value of the reference
            // We should handle these later...
            break;

        case '}':
            scope_level--;
            forward++;
            break;
        
        
        default:
            forward++;
            break;
        }
    }

    return tokens;
}


bool is_white_space(char chr)
{
    bool white_space = chr == ' ' || chr == '\t' || chr == '\r';
    return white_space ? true : false;
}

bool is_digit(char chr)
{
    return find_in_set(chr, NUMBERS);
}

bool is_letter(char chr)
{
    return find_in_set(chr, LETTERS);
}

bool is_line(char chr)
{
    return find_in_set(chr, LINES);
}

bool find_in_set(char chr, const std::unordered_set<char>& set)
{
    return set.find(chr) != set.end() ? true : false;
}




void get_bib_identifier(std::string::iterator& begin_of_lexeme, std::string::iterator& forward)
{
    // Do stuff
}