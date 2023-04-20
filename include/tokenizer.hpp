#pragma once
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <vector>



enum TokenType
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

    Token (TokenType input_type, SubString input_value);
    std::string as_string();
    SubString as_substring();
    void print_token();
};


void tokenizer(TokenizerBuffer &parser_buffer, std::list<Token> &tokens);


void tokenize_entry(TokenizerBuffer &buf, std::list<Token> &tokens);
void tokenize_entry_type(TokenizerBuffer &buf, std::list<Token> &tokens);
void tokenize_entry_body(TokenizerBuffer &buf, std::list<Token> &tokens);
void tokenize_bib_identifier(TokenizerBuffer &buf, std::list<Token> &tokens);
void tokenize_entry_attribute(TokenizerBuffer &buf, std::list<Token> &tokens);
void tokenize_comma(TokenizerBuffer &buf, std::list<Token> &tokens);
void tokenize_open_bracket(TokenizerBuffer &buf, std::list<Token> &tokens);
void tokenize_close_bracket(TokenizerBuffer &buf, std::list<Token> &tokens);
void tokenize_equal_sign(TokenizerBuffer &buf, std::list<Token> &tokens);
void tokenize_quotation_mark(TokenizerBuffer &buf, std::list<Token> &tokens);



void add_identifiers(std::list<Token> &tokens, std::unordered_map<std::string, TokenType> &symbol_table);