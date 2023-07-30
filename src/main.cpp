#include <string>
#include <iostream>
#include <vector>

#include "read_bib.hpp"
#include "parser.hpp"
#include "string_utils.hpp"
#include "syntax_check.hpp"



int main(int argc, char *argv[])
{
    std::string argument_to_parse = bibparser::get_path_to_file(argc, argv);
    std::string bib_file = argument_to_parse;
    //bibparser::Tokenizer tokenizer = bibparser::Tokenizer(bib_file);
    bibparser::Parser parser = bibparser::Parser(bib_file);
    parser.print_tokens();

    return 0;
}


namespace bibparser {
std::string get_path_to_file(int argc, char *argv[])
{
    if (argc < 2)
    {
        throw std::runtime_error("You have to give the path to a bib file to `bibparser`!");
    }

    for (int i = 1; i < argc; i++)
    {
        std::string current_argument = std::string(argv[i]);
        if (bibparser::starts_with(current_argument, "-"))
        {
            continue;
        }
        else
        {
            return current_argument;
        }
    }

    throw std::runtime_error("`bibparser` did not find a path to a bib file!");
}

}


