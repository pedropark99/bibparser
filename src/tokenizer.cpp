#include <string>
#include <iostream>

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









void tokenizer(TokenizerBuffer &buf)
{
    std::list<Token> tokens;
    std::cout << "[INFO:] ...Starting the tokenizer." << std::endl;
    while (true)
    {
        if (*buf.current_char == '@')
        {
            tokenize_entry(buf, tokens);
        }
        if (buf.current_char == buf.end)
        {
            std::cout << "[INFO:] Tokenizer reached end of file." << std::endl;
            break;
        }
        buf.current_char++;
    }


    std::cout
        << "[INFO:] First stage of token generation is complete." << std::endl
        << "[INFO:] ...Starting to reprocess the generated tokens." << std::endl;
    for (Token token: tokens)
    {
        token.print_token();
    }
}



SubString collect_entry_body(TokenizerBuffer &buf)
{
    buf.lexeme_begin = buf.current_char;
    while (buf.current_char != buf.end)
    {
        if (*(buf.current_char + 1) == '@')
        {
            break;
        }
        buf.current_char++;
    }

    SubString entry_body = trim_substring({buf.lexeme_begin, buf.current_char});
    return entry_body;
}

void process_entry_body(SubString entry_body)
{
    std::list<Token> body_tokens;
    std::list<SubString> unprocessed_body_components;
    std::string::iterator look_ahead;
    TokenizerBuffer buf = {
        entry_body.begin,
        entry_body.end,
        entry_body.begin,
        entry_body.begin
    };

    if (*buf.current_char == '{')
    {
        unprocessed_body_components.emplace_back(collect_current_substring(buf));
    }

    while (buf.current_char != buf.end)
    {
        if ((buf.current_char + 1) != buf.end)
        {
            look_ahead = buf.current_char + 1;
        }

        if (*look_ahead == '=' |
            *look_ahead == '{' |
            *look_ahead == '}' |
            *look_ahead == '"' |
            *look_ahead == ',')
        {
            unprocessed_body_components.emplace_back(collect_current_substring(buf));
            unprocessed_body_components.emplace_back(collect_current_substring(buf));
        }

        buf.current_char++;
    }


    for (SubString body_component: unprocessed_body_components)
    {
        print_substring(body_component);
    }
}








void tokenize_entry(TokenizerBuffer &buf, std::list<Token> &tokens)
{
    tokenize_entry_type(buf, tokens);

    SubString entry_body = collect_entry_body(buf);
    process_entry_body(entry_body);
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

    SubString entry_type = trim_substring({buf.lexeme_begin, buf.current_char});
    tokens.emplace_back(Token(BIB_TYPE, entry_type));
}



Token tokenize_bib_identifier(TokenizerBuffer &buf)
{
    buf.lexeme_begin = buf.current_char;
    while (buf.current_char != buf.end)
    {
        if (*(buf.current_char + 1) == ',')
        {
            break;
        }
        buf.current_char++;
    }
    SubString substring = {buf.lexeme_begin, buf.current_char};
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
    return Token(BIB_IDENTIFIER, substring);
}


Token tokenize_open_bracket(TokenizerBuffer &buf)
{
    buf.lexeme_begin = buf.current_char;
    SubString substring = {buf.lexeme_begin, buf.current_char};
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
    return Token(OPEN_BRACKET, substring);
}

Token tokenize_comma(TokenizerBuffer &buf)
{
    buf.lexeme_begin = buf.current_char;
    SubString substring = {buf.lexeme_begin, buf.current_char};
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
    return Token(COMMA, substring);
}

Token tokenize_text(TokenizerBuffer &buf)
{
    SubString substring = {buf.lexeme_begin, buf.current_char};
    if (buf.current_char != buf.end)
    {
        buf.current_char++;
    }
    buf.lexeme_begin = buf.current_char;
    return Token(BIB_ATTRIBUTE_VALUE, substring);
}

SubString collect_current_substring(TokenizerBuffer &buf)
{
    SubString substring = {
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













std::string token_type_to_string(TokenType type)
{
    std::string s_type;
    switch (type)
    {
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


