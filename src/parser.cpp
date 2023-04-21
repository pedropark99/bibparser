#include <string>
#include <list>


#include "parser.hpp"
#include "tokenizer.hpp"


Parser::Parser(std::string path_to_bib_file)
{
    tokenizer = Tokenizer(path_to_bib_file);
}

void Parser::parse_token(Token token)
{
    
}

void Parser::parse_file()
{
    tokenizer.collect_tokens();
    for (Token token: tokenizer.tokens)
    {
        token.print_token();
    }
}