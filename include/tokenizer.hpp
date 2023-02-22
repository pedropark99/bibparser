#pragma once
#include <string>
#include <list>


bool is_white_space(char chr);
bool is_digit(char chr);
bool is_letter(char chr);

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

    Token (Tag tag, std::string value)
    {
        tag = tag;
        value = value;
    }
};

std::list<Token> tokenizer(void);
Token buid_token(Tag type_of_token,
                std::string::iterator beginning_of_lexeme,
                std::string::iterator forward);