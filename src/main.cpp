#include <string>
#include <iostream>
#include <list>
#include <unordered_map>

#include "read_bib.hpp"
#include "parser.hpp"
#include "syntax_check.hpp"




struct CmdLineOptions {
    std::string path_to_file;
    bool parse_file;
    bool print_tokens;
    bool print_raw_tokens;
    bool syntax_check;
};

CmdLineOptions parse_cmd_options(int argc, char *argv[]);



int main(int argc, char *argv[])
{

    CmdLineOptions options = parse_cmd_options(argc, argv);

    if (options.parse_file == true)
    {
        bibparser::Parser parser = bibparser::Parser(options.path_to_file);
        parser.parse();
    }
    if (options.print_tokens == true)
    {
        bibparser::Tokenizer tokenizer = bibparser::Tokenizer(options.path_to_file);
        bibparser::Token current_token = bibparser::Token();
        tokenizer.collect_raw_tokens();
    }
    if (options.print_raw_tokens == true)
    {
        bibparser::Tokenizer tokenizer = bibparser::Tokenizer(options.path_to_file);
        std::vector<bibparser::Token> tokens = tokenizer.collect_raw_tokens();
        for (bibparser::Token token: tokens) token.print_token();
    }
    if (options.syntax_check == true)
    {
        bibparser::Tokenizer tokenizer = bibparser::Tokenizer(options.path_to_file);
        //bibparser::syntax_checker();
    }

    return 0;
}



CmdLineOptions parse_cmd_options(int argc, char *argv[])
{
    CmdLineOptions options = {
        "",
        true, false, false, false
    };

    options.path_to_file = bibparser::get_path_to_file(argc, argv);

    if (argc <= 2)
    {
        return options;
    }

    for (int i = 1; i < argc; i++)
    {
        std::string current_argument = std::string(argv[i]);
        if (current_argument == "-t" | current_argument == "--tokens")
        {
            options.print_tokens = true;
            options.parse_file = false;
        }
        if (current_argument == "-rt" | current_argument == "--raw-tokens")
        {
            options.print_raw_tokens = true;
            options.parse_file = false;
        }
        if (current_argument == "-s" | current_argument == "--syntax-check")
        {
            options.print_tokens = false;
            options.print_raw_tokens = false;
            options.parse_file = false;
            options.syntax_check = true;
        }
    }

    return options;
}

