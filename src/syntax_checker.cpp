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
        parser_buffer_ = {
        PARSING,
        tokens_.begin(),
        tokens_.end(),
        tokens_.begin(),
        tokens_.begin()
    };

    if (parser_buffer_.current_token->type_ != BIB_ENTRY)
    {
        report_token_type_error(*parser_buffer_.current_token, BIB_ENTRY);
    }

    next_token();

    if (parser_buffer_.current_token->type_ != BIB_TEXT)
    {
        report_token_type_error(*parser_buffer_.current_token, BIB_TEXT);
    }
    else
    {
        parser_buffer_.current_token->type_ = BIB_TYPE;
    }

    next_token();

    if (parser_buffer_.current_token->type_ != OPEN_BRACKET
       && parser_buffer_.current_token->type_ != QUOTATION_MARK)
    {
        report_token_type_error(*parser_buffer_.current_token, OPEN_BRACKET);
    }

    next_token();

    if (parser_buffer_.current_token->type_ != BIB_TEXT)
    {
        report_token_type_error(*parser_buffer_.current_token, BIB_TEXT);
    }
    else
    {
        parser_buffer_.current_token-> type_ = BIB_IDENTIFIER;
    }

    next_token();

    if (parser_buffer_.current_token->type_ != COMMA)
    {
        report_token_type_error(*parser_buffer_.current_token, COMMA);
    }

    next_token();

    while (parser_buffer_.current_token != parser_buffer_.end_of_tokens)
    {
        if (parser_buffer_.current_token->type_ != BIB_TEXT)
        {
            report_token_type_error(*parser_buffer_.current_token, BIB_TEXT);
        }
        else
        {
            parser_buffer_.current_token->type_ = BIB_ATTRIBUTE_KEY;
        }

        next_token();

        if (parser_buffer_.current_token->type_ != EQUAL_SIGN)
        {
            report_token_type_error(*parser_buffer_.current_token, EQUAL_SIGN);
        }

        next_token();

        if (parser_buffer_.current_token->type_ != OPEN_BRACKET
           && parser_buffer_.current_token->type_ != QUOTATION_MARK)
        {
            report_token_type_error(*parser_buffer_.current_token, OPEN_BRACKET);
        }

        next_token();

        if (parser_buffer_.current_token->type_ != BIB_TEXT)
        {
            report_token_type_error(*parser_buffer_.current_token, BIB_TEXT);
        }
        else
        {
            parser_buffer_.current_token->type_ = BIB_ATTRIBUTE_VALUE;
        }

        next_token();

        if (parser_buffer_.current_token->type_ != CLOSE_BRACKET
           && parser_buffer_.current_token->type_ != QUOTATION_MARK)
        {
            report_token_type_error(*parser_buffer_.current_token, CLOSE_BRACKET);
        }

        next_token();

        if (parser_buffer_.current_token->type_ != COMMA
           && parser_buffer_.current_token->type_ != CLOSE_BRACKET)
        {
            report_token_type_error(*parser_buffer_.current_token, COMMA);
        }

        next_token();
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