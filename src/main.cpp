#include <string>
#include <iostream>
#include <list>
#include <unordered_map>

#include "read_bib.hpp"
#include "parser.hpp"


int main(int argc, char *argv[])
{
    std::string path_to_file = get_path_to_file(argc, argv);

    Parser parser = Parser(path_to_file);
    for (int i = 0; i < 50; i++)
    {
        parser.get_next_token();        
    }

    std::unordered_map<std::string, TokenType> symbol_table;
    
}

