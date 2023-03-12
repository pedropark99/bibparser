#include <string>
#include <fstream>
#include <filesystem>

#include "read_bib.hpp"
#include "global_variables.hpp"


std::filesystem::path
bibparser::path_to_example = std::filesystem::absolute("data/example1.bib");


std::string get_path_to_file(int argc, char *argv[])
{
    if (argc < 2)
    {
        throw std::runtime_error("You have to give the path to a bib file to `bibparser`!");
    }
    std::string path_string = std::string(argv[1]);
    std::filesystem::path path_to_file = std::filesystem::absolute(path_string);
    return path_to_file.string();
}


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
	return buffer;
}