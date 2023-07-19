#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <string>
#include <cstring>

#include "syntax_check.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"

namespace bibparser {


SyntaxChecker::SyntaxChecker(std::vector<Token> &input_tokens)
{
    tokens_to_check_ = std::vector<Token>();
    syntax_buffer_ = {
        input_tokens.begin(),  // begin_of_tokens
        input_tokens.end(),    // end_of_tokens
        input_tokens.begin(),  // current_token
        input_tokens.begin()   // look_ahead
    };

    if (std::next(input_tokens.begin()) != input_tokens.end())
    {
        syntax_buffer_.look_ahead = std::next(input_tokens.begin());
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

void SyntaxChecker::match_next_token(TokenType type_to_match)
{
    if (syntax_buffer_.current_token->type_ != type_to_match)
    {
        report_token_type_error(*syntax_buffer_.current_token, type_to_match);
    }

    next_token();
}

void SyntaxChecker::match_next_token(std::vector<TokenType> types_to_match)
{
    TokenType current_token_type = syntax_buffer_.current_token->type_;
    bool any_of = std::find(
        types_to_match.begin(),
        types_to_match.end(),
        current_token_type
    ) != types_to_match.end();

    if ( !any_of )
    {
        report_token_type_error(*syntax_buffer_.current_token, types_to_match[0]);
    }

    next_token();
}

void SyntaxChecker::match_until(TokenType type_to_end_matching)
{
    while (syntax_buffer_.current_token->type_ != type_to_end_matching
           || syntax_buffer_.current_token->type_ != END_OF_FILE)
    {
        next_token();
    }
}




void SyntaxChecker::match_set_next_token(TokenType raw_type_to_match, TokenType new_type_to_set)
{
    if (syntax_buffer_.current_token->type_ != raw_type_to_match)
    {
        report_token_type_error(*syntax_buffer_.current_token, raw_type_to_match);
    }
    else
    {
        syntax_buffer_.current_token->type_ = new_type_to_set;
    }

    next_token();
}


std::vector<Token> SyntaxChecker::check_syntax()
{
    if (syntax_buffer_.current_token == syntax_buffer_.end_of_tokens)
    {
        return tokens_to_check_;
    }

    match_next_token(BIB_ENTRY);

    std::string bib_type = substring_to_string(syntax_buffer_.current_token->value_);
    std::string::iterator it = bib_type.begin();
    for (it; it != bib_type.end(); it++) *it = tolower(*it);

    if (bib_type == "string")
    {
        check_string_entry();
    }
    else
    {
        check_standard_body();
    }


    return tokens_to_check_;
}




void SyntaxChecker::check_string_entry()
{
    match_set_next_token(BIB_TEXT, BIB_TYPE);
    match_next_token(OPEN_BRACKET);
    match_set_next_token(BIB_TEXT, BIB_ATTRIBUTE_KEY);
    match_next_token(EQUAL_SIGN);
    match_set_next_token(BIB_TEXT, BIB_ATTRIBUTE_VALUE);
    match_next_token(CLOSE_BRACKET);
    match_next_token(CLOSE_BRACKET);
}




void SyntaxChecker::check_standard_body()
{
    match_set_next_token(BIB_TEXT, BIB_TYPE);
    match_next_token(OPEN_BRACKET);
    match_set_next_token(BIB_TEXT, BIB_IDENTIFIER);
    match_next_token(COMMA);

    while (syntax_buffer_.current_token != syntax_buffer_.end_of_tokens)
    {
        match_set_next_token(BIB_TEXT, BIB_ATTRIBUTE_KEY);
        match_next_token(EQUAL_SIGN);
        
        // Expect next a single token, or, multiple tokens that compose an attribute value
        check_attribute_value();

        match_next_token(std::vector<TokenType>{COMMA, CLOSE_BRACKET});
        
        if (syntax_buffer_.current_token->type_ == END_OF_FILE) break;
    }

}



void SyntaxChecker::check_attribute_value()
{
    if (syntax_buffer_.current_token->type_ == BIB_TEXT)
    {
        // The token is probably a number like in the example below:
        // year = 2005
        if ( !is_number(substring_to_string(syntax_buffer_.current_token->value_)) )
        {
            report_expected_number(*syntax_buffer_.current_token);
        }

        next_token();
    }

    if (syntax_buffer_.current_token->type_ == OPEN_BRACKET
        || syntax_buffer_.current_token->type_ == QUOTATION_MARK)
    {
        match_next_token(std::vector<TokenType>{OPEN_BRACKET, QUOTATION_MARK});
        match_set_next_token(BIB_TEXT, BIB_ATTRIBUTE_VALUE);
        match_next_token(std::vector<TokenType>{CLOSE_BRACKET, QUOTATION_MARK});
    }
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


void report_expected_number(Token token_found)
{
    token_found.print_token();

    std::string TYPE_ERROR_MESSAGE = "You did not used an open bracket, or, a quotation mark after the equal sign.";
    TYPE_ERROR_MESSAGE = TYPE_ERROR_MESSAGE + " As a result, the parser expected to find a parsable number (e.g. 2005) after the equal sign";
    TYPE_ERROR_MESSAGE = TYPE_ERROR_MESSAGE + ". But it found the above token (of type ";
    TYPE_ERROR_MESSAGE = TYPE_ERROR_MESSAGE + token_type_to_string(token_found.type_);
    TYPE_ERROR_MESSAGE = TYPE_ERROR_MESSAGE + ") instead.";

    std::cerr << TYPE_ERROR_MESSAGE << std::endl;

    throw std::exception();
}





} // end of namespace bibparser