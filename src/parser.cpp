#include <string>
#include <list>


#include "parser.hpp"
#include "tokenizer.hpp"


Parser::Parser(std::string path_to_bib_file)
{
    tokenizer = Tokenizer(path_to_bib_file);
}


Token Parser::get_next_token()
{
    Token token = tokenizer.get_next_token();
    token.print_token();
    return token;
}