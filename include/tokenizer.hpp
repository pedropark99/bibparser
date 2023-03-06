#pragma once
#include <string>
#include <list>
#include <unordered_set>


bool is_white_space(char chr);
bool is_digit(char chr);
bool is_letter(char chr);
bool find_in_set(char chr, const std::unordered_set<char>& set);

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

    Token (Tag input_tag, std::string input_value)
    {
        tag = input_tag;
        value = input_value;
    }
};

struct SubStringAdress {
    std::string::iterator begin;
    std::string::iterator end;
};




std::vector<SubStringAdress> collect_bib_entries(std::string file);


std::list<Token> tokenizer(std::string file);
Token buid_token(Tag type_of_token,
                std::string::iterator begin_of_lexeme,
                std::string::iterator end_of_lexeme);


void get_bib_identifier(std::string::iterator& begin_of_lexeme,
                        std::string::iterator& forward);