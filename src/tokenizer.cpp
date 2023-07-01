#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"


static const
std::unordered_set<char> token_delimiters = {
    '@'
    , '{'
    , '}'
    , ','
    , '='
    , '"'
    , '\n'
    , '\0'
};



Token::Token(TokenType input_type, SubString input_value)
    : type_(input_type), value_ (input_value), line_in_source_(0)
{

}

std::string Token::as_string()
{
    std::string s_line = "* Line in source: " + integer_to_string(line_in_source_) + "\n";
    std::string s_type = "* Token Type: " + token_type_to_string(type_)  + "\n";
    std::string s_value = "* Token Value: " + substring_to_string(value_)  + "\n\n";
    return "[TOKEN]\n" + s_line + s_type + s_value;
}


void Token::print_token()
{
    std::cout << Token::as_string() << std::endl;
}









Tokenizer::Tokenizer(std::string path_to_bib_file)
{
    bib_file_ = read_bib_file(path_to_bib_file = path_to_bib_file);
    
    tokenizer_buffer_ = {
        bib_file_.begin(),
        bib_file_.end(),
        bib_file_.begin(),
        bib_file_.begin(),
        bib_file_.begin()
    };
}


void Tokenizer::next_char()
{
    tokenizer_buffer_.current_char++;
    if (std::next(tokenizer_buffer_.current_char) != tokenizer_buffer_.end_of_file)
    {
        tokenizer_buffer_.look_ahead = std::next(tokenizer_buffer_.current_char);
    }
}


Token Tokenizer::get_next_token()
{
    Token token = Token();
    while (true)
    {
        if (char_equal_to_any_of(*tokenizer_buffer_.current_char, token_delimiters)
            || char_equal_to_any_of(*tokenizer_buffer_.look_ahead, token_delimiters)
            || tokenizer_buffer_.look_ahead == tokenizer_buffer_.end_of_file)
        {
            token = collect_token(tokenizer_buffer_.lexeme_begin, tokenizer_buffer_.current_char);
            break;
        }

        next_char();
    }

    next_char();
    tokenizer_buffer_.lexeme_begin = tokenizer_buffer_.current_char;
    
    return token;
}


Token Tokenizer::collect_token(std::string::iterator begin, std::string::iterator end)
{
    SubString token_value = trim_substring({begin, end});
    TokenType token_type = find_token_type(token_value);
    return Token(token_type, token_value);
}



void Tokenizer::collect_raw_tokens(bool raw_tokens)
{
    int64_t line_in_source = 1;
    while (true)
    {
        current_token_ = get_next_token();
        current_token_.line_in_source_ = line_in_source;
        if (current_token_.type_ == NEW_LINE) line_in_source++;
        tokens_.emplace_back(current_token_);
        if (current_token_.type_ == END_OF_FILE) break;
    }


    if (raw_tokens)
    {
        return;
    }
    else
    {
        redefine_bib_text_tokens();
    }
}

void Tokenizer::redefine_bib_text_tokens()
{
    std::list<Token>::iterator look_ahead = std::list<Token>::iterator();
    std::list<Token>::iterator look_behind = std::list<Token>::iterator();
    std::list<Token>::iterator token_it = std::list<Token>::iterator();
    auto is_bib_text = [](Token &token) { return token.type_ == BIB_TEXT; };

    for (token_it = tokens_.begin(); token_it != tokens_.end(); token_it++)
    {
        if (token_it->type_ == BIB_ENTRY
            & std::next(token_it) != tokens_.end()
            & std::next(token_it)->type_ == BIB_TEXT)
        {
            look_ahead = std::next(token_it);
            look_ahead->type_ = BIB_TYPE;
        }

        if (token_it->type_ == BIB_ENTRY)
        {
            look_ahead = std::find_if(token_it, tokens_.end(), is_bib_text);
            if (look_ahead != tokens_.end())
            {
                look_ahead->type_ = BIB_IDENTIFIER;
            }
        }
    }

    for (token_it = tokens_.begin(); token_it != tokens_.end(); token_it++)
    {
        if (token_it->type_ == EQUAL_SIGN
            & std::prev(token_it) != tokens_.begin()
            & std::prev(token_it)->type_ == BIB_TEXT)
        {
            look_behind = std::prev(token_it);
            look_behind->type_ = BIB_ATTRIBUTE_KEY;
        }

        if (token_it->type_ == EQUAL_SIGN)
        {
            look_ahead = std::find_if(token_it, tokens_.end(), is_bib_text);
            if (look_ahead != tokens_.end())
            {
                look_ahead->type_ = BIB_ATTRIBUTE_VALUE;
            }
        }
    }
}


void Tokenizer::print_tokens()
{
    for (Token token: tokens_)
    {
        token.print_token();
    }
}












TokenType find_token_type(SubString token_value)
{
    TokenType type = UNKNOWN;

    if (token_value.begin == token_value.end)
    {
        char value = substring_to_char(token_value);
        switch (value)
        {
        case '@':
            type = BIB_ENTRY;
            break;
        case ',':
            type = COMMA;
            break;
        case '{':
            type = OPEN_BRACKET;
            break;
        case '}':
            type = CLOSE_BRACKET;
            break;
        case '=':
            type = EQUAL_SIGN;
            break;
        case '"':
            type = QUOTATION_MARK;
            break;
        case ' ':
            type = EMPTY;
            break;
        case '\n':
            type = NEW_LINE;
            break;
        case '\0':
            type = END_OF_FILE;
            break;
        
        default:
            break;
        }
    }

    if (type == UNKNOWN)
    {
        type = BIB_TEXT;
    }

    return type;
}






std::string token_type_to_string(TokenType type)
{
    std::string s_type;
    switch (type)
    {
    case END_OF_FILE:
        s_type = "END_OF_FILE";
        break;
    case NEW_LINE:
        s_type = "NEW_LINE";
        break;
    case EMPTY:
        s_type = "EMPTY";
        break;
    case BIB_TEXT:
        s_type = "BIB_TEXT";
        break;
    case BIB_ENTRY:
        s_type = "BIB_ENTRY";
        break;
    case BIB_BODY:
        s_type = "BIB_BODY";
        break;
    case BIB_ATTRIBUTE_VALUE:
        s_type = "BIB_ATTRIBUTE_VALUE";
        break;
    case BIB_ATTRIBUTE_KEY:
        s_type = "BIB_ATTRIBUTE_KEY";
        break;
    case BIB_ATTRIBUTE:
        s_type = "BIB_ATTRIBUTE";
        break;
    case BIB_IDENTIFIER:
        s_type = "BIB_IDENTIFIER";
        break;
    case BIB_TYPE:
        s_type = "BIB_TYPE";
        break;
    case COMMA:
        s_type = "COMMA";
        break;
    case OPEN_BRACKET:
        s_type = "OPEN_BRACKET";
        break;
    case CLOSE_BRACKET:
        s_type = "CLOSE_BRACKET";
        break;
    case EQUAL_SIGN:
        s_type = "EQUAL_SIGN";
        break;
    case QUOTATION_MARK:
        s_type = "QUOTATION_MARK";
        break;
    default:
        break;
    }
    return s_type;
}


