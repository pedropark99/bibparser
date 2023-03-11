#include <string>
#include <unordered_set>
#include <iostream>

#include "tokenizer.hpp"

bool is_white_space(char chr);
bool is_digit(char chr);
bool is_letter(char chr);
bool find_in_set(char chr, const std::unordered_set<char>& set);

int count_char(std::string &string, char chr);
void find_first_position(std::string &string, char chr);

void print_substring(SubString substring);