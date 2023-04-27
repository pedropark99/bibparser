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
    bool standard_bibtex_type;
    
public:
    BibType(SubString input_type);
    BibType() = default;
    std::string as_string();
    bool is_standard_bibtex_type();
    void print_bib_type();
};

const std::unordered_set<std::string> standard_bibtex_types = {
    "misc"
    , "article"
    , "manual"
    , "book"
    , "booklet"
    , "conference"
    , "inbook"
    , "incollection"
    , "inproceedings"
    , "mastersthesis"
    , "phdthesis"
    , "proceedings"
    , "techreport"
    , "unpublished"
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

struct KeyValuePair {
    Token key_token;
    Token value_token;
};





struct BibEntry {
	BibIdentifier identifier;
	BibType type;
	std::list<BibAttribute> attributes;
};



BibType parse_bibtype(Token input_token);
BibIdentifier parse_identifier(Token input_token);
BibAttribute parse_bib_attribute(KeyValuePair key_value_pair);
void print_bib_entry(BibEntry &bib_entry);










enum ParserState {
    PARSING = 421,
    PARSE_ERROR = 422
};


struct ParserBuffer {
    ParserState parser_state;
    int current_line_in_source;

    std::list<Token>::iterator current_token;
    std::list<Token>::iterator look_ahead;
    std::list<Token>::iterator look_behind;
    std::list<Token>::iterator begin;
    std::list<Token>::iterator end;
};


class Parser
{
private:
    Tokenizer tokenizer;
    ParserBuffer parser_buffer;
    std::list<BibEntry> bib_entries;

public:
    Parser(std::string path_to_bib_file);
    void parse_tokens();
    void parse_entry_tokens(std::list<Token> entry_tokens);
    void parse_file();
    void print_bib_entries();
};

