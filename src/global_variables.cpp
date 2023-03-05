#include <unordered_set>
#include <string>

#include "global_variables.hpp"


const std::unordered_set<char> LETTERS = {
    u8'a', u8'b', u8'c', u8'd', u8'e', u8'f',
    u8'g', u8'h', u8'i', u8'j', u8'k', u8'l',
    u8'm', u8'n', u8'o', u8'p', u8'q', u8'r',
    u8's', u8't', u8'u', u8'v', u8'x', u8'w',
    u8'y', u8'z',
    
    u8'A', u8'B', u8'C', u8'D', u8'E', u8'F',
    u8'G', u8'H', u8'I', u8'J', u8'K', u8'L',
    u8'M', u8'N', u8'O', u8'P', u8'Q', u8'R',
    u8'S', u8'T', u8'U', u8'V', u8'X', u8'W',
    u8'Y', u8'Z'
};

const std::unordered_set<char> NUMBERS = {
    u8'0', u8'1', u8'2', u8'3', u8'4',
    u8'5', u8'6', u8'7', u8'8', u8'9'
};

const std::unordered_set<char> LINES = {
    u8'-', u8'_'
};