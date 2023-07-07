#pragma once
#include <string>
#include <list>
#include <unordered_set>
#include <stack>
#include <unordered_map>
#include <vector>

#include "tokenizer.hpp"


namespace bibparser {


class BibIdentifier {
private:
    SubString identifier_;
public:
    BibIdentifier(SubString input_identifier);
    BibIdentifier() = default;
    void print_bib_identifier();
    std::string as_string();
};




class BibType {
private:
    SubString type_;
    bool standard_bibtex_type_;
    
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
    SubString key_;
    SubString value_;
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





// struct BibEntry {
// 	BibIdentifier identifier;
// 	BibType type;
// 	std::list<BibAttribute> attributes;
// };

struct BibEntry {
	BibIdentifier identifier;
	BibType type;
	std::vector<BibAttribute> attributes;
    
    std::vector<Token> tokens;
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

    std::vector<Token>::iterator begin_of_tokens;
    std::vector<Token>::iterator end_of_tokens;
    std::vector<Token>::iterator current_token;
    std::vector<Token>::iterator look_ahead;
};


class Parser
{
private:
    Tokenizer tokenizer_;
    ParserBuffer parser_buffer_;
    std::list<BibEntry> ast;

public:
    Parser(std::string path_to_bib_file);
    void parse_tokens();
    void parse_entry_tokens(std::vector<Token> entry_tokens);
    void parse();
    void print_bib_entries();
    void syntax_check();
    void next_token();
};




} // end of namespace bibparser