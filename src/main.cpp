#include <string>
#include <iostream>
#include <list>
#include <unordered_map>

#include "read_bib.hpp"
#include "parser.hpp"
#include "string_utils.hpp"


struct CmdLineOptions {
    std::string path_to_file;
    bool parse_file;
    bool print_tokens;
    bool print_raw_tokens;
};

void parse_cmd_options(CmdLineOptions &options, int argc, char *argv[]);


int main(int argc, char *argv[])
{
    CmdLineOptions options = {
        "", true, false, false
    };

    parse_cmd_options(options, argc, argv);

    if (options.parse_file == true)
    {
        Parser parser = Parser(options.path_to_file);
        parser.parse_file();
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
}



void parse_cmd_options(CmdLineOptions &options, int argc, char *argv[])
{
    options.path_to_file = get_path_to_file(argc, argv);

    if (argc <= 2)
    {
        return;
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
    }
}