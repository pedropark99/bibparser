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


    void TraverseString(std::string& str)
    {
        for (char chr : str) {
            std::cout << chr << std::endl;
        }
    }


    
}


std::vector<std::string> file = bibparser::read_bib_file("./../../../data/example1.bib");

int
main(void)
{
    
    std::cout << file << std::endl;
    //bibparser::TraverseString(bibparser::file[1]);
    
    return 0;
}



