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


std::vector<SubStringAdress> collect_bib_entries(std::string& file)
{
    int n_of_entries = count_char('@');
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



    std::vector<SubStringAdress> bib_entries;
    bib_entries.reserve(n_of_entries);

    while (current_char != end)
    {
        if (*current_char == '@' & entries_allocated < n_of_entries - 1)
        {
            SubStringAdress entry_adress = {begin, current_char};
            bib_entries.emplace_back(entry_adress);
            entries_allocated++;
            current_char++;
            begin = current_char;
            continue;
        }

        // Get last bib entry in the file
        if ((current_char + 1) == end)
        {
            SubStringAdress entry_adress = {begin, current_char};
            bib_entries.emplace_back(entry_adress);
            entries_allocated++;
            current_char++;
            begin = current_char;
            break;
        }

        current_char++;
    }

    return bib_entries;
}

SubStringAdress find_entry_identifier(SubStringAdress attrs)
{
    std::string::iterator current_char = attrs.begin;
    std::string::iterator begin = attrs.begin;

    while (*current_char != ',')
    {
        current_char++;
    }

    return {begin, current_char};
}

SubStringAdress find_entry_type(SubStringAdress entry)
{
    std::string::iterator current_char = entry.begin;
    std::string::iterator begin = entry.begin;
    std::string::iterator end = entry.end;

    SubStringAdress entry_type;
    while (current_char != end)
    {
        if (*(current_char + 1) == '{')
        {
            entry_type = {begin, current_char + 1};
            break;
        }

        current_char++;
    }

    return entry_type;
}


void parse_entry(SubStringAdress entry)
{
    std::string::iterator current_char = entry.begin;
    std::string::iterator begin = entry.begin;
    std::string::iterator end = entry.end;

    std::string t = std::string(begin, end);
    t.resize(t.size() + 1);
    t[t.size() + 1] = '\0';
    std::cout << t << std::endl;

    while (*end != '}')
    {
        end--;
    }

    SubStringAdress entry_type = find_entry_type(entry);

    current_char = entry_type.end;
    begin = entry_type.end;

    //std::cout << std::string(begin, end) << std::endl;

    SubStringAdress entry_attrs = {current_char + 1, end - 1};
    SubStringAdress entry_identifier = find_entry_identifier(entry_attrs);

    current_char = entry_identifier.end;
    begin = entry_identifier.end;

    //std::cout << std::string(begin, end) << std::endl;

    entry_attrs = {current_char + 1, end - 1};

    //std::cout << std::endl << std::endl << std::endl << std::endl;

}



std::list<Token> tokenizer()
{
    std::list<Token> tokens;
    std::vector<SubStringAdress> bib_entries = collect_bib_entries(bibparser::bib_file);

    for (SubStringAdress entry : bib_entries)
    {
        parse_entry(entry);
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
