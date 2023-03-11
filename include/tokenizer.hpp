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
Token buid_token(Tag type_of_token,
                std::string::iterator begin_of_lexeme,
                std::string::iterator end_of_lexeme);





struct SubString {
    std::string::iterator begin;
    std::string::iterator end;
};
std::vector<SubString> collect_bib_entries(std::string &file);
void parse_entry(SubString entry);
SubString find_entry_type(SubString entry);


struct EntryBody {
    SubString identifier;
    std::vector<SubString> attributes;
};
EntryBody parse_entry_body(SubString attrs);
void parse_entry_attrs(std::vector<SubString> &attrs);
void key_value_pair(SubString kv);
