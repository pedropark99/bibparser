#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <string>

#include "syntax_check.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"

namespace bibparser {


SyntaxChecker::SyntaxChecker(std::vector<Token> &input_tokens)
{
    tokens_to_check_ = std::vector<Token>();
    for (Token token: input_tokens)
    {
        // Ignore spaces and new lines for simplicity in checking the syntax
        if (token.type_ == EMPTY || token.type_ == NEW_LINE) continue;
        tokens_to_check_.emplace_back(token);
    }

    syntax_buffer_ = {
        tokens_to_check_.begin(),  // begin_of_tokens
        tokens_to_check_.end(),    // end_of_tokens
        tokens_to_check_.begin(),  // current_token
        tokens_to_check_.begin()   // look_ahead
    };

    if (std::next(tokens_to_check_.begin()) != tokens_to_check_.end())
    {
        syntax_buffer_.look_ahead = std::next(tokens_to_check_.begin());
    }
}



void SyntaxChecker::next_token()
{
    syntax_buffer_.current_token++;
    if (std::next(syntax_buffer_.current_token) != syntax_buffer_.end_of_tokens)
    {
        syntax_buffer_.look_ahead = std::next(syntax_buffer_.current_token);
    }
}




std::vector<Token> SyntaxChecker::check_syntax()
{
    if (syntax_buffer_.current_token == syntax_buffer_.end_of_tokens)
    {
        return tokens_to_check_;
    }

    if (syntax_buffer_.current_token->type_ != BIB_ENTRY)
    {
        report_token_type_error(*syntax_buffer_.current_token, BIB_ENTRY);
    }

    next_token();

    if (syntax_buffer_.current_token->type_ != BIB_TEXT)
    {
        report_token_type_error(*syntax_buffer_.current_token, BIB_TEXT);
    }
    else
    {
        syntax_buffer_.current_token->type_ = BIB_TYPE;
    }


    next_token();

    if (syntax_buffer_.current_token->type_ != OPEN_BRACKET
       && syntax_buffer_.current_token->type_ != QUOTATION_MARK)
    {
        report_token_type_error(*syntax_buffer_.current_token, OPEN_BRACKET);
    }

    next_token();

    if (syntax_buffer_.current_token->type_ != BIB_TEXT)
    {
        report_token_type_error(*syntax_buffer_.current_token, BIB_TEXT);
    }
    else
    {
        syntax_buffer_.current_token-> type_ = BIB_IDENTIFIER;
    }

    next_token();

    if (syntax_buffer_.current_token->type_ != COMMA)
    {
        report_token_type_error(*syntax_buffer_.current_token, COMMA);
    }

    next_token();

    while (syntax_buffer_.current_token != syntax_buffer_.end_of_tokens)
    {

        if (syntax_buffer_.current_token->type_ != BIB_TEXT)
        {
            report_token_type_error(*syntax_buffer_.current_token, BIB_TEXT);
        }
        else
        {
            syntax_buffer_.current_token->type_ = BIB_ATTRIBUTE_KEY;
        }

        next_token();

        if (syntax_buffer_.current_token->type_ != EQUAL_SIGN)
        {
            report_token_type_error(*syntax_buffer_.current_token, EQUAL_SIGN);
        }

        next_token();

        if (syntax_buffer_.current_token->type_ != OPEN_BRACKET
           && syntax_buffer_.current_token->type_ != QUOTATION_MARK)
        {
            report_token_type_error(*syntax_buffer_.current_token, OPEN_BRACKET);
        }

        next_token();

        if (syntax_buffer_.current_token->type_ != BIB_TEXT)
        {
            report_token_type_error(*syntax_buffer_.current_token, BIB_TEXT);
        }
        else
        {
            syntax_buffer_.current_token->type_ = BIB_ATTRIBUTE_VALUE;
        }

        next_token();

        if (syntax_buffer_.current_token->type_ != CLOSE_BRACKET
           && syntax_buffer_.current_token->type_ != QUOTATION_MARK)
        {
            report_token_type_error(*syntax_buffer_.current_token, CLOSE_BRACKET);
        }

        next_token();

        if (syntax_buffer_.current_token->type_ != COMMA
           && syntax_buffer_.current_token->type_ != CLOSE_BRACKET)
        {
            report_token_type_error(*syntax_buffer_.current_token, COMMA);
        }

        next_token();
        
        if (syntax_buffer_.current_token->type_ == END_OF_FILE) break;
    }

    return tokens_to_check_;
}





void report_token_type_error(Token token_found, TokenType type_expected)
{
    token_found.print_token();

    std::string TYPE_ERROR_MESSAGE = "The parser expected to find next a token of type ";
    TYPE_ERROR_MESSAGE = TYPE_ERROR_MESSAGE + token_type_to_string(type_expected);
    TYPE_ERROR_MESSAGE = TYPE_ERROR_MESSAGE + ". But it found a token of type ";
    TYPE_ERROR_MESSAGE = TYPE_ERROR_MESSAGE + token_type_to_string(token_found.type_);
    TYPE_ERROR_MESSAGE = TYPE_ERROR_MESSAGE + " instead.";

    std::cerr << TYPE_ERROR_MESSAGE << std::endl;

    throw std::exception();
}







} // end of namespace bibparser