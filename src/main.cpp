#include <string>
#include <iostream>
#include <list>

#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "global_variables.hpp"
#include "string_utils.hpp"


int main(int argc, char *argv[])
{
    std::string path_to_file = get_path_to_file(argc, argv);
    std::string bib_file = read_bib_file(path_to_file);

    ParserBuffer parser_buffer;
    parser_buffer.begin = bib_file.begin();
    parser_buffer.end = bib_file.end();
    parser_buffer.anchor = bib_file.begin();
    parser_buffer.current_char = bib_file.begin();

    std::list<Token> tokens;
    tokenizer(parser_buffer, tokens);
    
    for (Token token: tokens)
    {
        trim_substring(token);
        token.print_token();
    }
    
}

