#include "parser.hpp"
#include <exception>
#include <iostream>

using namespace prs;

// an expr can represent an operator right argument
bool is_valid(token_category last, token_category curr){
    switch (last) {
    case token_category::temporary:
        return true;
    case token_category::expr:              // if last == expr can only be the left arg of a binary operator
        if (curr != token_category::binary_op) return false;
        break;
    case token_category::literal:           // if last == literal can only be the left arg of a binary operator
        if (curr != token_category::binary_op) return false;
        break;
    case token_category::unary_op:
        if (curr == token_category::binary_op) return false; // can be literal or expr
        break;
    case token_category::binary_op:
        if (curr == token_category::binary_op) return false; // can be literal or expr or unary operator
        break;    
    }
    return true;
}


std::vector<Token *> prs::parse(std::string expr){
    AutomaResult a_result{};
    token_category last_category = token_category::temporary;
    std::vector<Token *> v{};


    for (int i=0; i<expr.size(); i++){
        char& c = expr[i];

        if (std::isdigit(c)){
            a_result = parse_literal(expr, i);
        } else if (prs::is_operator_char(c)) {
            a_result = parse_operator(expr, i);
        } else if (c == '('){
            
            a_result = parse_expr(expr, i);
            if (a_result.t == nullptr){
                throw std::runtime_error{"parenthesis mismatch"};
            }

            // implicit multiplication
            if ((last_category == token_category::expr &&  a_result.t->get_category() == token_category::expr) ||
                (last_category == token_category::literal && 
                (a_result.t->get_category() == token_category::unary_op || a_result.t->get_category() == token_category::expr)))
            {
                v.push_back(new Token{token_type::mul, token_category::binary_op, std::string{'*'}});
                last_category = token_category::binary_op;
            }


        } else if (std::isblank(c)){
            continue;
        } else {
            throw std::runtime_error{"invalid character: " + c};
        }

        i = a_result.substr_end;
        if (!is_valid(last_category, a_result.t->get_category())){
            throw std::runtime_error{"invalid state -- token: " + a_result.t->to_string()};
        }
        last_category = a_result.t->get_category();

        v.push_back(a_result.t);
    }

    return v;
}

