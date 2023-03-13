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
    BIB_ATTRIBUTE_VALUE = 5235,
    BIB_ATTRIBUTE_KEY = 5236,
    COMMA = 5237,
    OPEN_BRACKET = 5238,
    CLOSE_BRACKET = 5239,
    EQUAL_SIGN = 5340,
    QUOTATION_MARK = 5341
};

std::string tag_to_string(Tag tag);

struct SubString {
    std::string::iterator begin;
    std::string::iterator end;
};

struct ParserBuffer {
    std::string::iterator begin;
    std::string::iterator end;
    std::string::iterator anchor;
    std::string::iterator current_char;
};


class Token {
public:
    Tag tag;
    SubString value;

    Token (Tag input_tag, SubString input_value);
    std::string as_string();
    SubString as_substring();
    void print_token();
};


void tokenizer(ParserBuffer &parser_buffer, std::list<Token> &tokens);


void tokenize_entry(ParserBuffer &buf, std::list<Token> &tokens);
void tokenize_entry_type(ParserBuffer &buf, std::list<Token> &tokens);
void tokenize_entry_body(ParserBuffer &buf, std::list<Token> &tokens);
void tokenize_bib_identifier(ParserBuffer &buf, std::list<Token> &tokens);
void tokenize_entry_attribute(ParserBuffer &buf, std::list<Token> &tokens);
void tokenize_comma(ParserBuffer &buf, std::list<Token> &tokens);
void tokenize_open_bracket(ParserBuffer &buf, std::list<Token> &tokens);
void tokenize_close_bracket(ParserBuffer &buf, std::list<Token> &tokens);
void tokenize_equal_sign(ParserBuffer &buf, std::list<Token> &tokens);
void tokenize_quotation_mark(ParserBuffer &buf, std::list<Token> &tokens);

