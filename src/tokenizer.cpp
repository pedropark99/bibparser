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

struct LexerState
{
    int line_in_file;
    int scope_level;
    std::string::iterator current_char;
};

struct LexerState lexer_st = {
    .line_in_file = 1,
    .scope_level = 0,
    .current_char = bibparser::bib_file.begin()
};



std::array<std::string::iterator, 2> look_ahead(char chr)
{
    std::array<std::string::iterator, 2> iterators;
    std::string::iterator begin = lexer_st.current_char;
    std::string::iterator end = lexer_st.current_char;

    while (*end != chr | end != bibparser::bib_file.end())
    {
        end++;
    }

    iterators[0] = begin;
    iterators[1] = end;

    return iterators;
}


char next(int n = 1)
{
    for (int i = 0; i < n; i++)
    {
        lexer_st.current_char++;
    }
    return *lexer_st.current_char;
}


std::list<std::string> collect_bib_entries(std::string file)
{
    std::list<std::string> bib_entries;
    
    while (lexer_st.current_char != file.end())
    {
        if (*lexer_st.current_char == '@') {
            std::array<std::string::iterator, 2> portion = look_ahead('@');
            std::string entry = std::string(portion[0], portion[1]);
            std::cout << "Entry: " << entry << std::endl << std::endl;
            bib_entries.emplace_back(entry);
        }

        lexer_st.current_char++;
    }

    return bib_entries;
}


std::list<Token> tokenizer(std::string file)
{
    std::list<Token> tokens;
    


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

