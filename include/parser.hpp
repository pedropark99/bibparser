#pragma once
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>

#include "tokenizer.hpp"


enum ParserState {
    PARSING = 421,
    PARSE_ERROR = 422
};

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
    std::string as_string();
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

void print_bib_entry();


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




