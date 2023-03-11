#pragma once
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <vector>



enum Tag
{
    BIB_IDENTIFIER = 5234,
    BIB_TYPE = 5233,
    BIB_ATTRIBUTE = 5235
};

class Token {
public:
    Tag tag;
    std::unordered_map<std::string, std::string> attributes;

    Token (Tag input_tag, std::string input_key, std::string input_value);
};

struct SubString {
    std::string::iterator begin;
    std::string::iterator end;
};

struct EntryBody {
    SubString identifier;
    std::vector<SubString> attributes;
};

struct EntryAttribute {
    SubString key;
    SubString value;
};



std::list<Token> tokenizer();
Token build_token(Tag type_of_token, SubString lexeme);
Token build_attribute_token(EntryAttribute attr);


std::vector<SubString> collect_bib_entries(std::string &file);
void parse_entry(SubString entry, std::list<Token> &tokens);
SubString get_entry_type(SubString entry);


EntryBody parse_entry_body(SubString attrs);
void print_entry_body (EntryBody body);


std::vector<EntryAttribute> parse_entry_attributes(std::vector<SubString> &attrs);
void print_entry_attributes (std::vector<EntryAttribute> attrs);