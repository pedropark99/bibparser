#include <list>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <vector>

#include "syntax_check.hpp"
#include "tokenizer.hpp"

namespace bibparser {



std::unordered_map<TokenType, TokenType> expects_next = {
    {BIB_ENTRY, BIB_TYPE}
};

struct SyntaxCheckerBuffer {
    std::list<Token>::iterator begin_of_tokens;
    std::list<Token>::iterator end_of_tokens;
    std::list<Token>::iterator current_token;
    std::list<Token>::iterator look_ahead;
};




void syntax_check()
{
    std::vector<Token> tokens;
    for (int i = 0; i < 65; i++)
    {
        Token ct = tokenizer_.get_next_token();
        if (ct.type_ != EMPTY)
        {
            tokens.emplace_back(tokenizer_.get_next_token());
        }
    }

    parser_buffer_ = {
        PARSING,
        1,
        tokens.begin(),
        tokens.end(),
        tokens.begin(),
        tokens.begin(),
        tokens.begin()
    };


    if (parser_buffer_.current_token->type_ == BIB_ENTRY)
    {
        std::cout << "BIB_ENTRY!" << std::endl;
        goto expect_bib_type_next;
    }
    else
    {
        // report parse error
    }


expect_bib_type_next:
    goto_next_token();
    if (parser_buffer_.current_token->type_ == BIB_TYPE)
    {
        std::cout << "BIB_TYPE!" << std::endl;
        goto expect_open_curly_braces_next;
    }
    else
    {
        // report parse error
    }


expect_open_curly_braces_next:
    goto_next_token();
    if (parser_buffer_.current_token->type_ == OPEN_BRACKET)
    {
        std::cout << "OPEN_BRACKET!" << std::endl;
        goto expect_open_curly_braces_next;
    }

}








void match_next_type(SyntaxCheckerBuffer buf, TokenType next_type)
{
    std::list<Token>::iterator look_ahead = std::list<Token>::iterator();
    if (std::next(buf.current_token) != buf.end_of_tokens)
    {
        look_ahead = std::next(buf.current_token);
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




} // end of namespace bibparser