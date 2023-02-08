#include <string>
#include <iostream>
#include <fstream>

int main (void)
{
    std::ifstream bib_file;
    bib_file.open("./../../../data/example1.bib");

    std::string line;
    while (std::getline(bib_file, line)) {
        std::cout << line << std::endl;
    }

    bib_file.close();
    
    return 0;
}