#include <list>


#include "syntax_check.hpp"
#include "tokenizer.hpp"


namespace syntax{
    
void syntax_checker(std::list<Token> &tokens)
{
    for (Token token: tokens)
    {
        token.print_token();
    }
}

} // end of namespace syntax