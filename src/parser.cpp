#include <string>
#include <list>


#include "parser.hpp"
#include "tokenizer.hpp"


Parser::Parser(/* args */)
{
}

Parser::get_next_token()
{
    return Tokenizer::get_next_token();
}