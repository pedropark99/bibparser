#include <unordered_set>
#include <string>
#include <filesystem>
#include <iostream>


#include "tokenizer.hpp"
#include "string_utils.hpp"



namespace bibparser {



bool is_white_space(char chr)
{
    bool white_space = chr == ' ' || chr == '\t' || chr == '\r' || chr == '\n';
    return white_space ? true : false;
}

bool is_digit(char chr)
{
    const std::unordered_set<char> NUMBERS = {
        u8'0', u8'1', u8'2', u8'3', u8'4',
        u8'5', u8'6', u8'7', u8'8', u8'9'
    };
    return find_in_set(chr, NUMBERS);
}

bool is_letter(char chr)
{
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
    return find_in_set(chr, LETTERS);
}


bool is_alpha_numeric(char chr)
{
    const std::unordered_set<char> ALPHA_NUM = {
        'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p',
        'q', 'r', 's', 't',
        'u', 'v', 'w', 'x',
        'y', 'z',

        'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X',
        'Y', 'Z',

        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9'
    };

    return find_in_set(chr, ALPHA_NUM);
}


bool is_line(char chr)
{
    const std::unordered_set<char> LINES = {
        u8'-', u8'_'
    };
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

bool ends_with (const std::string &string, const std::string end)
{
    if (string.length() >= end.length()) {
        return ( 0 == string.compare(string.length() - end.length(), end.length(), end) );
    } else {
        return false;
    }
}



bool char_equal_to_any_of(const char chr, std::unordered_set<char> set)
{
    return set.count(chr);
}

bool string_equal_to_any_of(const std::string str, std::unordered_set<std::string> set)
{
    return set.count(str);
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


int32_t substring_size(SubString substring)
{
    std::string::iterator it = substring.begin;
    int32_t size = 1;
    while(it != substring.end)
    {
        size++;
        it++;
    }
    return size;
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



int parse_number(SubString substring)
{
    int parsed_number = std::stoi(substring_to_string(substring));
    return parsed_number;
}

int parse_number(std::string str)
{
    int parsed_number = std::stoi(str);
    return parsed_number;
}




SubString empty_substring()
{
    std::string s = std::string();
    return {s.begin(), s.end()};
}



SubString trim_substring(SubString substring)
{
    std::string::iterator current_char = substring.begin;
    std::string::iterator begin = substring.begin;
    std::string::iterator end = substring.end;

    if (begin == end)
    {
        return substring;
    }

    while (is_white_space(*current_char))
    {
        current_char++;
    }
    begin = current_char;

    current_char = end;
    while (is_white_space(*current_char))
    {
        current_char--;
    }
    end = current_char;

    substring.begin = begin;
    substring.end = end;

    return substring;
}



std::string substring_to_string(SubString substring)
{
    std::string buffer = std::string();
    if (substring.begin == substring.end)
    {
        buffer = std::string(1, *substring.end);
        return buffer;
    }

    buffer = std::string(substring.begin, substring.end + 1);
    return buffer;
}

char substring_to_char(SubString substring)
{
    return *substring.begin;
}


void print_substring(SubString substring)
{
    std::cout << substring_to_string(substring) << std::endl;
}


bool substring_is_space(SubString sub)
{
    if (*sub.begin == ' ' | *sub.begin == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
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


std::string integer_to_string(int64_t i)
{
    std::stringstream stream;
    std::string si;
    stream << i;
    stream >> si;
    return si;
}



} // end of namespace bibparser