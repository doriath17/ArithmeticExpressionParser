#include "parser.hpp"
#include <iostream>

using namespace prs;

AutomaResult prs::parse_operator(std::string expr, int i){
    AutomaResult    result {static_cast<std::size_t>(i), nullptr};
    token_type type;
    char& c = expr[i];
    std::string substr;
    
    if (token_type type = to_token_type(expr[i]); type != token_type::expr){
        result.t = new Token(type, token_category::binary_op, std::string{expr[i]});
        return result;
    } else {
        std::cout<<"Error: using an invalid operator.\nTerminating the program...\n";
        exit(-1);
    }
}