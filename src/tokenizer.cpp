#include <string>
#include <iostream>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <regex>


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


int count_char(char chr)
{
    std::string::iterator current_char = bibparser::bib_file.begin();
    int n_of_occurrences = 0;
    while (current_char != bibparser::bib_file.end())
    {
        if (*current_char == chr)
        {
            n_of_occurrences++;
        }

        current_char++;
    }

    return n_of_occurrences;
}

void find_first_position(std::string::iterator &it, char chr)
{
    while (it != bibparser::bib_file.end())
    {
        if (*it == chr) {
            break;
        }

        it++;
    }
}


std::vector<std::string> collect_bib_entries(std::string file)
{
    int n_of_entries = count_char('@');
    std::vector<std::string> bib_entries;
    bib_entries.reserve(n_of_entries);
    int entries_allocated = 0;
    
    std::string::iterator begin = file.begin();
    std::string::iterator end = file.end();
    std::string::iterator current_char = begin;
    // Move iterator to first bib entry
    while (current_char != end)
    {
        if (*current_char == '@')
        {
            current_char++;
            begin = current_char;
            break;
        }
        current_char++;
    }

    while (current_char != end)
    {
        if (*current_char == '@' & entries_allocated < n_of_entries - 2)
        {
            std::string entry = std::string(begin, current_char);
            bib_entries.emplace_back(entry);
            entries_allocated++;
            current_char++;
            begin = current_char;
            continue;
        }

        // Get last bib entry in the file
        if ((current_char + 1) == end)
        {
            std::string entry = std::string(begin, current_char);
            bib_entries.emplace_back(entry);
            entries_allocated++;
            current_char++;
            begin = current_char;
            break;
        }

        current_char++;
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

