#include <string>
#include <iostream>

#include "global_variables.hpp"
#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"


Token::Token (Tag input_tag, std::string input_key, std::string input_value)
{
    tag = input_tag;
    attributes.emplace(input_key, input_value);
}


Token build_token(Tag type_of_token, SubString lexeme)
{
    std::string key;
    switch (type_of_token)
    {
    case BIB_TYPE:
        key = "type";
        break;
    case BIB_IDENTIFIER:
        key = "identifier";
        break;
    default:
        break;
    }

    std::string value = std::string(lexeme.begin, lexeme.end);
    Token token(type_of_token, key, value);
    return token;
}

Token build_attribute_token(EntryAttribute attr)
{
    std::string key = std::string(attr.key.begin, attr.key.end);
    std::string value = std::string(attr.value.begin, attr.value.end);
    Token token(BIB_ATTRIBUTE, key, value);
    return token;
}


void tokenizer(std::list<Token> &tokens)
{
    std::vector<SubString> bib_entries = collect_bib_entries(bibparser::bib_file);
    std::for_each(bib_entries.begin(), bib_entries.end(), &trim_substring);

    for (SubString entry : bib_entries)
    {
        parse_entry(entry, tokens);
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



void parse_entry(SubString entry, std::list<Token> &tokens)
{
    SubString entry_type = get_entry_type(entry);
    tokens.emplace_back(build_token(BIB_TYPE, entry_type));

    std::string::iterator end = entry.end;
    SubString substring_body = {entry_type.end, end};
    EntryBody entry_body = parse_entry_body(substring_body);

    tokens.emplace_back(build_token(BIB_IDENTIFIER, entry_body.identifier));

    std::vector<EntryAttribute> entry_attributes = parse_entry_attributes(entry_body.attributes);
    for (EntryAttribute attr: entry_attributes)
    {
        tokens.emplace_back(build_attribute_token(attr));
    }
}

SubString get_entry_type(SubString entry)
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



EntryBody parse_entry_body(SubString body)
{
    EntryBody entry_body;
    std::vector<SubString> substrings = split_substring(body, ',');
    
    if (substrings.size() == 1)
    {
        entry_body.identifier = substrings[0];
        std::vector<SubString> empty_vector;
        entry_body.attributes = empty_vector;
        return entry_body;
    }

    entry_body.identifier = substrings[0];
    substrings.erase(substrings.begin());
    entry_body.attributes = substrings;

    return entry_body;
}

std::vector<EntryAttribute> parse_entry_attributes(std::vector<SubString> &attrs)
{
    std::vector<EntryAttribute> attributes;
    int n_attrs = attrs.size();
    attributes.reserve(n_attrs);

    const char delimiter = '=';
    std::vector<SubString> substrings;
    EntryAttribute attribute;

    for (SubString attr: attrs)
    {
        substrings = split_substring(attr, delimiter);
        std::for_each(substrings.begin(), substrings.end(), &trim_substring);
        attribute.key = substrings[0];
        attribute.value = substrings[1];
        attributes.emplace_back(attribute);
    }

    return attributes;    
}





void print_entry_body (EntryBody body)
{
    std::cout << "[Entry Identifier]: ";
    print_substring(body.identifier);

    std::cout
        << std::endl
        << "[Entry Attributes]: "
        << std::endl;

    for (SubString attr: body.attributes)
    {
        print_substring(attr);
    }
}

void print_entry_attributes (std::vector<EntryAttribute> attrs)
{
    for (EntryAttribute attr: attrs)
    {
        std::cout << "[Attribute key]: ";
        std::cout << std::string(attr.key.begin, attr.key.end) << "   |   ";
        std::cout << "[Attribute value]: ";
        std::cout << std::string(attr.value.begin, attr.value.end) << std::endl;
    } 
}