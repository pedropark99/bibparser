#include <string>
#include <iostream>

#include "global_variables.hpp"
#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"


Token::Token (TokenType input_type, SubString input_value)
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



void tokenizer(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    while (true)
    {
        if (*buf.current_char == '@')
        {
            tokenize_entry(buf, tokens);
        }
        if (buf.current_char == buf.end)
        {
            std::cout << "Tokenizer reached end of file!" << std::endl;
            break;
        }
        buf.current_char++;
    }

    for (Token token: tokens)
    {
        trim_substring(token);
        //token.print_token();
    }

}


void tokenize_entry(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    tokenize_entry_type(buf, tokens);
    tokenize_entry_body(buf, tokens);
}

void tokenize_entry_type(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    buf.lexeme_begin = buf.current_char;
    while (buf.current_char != buf.end)
    {
        if (*buf.current_char == '{')
        {
            break;
        }
        buf.current_char++;
    }

    SubString entry_type = {buf.lexeme_begin, buf.current_char};
    tokens.emplace_back(Token(BIB_TYPE, entry_type));
}


void tokenize_entry_body(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    buf.lexeme_begin = buf.current_char;

    while (buf.current_char != buf.end)
    {
        if (*(buf.current_char + 1) == '@')
        {
            return;
        }

        if (*buf.current_char == '{')
        {
            tokenize_open_bracket(buf, tokens);
            break;
        }
        buf.current_char++;
    }


    while (buf.current_char != buf.end)
    {
        if (*(buf.current_char + 1) == '@')
        {
            return;
        }

        if (*(buf.current_char + 1) == ',')
        {
            tokenize_bib_identifier(buf, tokens);
            tokenize_comma(buf, tokens);
            break;
        }
        buf.current_char++;
    }

    while (buf.current_char != buf.end)
    {
        if (*(buf.current_char + 1) == '@')
        {
            return;
        }

        if (*buf.current_char == ',')
        {
            tokenize_comma(buf, tokens);
        }

        if (*buf.current_char == '=')
        {
            tokenize_entry_attribute(buf, tokens);
            continue;
        }

        buf.current_char++;
    }
}


void tokenize_bib_identifier(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    SubString substring = {buf.lexeme_begin, buf.current_char + 1};
    tokens.emplace_back(Token(BIB_IDENTIFIER, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
}

void tokenize_entry_attribute(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    buf.lexeme_begin = buf.current_char;
    while (buf.current_char != buf.begin)
    {
        if (*(buf.current_char - 1) == ',')
        {
            break;
        }
        buf.current_char--;
    }
    SubString attribute_key = {buf.current_char, buf.lexeme_begin};
    tokens.emplace_back(Token(BIB_ATTRIBUTE_KEY, attribute_key));

    buf.current_char = buf.lexeme_begin;
    tokenize_equal_sign(buf, tokens);

    char value_delimiter_open;
    char value_delimiter_close;
    while (buf.current_char != buf.end)
    {
        if (*buf.current_char == '"')
        {
            value_delimiter_open = '"';
            value_delimiter_close = '"';
            tokenize_quotation_mark(buf, tokens);
            break;
        }
        if (*buf.current_char == '{')
        {
            value_delimiter_open = '{';
            value_delimiter_close = '}';
            tokenize_open_bracket(buf, tokens);
            break;
        }
        buf.current_char++;       
    }

    while (buf.current_char != buf.end)
    {
        if (*(buf.current_char + 1) == value_delimiter_close)
        {
            break;
        }
        buf.current_char++;   
    }

    SubString attribute_value = {buf.lexeme_begin, buf.current_char + 1};
    tokens.emplace_back(Token(BIB_ATTRIBUTE_VALUE, attribute_value));
    buf.current_char++;
    buf.lexeme_begin = buf.current_char;

    if (value_delimiter_close == '"')
    {
        tokenize_quotation_mark(buf, tokens);
    }
    else
    {
        tokenize_close_bracket(buf, tokens);
    }
}

void tokenize_comma(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    buf.lexeme_begin = buf.current_char;
    SubString substring = {buf.lexeme_begin, buf.current_char};
    tokens.emplace_back(Token(COMMA, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
}

void tokenize_open_bracket(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    buf.lexeme_begin = buf.current_char;
    SubString substring = {buf.lexeme_begin, buf.current_char};
    tokens.emplace_back(Token(OPEN_BRACKET, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
}

void tokenize_close_bracket(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    buf.lexeme_begin = buf.current_char;
    SubString substring = {buf.lexeme_begin, buf.current_char};
    tokens.emplace_back(Token(CLOSE_BRACKET, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
}

void tokenize_equal_sign(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    buf.lexeme_begin = buf.current_char;
    SubString substring = {buf.lexeme_begin, buf.current_char};
    tokens.emplace_back(Token(EQUAL_SIGN, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
}

void tokenize_quotation_mark(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    buf.lexeme_begin = buf.current_char;
    SubString substring = {buf.lexeme_begin, buf.current_char};
    tokens.emplace_back(Token(QUOTATION_MARK, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
}


std::string token_type_to_string(TokenType type)
{
    std::string s_type;
    switch (type)
    {
    case BIB_ATTRIBUTE_VALUE:
        s_type = "BIB_ATTRIBUTE_VALUE";
        break;
    case BIB_ATTRIBUTE_KEY:
        s_type = "BIB_ATTRIBUTE_KEY";
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



void add_identifiers(std::list<Token> &tokens, std::unordered_map<std::string, TokenType> &symbol_table)
{
    for (Token token: tokens)
    {
        if (token.type == BIB_IDENTIFIER)
        {
            symbol_table.emplace(
                std::string(token.value.begin, token.value.end),
                BIB_IDENTIFIER
            );
        }
    }
}