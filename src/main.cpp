#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <filesystem>

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




int main(int argc, char *argv[])
{
    std::string path_to_file = get_path_to_file(argc, argv);
    std::string bib_file = bibparser::read_bib_file(path_to_file);

    std::list<Token> tokens;
    tokenizer(bib_file, tokens);
    // for (Token token: tokens)
    // {
    //     print_token(token);
    // }
    
}

