#include <string>
#include <iostream>
#include <list>
#include <unordered_map>

#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "global_variables.hpp"
#include "string_utils.hpp"


int main(int argc, char *argv[])
{
    std::string path_to_file = get_path_to_file(argc, argv);
    std::string bib_file = read_bib_file(path_to_file);

    TokenizerBuffer tokenizer_buffer;
    tokenizer_buffer.begin = bib_file.begin();
    tokenizer_buffer.end = bib_file.end();
    tokenizer_buffer.lexeme_begin = bib_file.begin();
    tokenizer_buffer.current_char = bib_file.begin();

    std::list<Token> tokens;
    tokenizer(tokenizer_buffer, tokens);

    for (Token token : tokens)
    {
        token.print_token();
    }

    std::unordered_map<std::string, TokenType> symbol_table;
    add_identifiers(tokens, symbol_table);

    
    
}

