#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <regex>

#include "read_bib.h"


std::string path_string = "data/example1.bib";
std::filesystem::path bibparser::path_to_example = std::filesystem::absolute(path_string);
std::string bibparser::bib_file = bibparser::read_bib_file(
	bibparser::path_to_example.string()
);


std::string bibparser::read_bib_file(std::string path)
{
	std::string buffer;
	std::ifstream file_connection;
	file_connection.open(path);

	if (!file_connection.is_open()) {
		throw std::runtime_error("`std::ifstream` could not open the file. Check if the given path is correct.");
	}
	// Go to EOF and calculate the size of file;
	file_connection.seekg(0, std::ios::end);
	size_t size_of_file = file_connection.tellg();
	// Go back to the beggining of the file;
	file_connection.seekg(0, std::ios::beg);
	// Resize buffer to the size of file, and read contents of the file to the buffer;
    buffer.resize(size_of_file);
	file_connection.read(&buffer[0], buffer.size());

	file_connection.close();
	// Remove new lines and white spaces from bib file
	buffer = bibparser::remove_white_spaces(buffer);
	return buffer;
}


std::string bibparser::remove_white_spaces(std::string bib_file)
{
	std::regex ws_regex("[:space:]*", std::regex::extended);
	return std::regex_replace(
		bib_file,
		ws_regex,
		""
	);
}


void bibparser::TraverseString(std::string& str)
{
	for (char chr : str) {
		std::cout << chr << std::endl;
	}
}

