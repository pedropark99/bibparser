#include <string>
#include <unordered_set>
#include <iostream>
#include <vector>

#include "tokenizer.hpp"


namespace bibparser {

bool is_white_space(char chr);
bool is_digit(char chr);
bool is_letter(char chr);
bool is_alpha_numeric(char chr);
bool is_number(std::string str);
bool find_in_set(char chr, const std::unordered_set<char>& set);

SubString empty_substring();

bool char_equal_to_any_of(const char chr, std::unordered_set<char> set);
bool string_equal_to_any_of(const std::string str, std::unordered_set<std::string> set);

bool starts_with(const std::string &string, const std::string start);
bool ends_with (const std::string &string, const std::string end);

int count_char(std::string &string, char chr);
int count_char(SubString string, char chr);
int32_t substring_size(SubString substring);
void find_first_position(std::string &string, char chr);
bool substring_is_space(SubString sub);

int parse_number(SubString substring);
int parse_number(std::string str);

SubString trim_substring(SubString substring);
void trim_substring(Token &token);
std::vector<SubString> split_substring(SubString sub, const char delimiter);


std::string substring_to_string(SubString substring);
char substring_to_char(SubString substring);
std::string integer_to_string(int64_t i);
void print_substring(SubString substring);

} // end of namespace bibparser