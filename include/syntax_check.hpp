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
    SyntaxChecker(std::vector<Token> &input_tokens);
    std::vector<Token> check_syntax();

private:
    void next_token();
    void check_standard_body();
    void check_string_entry();
    void check_preamble_entry();
};


void report_token_type_error(Token token_found, TokenType type_expected);


} // end of namespace bibparser