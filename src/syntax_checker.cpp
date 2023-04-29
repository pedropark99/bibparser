#include <list>
#include <unordered_map>
#include <iostream>

#include "syntax_check.hpp"
#include "tokenizer.hpp"

namespace bibparser {
namespace syntax {


struct SyntaxCheckerBuffer {
    std::list<Token>::iterator token_it;
    std::list<Token>::iterator begin;
    std::list<Token>::iterator end;
};



std::unordered_map<TokenType, TokenType> expects_next = {
    {BIB_ENTRY, BIB_TYPE}
};



void match_next_type(SyntaxCheckerBuffer buf, TokenType next_type)
{
    std::list<Token>::iterator look_ahead = std::list<Token>::iterator();
    if (std::next(buf.token_it) != buf.end)
    {
        look_ahead = std::next(buf.token_it);
    }

    if (look_ahead->type_ == next_type)
    {
        return;
    }
    else
    {
        //raise some errror!
    }
}


    
void syntax_checker(std::list<Token> &tokens)
{
    SyntaxCheckerBuffer buf = {
        tokens.begin(),
        tokens.begin(),
        tokens.end()
    };

    TokenType next_type = TokenType();
    for (buf.token_it; buf.token_it != buf.end; buf.token_it++)
    {
        next_type = expects_next[buf.token_it->type_];
        match_next_type(buf, next_type);
        std::cout << next_type << std::endl;
    }
}

} // end of namespace syntax
} // end of namespace bibparser