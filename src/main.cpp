#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "read_bib.h"

int main(void)
{
    std::string a = bibparser::bib_file;
    std::string::iterator it = a.begin();

    std::cout << *it << std::endl;
    it++;
    std::cout << *it << std::endl;

}



