#pragma once
#include <string>
#include <list>



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
    int64_t line_in_source_;

    Token(TokenType input_type, SubString input_value);
    Token() = default;

    std::string as_string();
    SubString as_substring();
    void print_token();
};


class Tokenizer {
private:
    std::string bib_file_;
    TokenizerBuffer buf_;

public:
    std::list<Token> tokens;
    Token current_token;
    
    Tokenizer(std::string path_to_bib_file);
    Tokenizer() = default;

    Token get_next_token();
    SubString collect_current_substring();
    void collect_tokens(bool raw_tokens = false);
    void print_tokens();
    void redefine_bib_text_tokens();
    
    std::list<Token>::iterator find_next_token_of_type (std::list<Token>::iterator current_position,
                                                        TokenType type);
};
