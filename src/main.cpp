#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>

#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "global_variables.hpp"


void print_token(Token token)
{
    std::cout << "Token: "
        << token.tag
        << "   |   ";
    
    for (auto& it: token.attributes) {
    // Do stuff
        std::cout << it.first
            << "   |   "
            << it.second
            << std::endl;
    }

}


int main(void)
{
    std::list<Token> tokens;
    tokenizer(tokens);
    for (Token token: tokens)
    {
        print_token(token);
    }
    
}

