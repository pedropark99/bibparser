#include <string>
#include <list>


#include "parser.hpp"
#include "tokenizer.hpp"

/*
Parser steps:

1. get next token;
2. start to parse this token;
5. parse the token into its best format;
3. check for grammar errors;
4. check for sytax errors;
6. register the property into the symbol table.
*/


Parser::Parser(std::string path_to_bib_file)
{
    tokenizer = Tokenizer(path_to_bib_file);
}


void Parser::parse_file()
{
    tokenizer.collect_tokens();
    for (Token token: tokenizer.tokens)
    {
        token.print_token();
    }
}


void Parser::parse_token(Token token)
{
    if (token.type == BIB_ENTRY)
    {
        stack_of_tokens.clear();
        stack_of_tokens.emplace_back(token);
    }
}