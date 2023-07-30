#include <list>


#include "tokenizer.hpp"

namespace bibparser {

struct SyntaxCheckerBuffer {
    std::vector<Token>::iterator begin_of_tokens;
    std::vector<Token>::iterator end_of_tokens;
    std::vector<Token>::iterator current_token;
    std::vector<Token>::iterator look_ahead;
};


    
class SyntaxChecker {
private:
    SyntaxCheckerBuffer syntax_buffer_;
    std::vector<Token> tokens_to_check_;

public:
    SyntaxChecker(const std::string bib_string);
    SyntaxChecker(std::vector<Token> &input_tokens);
    std::vector<Token> check_syntax();

private:
    void next_token();
    void match_next_token(TokenType type_to_match);
    void match_next_token(std::vector<TokenType> types_to_match);
    void match_and_mark_next_token(TokenType raw_type_to_match, TokenType new_type_to_set);
    void match_until(TokenType type_to_end_matching);
    bool is_token_of_type(TokenType type);
    void check_standard_body();
    void check_attribute_tokens();
    void check_string_entry();
    void check_preamble_entry();
};


void report_token_type_error(Token token_found, TokenType type_expected);
void report_expected_number(Token token_found);


} // end of namespace bibparser
