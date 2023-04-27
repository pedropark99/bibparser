#include <string>
#include <list>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <fstream>
#include <iostream>


#include "parser.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"



Parser::Parser(std::string path_to_bib_file)
{
    tokenizer = Tokenizer(path_to_bib_file);
    parser_buffer = {
        PARSING,
        1,
        std::list<Token>::iterator(),
        std::list<Token>::iterator(),
        std::list<Token>::iterator(),
        std::list<Token>::iterator(),
        std::list<Token>::iterator()
    };
}


void Parser::parse_file()
{
    tokenizer.collect_tokens();
    parse_tokens();
    print_bib_entries();
}


void Parser::parse_tokens()
{
    Token current_token = Token();
    Token next_token = Token();
    std::list<Token> entry_tokens = std::list<Token>();
    std::list<Token>::iterator token_it = tokenizer.tokens.begin();

    while (token_it != tokenizer.tokens.end())
    {
        current_token = *token_it;
        if (std::next(token_it) != tokenizer.tokens.end())
        {
            next_token = *std::next(token_it);
        }
        if (next_token.type == BIB_ENTRY)
        {
            entry_tokens.emplace_back(current_token);
            parse_entry_tokens(entry_tokens);
            entry_tokens.clear();
            token_it++;
            continue;
        }

        entry_tokens.emplace_back(current_token);
        token_it++;
    }

    // Parse the remaining tokens in `entry_tokens`;
    parse_entry_tokens(entry_tokens);
}


void Parser::parse_entry_tokens(std::list<Token> &entry_tokens)
{
    BibEntry bib_entry = {
        BibIdentifier(),
        BibType(),
        std::list<BibAttribute>()
    };
    KeyValuePair key_value_pair = {Token(), Token()};
    Token current_token = Token();
    std::list<Token>::iterator token_it = entry_tokens.begin();

    while (token_it != entry_tokens.end())
    {
        current_token = *token_it;
        
        switch (current_token.type)
        {
        case BIB_TYPE:
            bib_entry.type = parse_bibtype(current_token);
            break;
        case BIB_IDENTIFIER:
            bib_entry.identifier = parse_identifier(current_token);
            break;
        case BIB_ATTRIBUTE_KEY:
            key_value_pair.key_token = current_token;
            break;
        case BIB_ATTRIBUTE_VALUE:
            key_value_pair.value_token = current_token;
            bib_entry.attributes.emplace_back(
                parse_bib_attribute(key_value_pair)
            );
            break;

        default:
            // BIB_ENTRY, NEW_LINE, COMMA, EQUAL_SIGN, etc.
            break;
        }
        
        token_it++;
    }

    bib_entries.emplace_back(bib_entry);
}


void Parser::print_bib_entries()
{
    for (BibEntry bib_entry: bib_entries)
    {
        print_bib_entry(bib_entry);
    }
}

void print_bib_entry(BibEntry &bib_entry)
{
    std::string attributes_list = "* Attributes:\n";
    for (BibAttribute bib_attribute: bib_entry.attributes)
    {
        attributes_list.append("  - " + bib_attribute.as_string() + "\n");
    }

    std::cout
        << "[BIB ENTRY]" << std::endl
        << "* Identifier: " << bib_entry.identifier.as_string() << std::endl
        << "* Type: " << bib_entry.type.as_string() << std::endl
        << attributes_list << std::endl;
}


















std::string BibType::as_string()
{
    return substring_to_string(type);
}

BibType parse_bibtype(Token input_token)
{
    return BibType(input_token.value);
}

bool BibType::is_standard_bibtex_type()
{
    bool is_standard_bibtex_type = std::find(
        standard_bibtex_types.begin(),
        standard_bibtex_types.end(),
        substring_to_string(type)
    ) != standard_bibtex_types.end();

    return is_standard_bibtex_type;
}

BibType::BibType(SubString input_type)
{
    type = input_type;
    standard_bibtex_type = is_standard_bibtex_type();
}














BibIdentifier::BibIdentifier(SubString input_identifier)
{
    identifier = input_identifier;
}

std::string BibIdentifier::as_string()
{
    return substring_to_string(identifier);
}

void BibIdentifier::print_bib_identifier()
{
    std::cout << substring_to_string(identifier);
}

BibIdentifier parse_identifier(Token input_token)
{
    std::string identifier = substring_to_string(input_token.value);
    if (identifier.find(' ') != identifier.npos)
    {
        throw std::runtime_error("Identifier contains invalid characters");
    }

    return BibIdentifier(input_token.value);
}














BibAttribute::BibAttribute(SubString input_key, SubString input_value)
{
    key = input_key;
    value = input_value;
}

std::string BibAttribute::as_string()
{
    std::string s_key = substring_to_string(key);
    std::string s_value = substring_to_string(value);
    return s_key + "=" + s_value;
}

BibAttribute parse_bib_attribute(KeyValuePair key_value_pair)
{
    Token attribute_value = key_value_pair.value_token;
    Token attribute_key = key_value_pair.key_token;
    return BibAttribute(attribute_key.value, attribute_value.value); 
}

