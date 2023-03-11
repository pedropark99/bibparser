#include <string>
#include <unordered_set>
#include <iostream>


#include "global_variables.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"


bool is_white_space(char chr)
{
    bool white_space = chr == ' ' || chr == '\t' || chr == '\r' || chr == '\n';
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






int count_char(std::string &string, char chr)
{
    std::string::iterator current_char = string.begin();
    int n_of_occurrences = 0;
    while (current_char != string.end())
    {
        if (*current_char == chr)
        {
            n_of_occurrences++;
        }

        current_char++;
    }

    return n_of_occurrences;
}

void find_first_position(std::string &string, char chr)
{
    std::string::iterator it = string.begin();
    while (it != string.end())
    {
        if (*it == chr) {
            break;
        }

        it++;
    }
}

void print_substring(SubString substring)
{
    std::string s = std::string(substring.begin, substring.end);
    std::cout << s << std::endl;
}
