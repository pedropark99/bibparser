#include <string>
#include <iostream>


#include "read_bib.hpp"
#include "tokenizer.hpp"

enum TAG
{
    BIB_IDENTIFIER = 5234,
    BIB_TYPE = 5233,
    BIB_ATTRIBUTE = 5235
};

enum STATE
{
    LOOK_AHEAD
};



void tokenizer(void)
{
    std::string::iterator it = bibparser::bib_file.begin();
    std::string buffer;
    STATE state;
    buffer.reserve(5400);
    TAG tag;

    while (it != bibparser::bib_file.end())
    {
        // std::cout << *it << std::endl;
        // Ignore white spaces and go to the next character;
        if (is_white_space(*it))
        {
            std::cout << "Ignoring white space..." << std::endl;
            it++;
            continue;
        }

        it++;
    }
}


bool is_white_space(char chr)
{
    if (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\r') {
        return true;
    } 
    else {
        return false;
    }
}