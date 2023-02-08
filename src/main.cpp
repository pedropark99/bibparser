#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace bibparser
{
    std::vector<std::string> &
    read_bib_file(std::string path)
    {
        std::vector<std::string> bib_file;
        bib_file.reserve(500);

        std::ifstream file_connection;
        file_connection.open(path);

        std::string line;
        while (std::getline(file_connection, line)) {
            bib_file.emplace_back(line);
        }

        file_connection.close();

        return bib_file;
    }

}


int
main(void)
{
    
    bibparser::read_bib_file("./../../../data/example1.bib");
    
    
    return 0;
}



