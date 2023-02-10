#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>


#include "read_bib.h"


std::vector<std::string> bibparser::read_bib_file(std::string path)
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


// void bibparser::TraverseString(std::string& str)
// {
// 	for (char chr : str) {
// 		std::cout << chr << std::endl;
// 	}
// }

std::string path_string = "data/example1.bib";

std::filesystem::path bibparser::path_to_example = std::filesystem::absolute(path_string);

std::vector<std::string> bibparser::bib_file = bibparser::read_bib_file(
	bibparser::path_to_example.string()
);

