#include <string>
#include <iostream>
#include <vector>

#include "read_bib.hpp"
#include "parser.hpp"
#include "string_utils.hpp"
#include "syntax_check.hpp"
#include "tokenizer.hpp"



int main(int argc, char *argv[])
{
    std::string str = "@main{teste,tk=2005}";
    //std::string argument_to_parse = bibparser::get_path_to_file(argc, argv);
    //std::string bib_file = argument_to_parse;
    bibparser::Tokenizer tokenizer = bibparser::Tokenizer(str);
    std::vector<bibparser::Token> tokens = tokenizer.collect_raw_tokens();
    bibparser::SyntaxChecker checker = bibparser::SyntaxChecker(tokens);
    checker.check_syntax();

    return 0;
}


