#pragma once
#include <string>
#include <list>
#include <unordered_set>
#include <stack>
#include <unordered_map>

#include "tokenizer.hpp"




class BibIdentifier {
private:
    SubString identifier;
public:
    BibIdentifier(SubString input_identifier);
    BibIdentifier() = default;
    void print_bib_identifier();
    std::string as_string();
};




class BibType {
private:
    SubString type;
public:
    BibType(SubString input_type);
    BibType() = default;
    void print_bib_type();
    std::string as_string();
};

const std::unordered_set<std::string> allowed_bib_types = {
    "misc"
    , "article"
    , "manual"
    , "book"
};




class BibAttribute {
private:
    SubString key;
    SubString value;
public:
    BibAttribute(SubString input_key, SubString input_value);
    BibAttribute() = default;
    void print_bib_attribute();
    std::string as_string();
};






struct BibEntry {
	BibIdentifier identifier;
	BibType type;
	std::list<BibAttribute> attributes;
};



BibType parse_bibtype(Token input_token);
BibIdentifier parse_identifier(Token input_token);
BibAttribute parse_bib_attribute(std::stack<Token> &key_value_stack);
bool is_valid_bib_type(SubString type);
void check_key_value_stack(std::stack<Token> &key_value_stack, Token input_token);
void clear_key_value_stack(std::stack<Token> &key_value_stack);
void print_bib_entry(BibEntry &bib_entry);










enum ParserState {
    PARSING = 421,
    PARSE_ERROR = 422
};


class Parser
{
private:
    Tokenizer tokenizer;
    ParserState parser_state;
    std::list<BibEntry> bib_entries;

public:
    Parser(std::string path_to_bib_file);
    void parse_tokens();
    void parse_entry_tokens(std::list<Token> entry_tokens);
    void parse_file();
    void print_bib_entries();
};

