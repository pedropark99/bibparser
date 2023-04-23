#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <ranges>

#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"


Token::Token(TokenType input_type, SubString input_value)
{
    type = input_type;
    value = input_value;
}

std::string Token::as_string()
{
    std::string s_type = token_type_to_string(type);
    std::string s_value = substring_to_string(value);
    std::string text = s_type + ": " + s_value;
    return text;
}

void Token::print_token()
{
    std::cout << Token::as_string() << std::endl;
}





Tokenizer::Tokenizer(std::string path_to_bib_file)
{
    bib_file = read_bib_file(path_to_bib_file = path_to_bib_file);
    std::string::iterator begin = bib_file.begin();
    std::string::iterator end = bib_file.end();
    
    buf = {
        begin,
        end,
        begin,
        begin
    };
}

Token Tokenizer::get_next_token()
{
    TokenType token_type;
    SubString token_value;
    std::string::iterator look_ahead;

    while (buf.current_char != buf.end)
    {
        if (*buf.current_char == '@' |
            *buf.current_char == '{' |
            *buf.current_char == '}' |
            *buf.current_char == ',' |
            *buf.current_char == '=' |
            *buf.current_char == '"' |
            *buf.current_char == '\n')
        {
            token_value = Tokenizer::collect_current_substring();
            break;
        }

        if ((buf.current_char + 1) != buf.end)
        {
            look_ahead = (buf.current_char + 1);
        }

        if (*look_ahead == '@' |
            *look_ahead == '{' |
            *look_ahead == '}' |
            *look_ahead == ',' |
            *look_ahead == '=' |
            *look_ahead == '"' |
            *look_ahead == '\n')
        {
            token_value = Tokenizer::collect_current_substring();
            break;
        }

        buf.current_char++;
    }

    if (buf.current_char == buf.end)
    {
        return Token(END_OF_FILE, {buf.end, buf.end});
    }

    token_value = trim_substring(token_value);
    token_type = find_token_type(token_value);
    if (token_type == EMPTY)
    {
        return get_next_token();
    }

    return Token(token_type, token_value);
}


SubString Tokenizer::collect_current_substring()
{
    SubString substring;
    substring = {
        buf.lexeme_begin,
        buf.current_char
    };

    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
    return substring;
}

void Tokenizer::collect_tokens()
{
    while (true)
    {
        current_token = get_next_token();
        tokens.emplace_back(current_token);
        if (current_token.type == END_OF_FILE)
        {
            break;
        }
    }

    redefine_bib_text_tokens();
}

void Tokenizer::redefine_bib_text_tokens()
{
    auto is_bib_entry = [](Token token) {return token.type == BIB_ENTRY;};
    auto bib_entries = std::views::iota(tokens) | std::views::filter(is_bib_entry);
    for (Token token: bib_entries)
    {
        token.print_token();
    }
}


void Tokenizer::set_token_type_if(TokenType type_equal_to, TokenType new_token_type, int n_steps = 1)
{
    std::list<Token>::iterator look_ahead;
    std::list<Token>::iterator look_behind;
    std::list<Token>::iterator token_it;

    for (token_it = tokens.begin(); token_it != tokens.end(); token_it++)
    {
        if ((*token_it).type != type_equal_to)
            continue;

        if (n_steps > 0
            & std::next(token_it, n_steps) != tokens.end()
            & (*std::next(token_it, n_steps)).type == BIB_TEXT)
        {
            look_ahead = std::next(token_it, n_steps);
            (*look_ahead).type = new_token_type;
        }

        if (n_steps < 0
            & std::prev(token_it, abs(n_steps)) != tokens.begin()
            & (*std::prev(token_it, abs(n_steps))).type == BIB_TEXT)
        {
            look_behind = std::prev(token_it, abs(n_steps));
            (*look_behind).type = new_token_type;  
        }
    }
}



TokenType find_token_type(SubString token_value)
{
    TokenType type;
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
    else
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


