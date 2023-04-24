#include <string>
#include <unordered_set>
#include <iostream>
#include <vector>

#include "tokenizer.hpp"

bool is_white_space(char chr);
bool is_digit(char chr);
bool is_letter(char chr);
bool find_in_set(char chr, const std::unordered_set<char>& set);

bool starts_with(const std::string &string, const std::string start);
bool ends_with (const std::string &string, const std::string end);

int count_char(std::string &string, char chr);
int count_char(SubString string, char chr);
void find_first_position(std::string &string, char chr);
SubString trim_substring(SubString substring);
bool substring_is_space(SubString sub);
void trim_substring(Token &token);

std::string substring_to_string(SubString substring);
char substring_to_char(SubString substring);
void print_substring(SubString substring);
std::vector<SubString> split_substring(SubString sub, const char delimiter);