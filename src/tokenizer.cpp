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
    std::list<Token> first_stage_tokens;
    std::list<Token> second_stage_tokens;
    
    while (true)
    {
        if (*buf.current_char == '@')
        {
            tokenize_entry(buf, first_stage_tokens);
        }
        if (buf.current_char == buf.end)
        {
            std::cout << "[INFO:] Tokenizer reached end of file." << std::endl;
            std::cout << "[INFO:] First stage of token generation is complete." << std::endl;
            break;
        }
        buf.current_char++;
    }

    for (Token token: first_stage_tokens)
    {
        trim_substring(token);
        token.print_token();
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
            break;
        }
        buf.current_char++;
    }

    SubString bib_body = {buf.lexeme_begin, buf.current_char};
    tokens.emplace_back(Token(BIB_BODY, bib_body));
}














// void reprocess_tokens ()
// {
//     std::cout << "[INFO:] Starting second stage of token generation." << std::endl;
// }

























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


