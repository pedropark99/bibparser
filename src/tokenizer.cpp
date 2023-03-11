#include <string>
#include <iostream>


#include "global_variables.hpp"
#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"


Token::Token (Tag input_tag, std::string input_value)
{
    tag = input_tag;
    value = input_value;
}

Token buid_token(Tag type_of_token,
                std::string::iterator begin_of_lexeme,
                std::string::iterator end_of_lexeme)
{
    std::string lexeme = std::string(begin_of_lexeme, end_of_lexeme);
    Token token(type_of_token, lexeme);
    return token;
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



void parse_entry(SubString entry)
{
    std::string::iterator end = entry.end;

    SubString entry_type = find_entry_type(entry);
    SubString entry_attrs = {entry_type.end, end};
    SubString entry_identifier = find_entry_identifier(entry_attrs);
    print_substring(entry_attrs);


    //std::cout << std::string(entry_identifier.begin, entry_identifier.end) << std::endl;

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

