#include <string>
#include <fstream>
#include <filesystem>

#include "read_bib.hpp"
#include "string_utils.hpp"


namespace bibparser
{
    std::filesystem::path path_to_example = std::filesystem::absolute("data/example1.bib");
}


std::string get_path_to_file(int argc, char *argv[])
{
    if (argc < 2)
    {
        throw std::runtime_error("You have to give the path to a bib file to `bibparser`!");
    }

    for (int i = 1; i < argc; i++)
    {
        std::string current_argument = std::string(argv[i]);
        if (ends_with(current_argument, ".bib"))
        {
            std::filesystem::path path_to_file = std::filesystem::absolute(current_argument);
            return path_to_file.string();
        }
    }

    throw std::runtime_error("`bibparser` did not find a path to a bib file!");
}


std::string read_bib_file(std::string path)
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