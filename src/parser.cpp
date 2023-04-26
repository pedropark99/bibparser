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



const std::unordered_set<std::string> allowed_bib_types = {
    "misc"
    , "article"
    , "manual"
    , "book"
};


bool is_valid_bib_type(SubString type)
{
    std::string s_type = substring_to_string(type);
    if (std::find(
            allowed_bib_types.begin(),
            allowed_bib_types.end(),
            s_type
        ) != allowed_bib_types.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

BibType::BibType(SubString input_type)
{
    type = input_type;
}

std::string BibType::as_string()
{
    return substring_to_string(type);
}

BibType parse_bibtype(Token input_token)
{
    SubString type = input_token.value;
    if (is_valid_bib_type(type))
    {
        return BibType(type);
    }
    else
    {
        throw std::runtime_error("Bib Type is invalid");
    }
}


BibIdentifier::BibIdentifier(SubString input_identifier)
{
    identifier = input_identifier;
}

std::string BibIdentifier::as_string()
{
    return substring_to_string(identifier);
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


void check_key_value_stack(std::stack<Token> &key_value_stack, Token input_token)
{
    if (key_value_stack.empty())
    {
        return;
    }

    TokenType token_type = input_token.type;

    if (token_type == BIB_ATTRIBUTE_KEY & key_value_stack.top().type == BIB_ATTRIBUTE_KEY)
    {
        throw std::runtime_error("There are two BIB_ATTRIBUTE_KEY tokens in a row on the key-value pair stack!");
    }
    if (token_type == BIB_ATTRIBUTE_VALUE & key_value_stack.top().type == BIB_ATTRIBUTE_VALUE)
    {
        throw std::runtime_error("There are two BIB_ATTRIBUTE_VALUE tokens in a row on the key-value pair stack!");
    }
}

void clear_key_value_stack(std::stack<Token> &key_value_stack)
{
    while(!key_value_stack.empty())
        key_value_stack.pop();
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

BibAttribute parse_bib_attribute(std::stack<Token> &key_value_stack)
{
    Token attribute_value = key_value_stack.top();
    key_value_stack.pop();
    Token attribute_key = key_value_stack.top();
    key_value_stack.pop();
    return BibAttribute(attribute_key.value, attribute_value.value); 
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


/*
Parser steps:

1. get next token;
2. start to parse this token;
5. parse the token into its best format;
3. check for grammar errors;
4. check for sytax errors;
6. register the property into the symbol table.
*/


Parser::Parser(std::string path_to_bib_file)
{
    tokenizer = Tokenizer(path_to_bib_file);
}


void Parser::parse_file()
{
    tokenizer.collect_tokens();
    parse_tokens();
    print_bib_entries();
}



void Parser::parse_tokens()
{
    Token current_token;
    std::list<Token> entry_tokens;
    std::list<Token>::iterator token_it = tokenizer.tokens.begin();

    if ((*token_it).type == BIB_ENTRY)
    {
        entry_tokens.emplace_back(*token_it);
        token_it++;
    }

    while (token_it != tokenizer.tokens.end())
    {
        current_token = *token_it;
        if (current_token.type != BIB_ENTRY)
        {
            entry_tokens.emplace_back(current_token);
        }
        else
        {
            parse_entry_tokens(entry_tokens);
            entry_tokens.clear();
            entry_tokens.emplace_back(current_token);
        }

        token_it++;
    }
}


void Parser::parse_entry_tokens(std::list<Token> entry_tokens)
{
    Token current_token;
    std::list<Token>::iterator token_it = entry_tokens.begin();
    BibEntry bib_entry;
    std::stack<Token> key_value_pair;

    while (token_it != entry_tokens.end())
    {
        current_token = *token_it;
        

        "teste";
        switch (current_token.type)
        {
        case BIB_TYPE:
            bib_entry.type = parse_bibtype(current_token);
            break;
        case BIB_IDENTIFIER:
            bib_entry.identifier = parse_identifier(current_token);
            break;
        case BIB_ATTRIBUTE_KEY:
            check_key_value_stack(key_value_pair, current_token);
            clear_key_value_stack(key_value_pair);
            key_value_pair.emplace(current_token);
            break;
        case BIB_ATTRIBUTE_VALUE:
            check_key_value_stack(key_value_pair, current_token);
            key_value_pair.emplace(current_token);
            bib_entry.attributes.emplace_back(
                parse_bib_attribute(key_value_pair)
            );
            clear_key_value_stack(key_value_pair);
            break;

        default:
            // BIB_ENTRY, NEW_LINE, COMMA, EQUAL_SIGN, etc.
            break;
        }
        
        token_it++;
    }

    bib_entries.emplace_back(bib_entry);
}



void BibIdentifier::print_bib_identifier()
{
    std::cout << substring_to_string(identifier);
}


void Parser::print_bib_entries()
{
    for (BibEntry bib_entry: bib_entries)
    {
        print_bib_entry(bib_entry);
    }
}