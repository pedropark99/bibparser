#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "read_bib.hpp"
#include "tokenizer.hpp"
#include "global_variables.hpp"

void print_tokens (std::list<Token> tokens) {
    int token_number = 0;
    for (Token token: tokens) {
        token_number++;
        std::cout << "Token Number: "
            << token_number
            << "  | Tag is: " << token.tag
            << "  | Lexeme is: " << token.value
            << std::endl;
    }
}

int main(void)
{
    collect_bib_entries(bibparser::bib_file);
    // std::list<Token> tokens = tokenizer(bibparser::bib_file);
    // print_tokens(tokens);
}



