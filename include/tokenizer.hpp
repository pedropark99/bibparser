#pragma once
#include <string>
#include <list>
#include <unordered_set>
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
    std::string value;

    Token (Tag input_tag, std::string input_value);
};

std::list<Token> tokenizer();
Token build_token(Tag type_of_token, SubString lexeme);





struct SubString {
    std::string::iterator begin;
    std::string::iterator end;
};
std::vector<SubString> collect_bib_entries(std::string &file);
void parse_entry(SubString entry);
SubString get_entry_type(SubString entry);


struct EntryBody {
    SubString identifier;
    std::vector<SubString> attributes;
};
EntryBody parse_entry_body(SubString attrs);
void print_entry_body (EntryBody body);


struct EntryAttribute {
    SubString key;
    SubString value;
};
std::vector<EntryAttribute> parse_entry_attributes(std::vector<SubString> &attrs);
void print_entry_attributes (std::vector<EntryAttribute> attrs);