#include <string>
#include <list>
#include <unordered_map>
#include <stack>
#include <iterator>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <vector>


#include "parser.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"


namespace bibparser {


Parser::Parser(std::string path_to_bib_file)
{
    tokenizer_ = Tokenizer(path_to_bib_file);
    parser_buffer_ = {
        PARSING,
        std::vector<Token>::iterator(),   // begin_of_tokens
        std::vector<Token>::iterator(),   // end_of_tokens
        std::vector<Token>::iterator(),   // current_token
        std::vector<Token>::iterator()    // look_ahead
    };
}





void Parser::parse()
{
    // tokenizer_.collect_raw_tokens();
    // parse_tokens();
    // print_bib_entries();

    Token tk = Token();
    std::vector<Token> tokens_;
    for (int i = 0; i < 65; i++)
    {
        tk = tokenizer_.get_next_token();
        if (tk.type_ != EMPTY && tk.type_ != NEW_LINE) tokens_.emplace_back(tk);
    }

    parser_buffer_ = {
        PARSING,
        tokens_.begin(),
        tokens_.end(),
        tokens_.begin(),
        tokens_.begin()
    };

    if (parser_buffer_.current_token->type_ != BIB_ENTRY)
    {
        throw std::exception();
    }

    next_token();

    if (parser_buffer_.current_token->type_ != BIB_TEXT)
    {
        throw std::exception();
    }
    else
    {
        parser_buffer_.current_token->type_ = BIB_TYPE;
    }

    next_token();

    if (parser_buffer_.current_token->type_ != OPEN_BRACKET
       && parser_buffer_.current_token->type_ != QUOTATION_MARK)
    {
        throw std::exception();
    }

    next_token();

    if (parser_buffer_.current_token->type_ != BIB_TEXT)
    {
        throw std::exception();
    }
    else
    {
        parser_buffer_.current_token-> type_ = BIB_IDENTIFIER;
    }

    next_token();

    if (parser_buffer_.current_token->type_ != COMMA)
    {
        throw std::exception();
    }

    while (parser_buffer_.current_token != parser_buffer_.end_of_tokens)
    {
        
    }


    for (Token token: tokens_)
    {
        token.print_token();
    }
}


void Parser::next_token()
{
    parser_buffer_.current_token++;
    if (std::next(parser_buffer_.current_token) != parser_buffer_.end_of_tokens)
    {
        parser_buffer_.look_ahead = std::next(parser_buffer_.current_token);
    }
}


void Parser::parse_tokens()
{
    std::vector<Token> entry_tokens = std::vector<Token>();
    parser_buffer_ = {
        PARSING,
        tokenizer_.tokens_.begin(),   // begin_of_tokens
        tokenizer_.tokens_.end(),     // end_of_tokens
        tokenizer_.tokens_.begin(),   // current_token
        tokenizer_.tokens_.begin()    // look_ahead
    };

    if (std::next(parser_buffer_.current_token) != parser_buffer_.end_of_tokens)
    {
        parser_buffer_.look_ahead = std::next(parser_buffer_.current_token);
    }
    

    while (parser_buffer_.current_token != parser_buffer_.end_of_tokens)
    {
        if (parser_buffer_.look_ahead->type_ == BIB_ENTRY)
        {
            entry_tokens.emplace_back(*parser_buffer_.current_token);
            parse_entry_tokens(entry_tokens);
            entry_tokens.clear();
            next_token();
            continue;
        }

        entry_tokens.emplace_back(*parser_buffer_.current_token);
        next_token();
    }

    // Parse the remaining tokens in `entry_tokens` from the last iteration;
    // parse_entry_tokens(entry_tokens);
}


void Parser::parse_entry_tokens(std::vector<Token> entry_tokens)
{
    KeyValuePair key_value_pair = {Token(), Token()};
    BibEntry bib_entry = {
        BibIdentifier(empty_substring()),  // identifier
        BibType(empty_substring()),        // type
        std::list<BibAttribute>()          // attributes
    };

    
    for (Token token: entry_tokens)
    {
        token.print_token();
    }

    ast.emplace_back(bib_entry);
}


void Parser::print_bib_entries()
{
    for (BibEntry bib_entry: ast)
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


















BibType parse_bibtype(Token input_token)
{
    return BibType(input_token.value_);
}

BibType::BibType(SubString input_type)
{
    type_ = input_type;
    standard_bibtex_type_ = is_standard_bibtex_type();
}

bool BibType::is_standard_bibtex_type()
{
    bool is_standard_bibtex_type = std::find(
        standard_bibtex_types.begin(),
        standard_bibtex_types.end(),
        substring_to_string(type_)
    ) != standard_bibtex_types.end();

    return is_standard_bibtex_type;
}

std::string BibType::as_string()
{
    return substring_to_string(type_);
}

void BibType::print_bib_type()
{
    std::cout << "Type: " << as_string() << std::endl;
}


















BibIdentifier::BibIdentifier(SubString input_identifier)
{
    identifier_ = input_identifier;
}

std::string BibIdentifier::as_string()
{
    return substring_to_string(identifier_);
}

void BibIdentifier::print_bib_identifier()
{
    std::cout << substring_to_string(identifier_);
}

BibIdentifier parse_identifier(Token input_token)
{
    std::string identifier = substring_to_string(input_token.value_);
    if (identifier.find(' ') != identifier.npos)
    {
        throw std::runtime_error("Identifier contains invalid characters");
    }

    return BibIdentifier(input_token.value_);
}














BibAttribute::BibAttribute(SubString input_key, SubString input_value)
{
    key_ = input_key;
    value_ = input_value;
}

std::string BibAttribute::as_string()
{
    std::string s_key = substring_to_string(key_);
    std::string s_value = substring_to_string(value_);
    return s_key + "=" + s_value;
}

BibAttribute parse_bib_attribute(KeyValuePair key_value_pair)
{
    Token attribute_value = key_value_pair.value_token;
    Token attribute_key = key_value_pair.key_token;
    return BibAttribute(attribute_key.value_, attribute_value.value_); 
}


} // end of namespace bibparser