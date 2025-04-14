#include "parser.hpp"
#include <iostream>

using namespace prs;

bool prs::is_operator_char(char &c){
    switch (c) {
        case '+': case '-': case '*': case '/':
            return true;
        default:
            return false; 
    }
}

token_type prs::to_token_type(char &c){
    switch (c){
        case '+':
            return token_type::add;
        case '-':
            return token_type::sub;
        case '*':
            return token_type::mul;
        case '/':
            return token_type::div; 
    }

    return token_type::expr;
}

std::string prs::extract_substring(const std::string& str, int i, int j){
    std::string ret {};

    if (j >= str.size()){
        std::cout << "Error: cannot extract substring.\nExiting the program...\n";
        exit(-1);
    }

    for (; i<=j; i++){
        ret.push_back(str[i]);
    }

    return ret;
}