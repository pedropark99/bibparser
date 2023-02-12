#include <string>
#include <iostream>


#include "read_bib.hpp"

enum Tag
{
    BIB_IDENTIFIER = 5234,
    BIB_TYPE = 5233,
    BIB_ATTRIBUTE = 5235
};


void tokenizer(void)
{
    std::string::iterator it = bibparser::bib_file.begin();
    while (it != bibparser::bib_file.end())
    {
    std::cout << *it << std::endl;
    it++;
    // case chr == '@':
    //     BIB_BEGIN;
    //     break;
    
    // default:
    //     break;
    }
}