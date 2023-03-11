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


std::vector<SubString> collect_bib_entries(std::string &file)
{
    int n_of_entries = count_char(file, '@');
    std::vector<SubString> bib_entries;
    bib_entries.reserve(n_of_entries);
    
    std::string::iterator begin = file.begin();
    std::string::iterator end = file.end();
    std::string::iterator current_char = begin;
    int entry_number = 0;

    while (current_char != end)
    {
        if (*current_char == '@' & entry_number == 0)
        {
            current_char++;
            begin = current_char;
            entry_number++;
            continue;
        }

        if (*current_char == '@' & entry_number < n_of_entries)
        {
            SubString entry_adress = {begin, current_char};
            bib_entries.emplace_back(entry_adress);
            entry_number++;
            current_char++;
            begin = current_char;
            continue;
        }

        // Get last bib entry in the file
        if ((current_char + 1) == end)
        {
            SubString entry_adress = {begin, current_char};
            bib_entries.emplace_back(entry_adress);
            entry_number++;
            current_char++;
            begin = current_char;
            break;
        }

        current_char++;
    }

    return bib_entries;
}

void trim_entry(SubString &entry)
{
    std::string::iterator begin = entry.begin;
    std::string::iterator end = entry.end;
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

    entry.begin = begin;
    entry.end = end;
}


SubString find_entry_identifier(SubString attrs)
{
    std::string::iterator current_char = attrs.begin;
    std::string::iterator begin = attrs.begin;

    if (*current_char == '{')
    {
        current_char++;
        begin = current_char;
    }

    while (*current_char != ',' | current_char == attrs.end)
    {
        current_char++;
    }

    return {begin, current_char};
}

SubString find_entry_type(SubString entry)
{
    std::string::iterator current_char = entry.begin;
    std::string::iterator begin = entry.begin;
    std::string::iterator end = entry.end;

    while (current_char != end)
    {
        if (*(current_char + 1) == '{')
        {
            break;
        }

        current_char++;
    }

    return {begin, current_char + 1};
}


void print_substring(SubString substring)
{
    std::string s = std::string(substring.begin, substring.end);
    std::cout << s << std::endl;
}


void parse_entry(SubString entry)
{
    std::string::iterator end = entry.end;

    SubString entry_type = find_entry_type(entry);
    SubString entry_attrs = {entry_type.end, end};
    SubString entry_identifier = find_entry_identifier(entry_attrs);
    print_substring(entry_attrs);


    //std::cout << std::string(entry_identifier.begin, entry_identifier.end) << std::endl;

}



std::list<Token> tokenizer()
{
    std::list<Token> tokens;
    std::vector<SubString> bib_entries = collect_bib_entries(bibparser::bib_file);
    std::for_each(bib_entries.begin(), bib_entries.end(), &trim_entry);

    for (SubString entry : bib_entries)
    {
        parse_entry(entry);
    }

    return tokens;
}





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

