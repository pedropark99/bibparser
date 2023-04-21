#pragma once
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <vector>



enum TokenType
{
    END_OF_FILE = 5226,
    NEW_LINE = 5227,
    BIB_TEXT = 5228,
    EMPTY = 5229,
    BIB_ENTRY = 5230,
    BIB_BODY = 5231,
    BIB_IDENTIFIER = 5232,
    BIB_TYPE = 5233,
    BIB_ATTRIBUTE_VALUE = 5234,
    BIB_ATTRIBUTE_KEY = 5235,
    BIB_ATTRIBUTE = 5236,
    COMMA = 5237,
    OPEN_BRACKET = 5238,
    CLOSE_BRACKET = 5239,
    EQUAL_SIGN = 5340,
    QUOTATION_MARK = 5341
};

std::string token_type_to_string(TokenType type);




struct SubString {
    std::string::iterator begin;
    std::string::iterator end;
};

struct TokenizerBuffer {
    std::string::iterator begin;
    std::string::iterator end;
    std::string::iterator lexeme_begin;
    std::string::iterator current_char;
};






class Token {
public:
    TokenType type;
    SubString value;

    Token(TokenType input_type, SubString input_value);
    Token() = default;

    std::string as_string();
    SubString as_substring();
    void print_token();
};


class Tokenizer {
private:
    std::string bib_file;
    TokenizerBuffer buf;
public:
    Tokenizer(std::string path_to_bib_file);
    Tokenizer() = default;

    Token get_next_token();
    SubString collect_current_substring(bool include_look_ahead);
};


Token build_token(SubString token_value);
TokenType find_token_type(SubString token_value);