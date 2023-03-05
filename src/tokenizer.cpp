#include <string>
#include <iostream>
#include <list>
#include <unordered_set>
#include <unordered_map>
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

struct TokenizerState
{
    int line_in_file;
    int scope_level;
    std::string file;
    std::string::iterator current_char;
    std::string::iterator beginning_of_lexeme;
};


void match(TokenizerState &ts, char chr)
{
    ts.beginning_of_lexeme = ts.current_char;
    while (*ts.current_char != chr)
    {
        ts.current_char++;
    }
}



std::list<Token> tokenizer(std::string file)
{
    std::list<Token> tokens;
    TokenizerState ts;
    ts.line_in_file = 1;
    ts.scope_level = 0;
    ts.current_char = file.begin();
    ts.beginning_of_lexeme = ts.current_char;

    while (ts.current_char != file.end())
    {
        if (*ts.current_char == '\n')
        {
            ts.line_in_file++;
            ts.current_char++;
            continue;
        }
        // Ignore white spaces and go to the next character;
        if (is_white_space(*ts.current_char))
        {
            ts.current_char++;
            continue;
        }

        if (*ts.current_char == '@')
        {
            ts.current_char++;
            match(ts, '{');
            tokens.emplace_back(
                buid_token(BIB_TYPE, ts.beginning_of_lexeme, ts.current_char)
            );
            continue;
        }

        if (*ts.current_char == '{')
        {
            
        }

        ts.current_char++;
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

