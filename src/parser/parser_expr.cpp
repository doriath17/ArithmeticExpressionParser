#include "parser.hpp"

using namespace prs;

/**
 * 
 * return: a result with t == nullptr if there is an error (the caller should check this)
 */
AutomaResult prs::parse_expr(std::string expr, int i){
    int count = 1;
    std::string str {};
    AutomaResult result {static_cast<std::size_t>(i), nullptr};

    // with i++ and the check on count != 0 eliminate the outermost parenthesis
    for (i++; i<expr.size() && count>0; i++){
        char c = expr[i];

        if (c == ')'){
            count--;
        } else if (c == '(') {
            count++;
        }

        if (count != 0){
            str.push_back(c);
        }
    }

    if (count == 0){
        result.substr_end = i-1;
        result.t = new Token{token_type::expr, token_category::expr, str};
    }

    return result;

}