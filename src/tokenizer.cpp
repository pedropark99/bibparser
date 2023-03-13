#include <string>
#include <iostream>

#include "global_variables.hpp"
#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "string_utils.hpp"


Token::Token (Tag input_tag, SubString input_value)
{
    tag = input_tag;
    value = input_value;
}

std::string Token::as_string()
{
    std::string s_tag = tag_to_string(tag);
    std::string s_value = substring_to_string(value);
    std::string text = s_tag + "=" + s_value;
    return text;
}

void Token::print_token()
{
    std::cout << Token::as_string() << std::endl;
}



void tokenizer(ParserBuffer &buf, std::list<Token> &tokens)
{
    while (true)
    {
        if (*buf.current_char == '@')
        {
            parse_entry(buf, tokens);
        }
        if (buf.current_char == buf.end)
        {
            std::cout << "Tokenizer reached end of file!" << std::endl;
            break;
        }
        buf.current_char++;
    }

}


void parse_entry(ParserBuffer &buf, std::list<Token> &tokens)
{
    parse_entry_type(buf, tokens);
    parse_entry_body(buf, tokens);
}

void parse_entry_type(ParserBuffer &buf, std::list<Token> &tokens)
{
    buf.anchor = buf.current_char;
    while (buf.current_char != buf.end)
    {
        if (*buf.current_char == '{')
        {
            break;
        }
        buf.current_char++;
    }

    SubString entry_type = {buf.anchor, buf.current_char};
    tokens.emplace_back(Token(BIB_TYPE, entry_type));
}


void parse_entry_body(ParserBuffer &buf, std::list<Token> &tokens)
{
    buf.anchor = buf.current_char;

    while (buf.current_char != buf.end)
    {
        if (*(buf.current_char + 1) == '@')
        {
            return;
        }

        if (*buf.current_char == '{')
        {
            parse_open_bracket(buf, tokens);
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
            parse_bib_identifier(buf, tokens);
            parse_comma(buf, tokens);
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

        if (*buf.current_char == '=')
        {
            parse_entry_attribute(buf, tokens);
            continue;
        }

        buf.current_char++;
    }
}


void parse_bib_identifier(ParserBuffer &buf, std::list<Token> &tokens)
{
    SubString substring = {buf.anchor, buf.current_char + 1};
    tokens.emplace_back(Token(BIB_IDENTIFIER, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.anchor = buf.current_char;
}

void parse_entry_attribute(ParserBuffer &buf, std::list<Token> &tokens)
{
    buf.anchor = buf.current_char;
    while (buf.current_char != buf.begin)
    {
        if (*(buf.current_char - 1) == ',')
        {
            break;
        }
        buf.current_char--;
    }
    SubString attribute_key = {buf.current_char, buf.anchor};
    tokens.emplace_back(Token(BIB_ATTRIBUTE_KEY, attribute_key));

    buf.current_char = buf.anchor;
    buf.current_char++;
    // char value_delimiter_open;
    // char value_delimiter_end;
    // while (buf.current_char != buf.end)
    // {
    //     if (*buf.current_char == '"')
    //     {
    //         value_delimiter_open = '"';
    //         value_delimiter_end = '"';
    //     }
    //     if (*buf.current_char == '{')
    //     {
    //         value_delimiter_open = '{';
    //         value_delimiter_end = '}';
    //     }
    //     buf.current_char++;       
    // }
}

void parse_comma(ParserBuffer &buf, std::list<Token> &tokens)
{
    buf.anchor = buf.current_char;
    SubString substring = {buf.anchor, buf.current_char};
    tokens.emplace_back(Token(COMMA, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.anchor = buf.current_char;
}

void parse_open_bracket(ParserBuffer &buf, std::list<Token> &tokens)
{
    buf.anchor = buf.current_char;
    SubString substring = {buf.anchor, buf.current_char};
    tokens.emplace_back(Token(OPEN_BRACKET, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.anchor = buf.current_char;
}

void parse_close_bracket(ParserBuffer &buf, std::list<Token> &tokens)
{
    buf.anchor = buf.current_char;
    SubString substring = {buf.anchor, buf.current_char};
    tokens.emplace_back(Token(CLOSE_BRACKET, substring));
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.anchor = buf.current_char;
}


std::string tag_to_string(Tag tag)
{
    std::string s_tag;
    switch (tag)
    {
    case BIB_ATTRIBUTE_VALUE:
        s_tag = "BIB_ATTRIBUTE_VALUE";
        break;
    case BIB_ATTRIBUTE_KEY:
        s_tag = "BIB_ATTRIBUTE_KEY";
        break;
    case BIB_IDENTIFIER:
        s_tag = "BIB_IDENTIFIER";
        break;
    case BIB_TYPE:
        s_tag = "BIB_TYPE";
        break;
    case COMMA:
        s_tag = "COMMA";
        break;
    case OPEN_BRACKET:
        s_tag = "OPEN_BRACKET";
        break;
    case CLOSE_BRACKET:
        s_tag = "CLOSE_BRACKET";
        break;
    default:
        break;
    }
    return s_tag;
}