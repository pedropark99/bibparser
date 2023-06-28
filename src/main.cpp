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
        Parser parser = Parser(options.path_to_file);
        parser.parse_bib_file();
    }
    if (options.print_tokens == true)
    {
        Tokenizer tokenizer = Tokenizer(options.path_to_file);
        tokenizer.collect_tokens();
        tokenizer.print_tokens();
    }
    if (options.print_raw_tokens == true)
    {
        Tokenizer tokenizer = Tokenizer(options.path_to_file);
        tokenizer.collect_tokens(true);
        tokenizer.print_tokens();
    }
    if (options.syntax_check == true)
    {
        Tokenizer tokenizer = Tokenizer(options.path_to_file);
        tokenizer.collect_tokens();
        bibparser::syntax::syntax_checker(tokenizer.tokens);
    }

    return 0;
}



CmdLineOptions parse_cmd_options(int argc, char *argv[])
{
    CmdLineOptions options = {
        "",
        true, false, false, false
    };

    options.path_to_file = get_path_to_file(argc, argv);

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

