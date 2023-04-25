#include <string>
#include <list>
#include <unordered_map>
#include <stack>


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


void Parser::parse_tokens(std::list<Token> entry_tokens)
{
    Token current_token;
    BibEntry bib_entry;
    std::list<Token>::iterator token_it = entry_tokens.begin();
    std::stack<Token> key_value_pair;

    while (token_it != entry_tokens.end())
    {
        current_token = *token_it;
        switch (current_token.type)
        {
        case BIB_TYPE:
            bib_entry.type = parse_bibtype(current_token);
            break;
        case BIB_IDENTIFIER:
            bib_entry.identifier = parse_identifier(current_token);
            break;
        case BIB_ATTRIBUTE_KEY:
            check_key_value_stack(key_value_pair);
            key_value_pair.emplace(current_token);
            break;
        case BIB_ATTRIBUTE_VALUE:
            check_key_value_stack(key_value_pair);
            key_value_pair.emplace(current_token);
            bib_entry.attributes.emplace_back(
                parse_bib_attribute(key_value_pair)
            );
            break;

        default:
            break;
        }
        
        token_it++;
    }

}