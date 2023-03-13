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


bool starts_with(const std::string &string, const std::string start)
{
    return string.rfind(start, 0) == 0;
}

bool ends_with (const std::string &string, const std::string end) {
    if (string.length() >= end.length()) {
        return ( 0 == string.compare(string.length() - end.length(), end.length(), end) );
    } else {
        return false;
    }
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

int count_char(SubString sub, char chr)
{
    std::string::iterator current_char = sub.begin;
    int n_of_occurrences = 0;
    while (current_char != sub.end)
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


void trim_substring(SubString &sub)
{
    std::string::iterator begin = sub.begin;
    std::string::iterator end = sub.end;

    if (begin == end)
    {
        return;
    }

    std::string::iterator current_char = begin;
    while (is_white_space(*(current_char + 1)))
    {
        current_char++;
    }
    begin = current_char;

    current_char = end;
    while (is_white_space(*(current_char - 1)))
    {
        current_char--;
    }
    end = current_char;

    sub.begin = begin;
    sub.end = end;
}

void trim_substring(Token &token)
{
    std::string::iterator begin = token.value.begin;
    std::string::iterator end = token.value.end;

    if (begin == end)
    {
        return;
    }

    std::string::iterator current_char = begin;
    while (is_white_space(*(current_char + 1)))
    {
        current_char++;
    }
    begin = current_char;

    current_char = end;
    while (is_white_space(*(current_char - 1)))
    {
        current_char--;
    }
    end = current_char;

    token.value.begin = begin;
    token.value.end = end;
}



std::string substring_to_string(SubString substring)
{
    std::string str;
    if (substring.begin == substring.end)
    {
        str = std::string(1, *substring.end);
    } 
    else
    {
        str = std::string(substring.begin, substring.end);
    }
    return str;
}


void print_substring(SubString substring)
{
    std::cout << substring_to_string(substring) << std::endl;
}



std::vector<SubString> split_substring(SubString sub, const char delimiter)
{
    std::string::iterator begin = sub.begin;
    std::string::iterator end = sub.end;
    std::string::iterator current_char = sub.begin;

    int n = count_char(sub, delimiter);
    std::vector<SubString> substrings;
    if (n == 0)
    {
        substrings.emplace_back(sub);
        return substrings;
    }
    substrings.reserve(n);

    while (current_char != end)
    {
        if (*current_char == delimiter)
        {
            SubString sub = {begin, current_char};
            substrings.emplace_back(sub);
            current_char++;
            begin = current_char;
            continue;
        }
        current_char++;
    }

    SubString last_substring = {begin, current_char};
    substrings.emplace_back(last_substring);

    return substrings;
}