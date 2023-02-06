#include <string>
#include <iostream>
#include <fstream>

int main (void)
{
    std::ifstream bib_file;
    bib_file.open("./../data/example.bib");
    if (bib_file.is_open()) {
        std::string line;
        while (std::getline(bib_file, line) {
            std::cout << line << std::endl;
        }
        bib_file.close()
    }
    
    return 0;
}