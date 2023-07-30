#pragma once
#include <filesystem>
#include <string>
#include <list>
#include <vector>


namespace bibparser {


struct SubString {
    std::string::iterator begin;
    std::string::iterator end;
};

struct TokenizerBuffer {
    std::string::iterator begin_of_file;
    std::string::iterator end_of_file;
    std::string::iterator lexeme_begin;
    std::string::iterator current_char;
    std::string::iterator look_ahead;

    size_t line_in_source;

};







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
    QUOTATION_MARK = 5341,
    UNKNOWN = 5342
};

std::string token_type_to_string(TokenType type);
TokenType find_token_type(SubString token_value);






class Token {
public:
    TokenType type_;
    SubString value_;
    size_t line_in_source_;
    size_t column_in_source_;

    Token(TokenType input_type, SubString input_value);
    Token() = default;

    std::string as_string();
    SubString as_substring();
    void print_token();
};


class Tokenizer {
public:
    std::string bib_file_;
    TokenizerBuffer tokenizer_buffer_;
    Token current_token_;
    

public:
    Tokenizer(std::string bib_string);

    Token get_next_token();
    void print_tokens();
    std::vector<Token> collect_raw_tokens();
    std::vector<Token> collect_next_entry_tokens();

private:
    void next_char();
    Token collect_token(std::string::iterator begin, std::string::iterator end);
};


bool any_token_of_type (std::vector<Token> &tokens, const TokenType type);
bool all_tokens_of_type (std::vector<Token> &tokens, const TokenType type);



} // end of namespace bibparser
