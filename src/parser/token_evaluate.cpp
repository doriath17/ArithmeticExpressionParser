#include "token.hpp"
#include "parser.hpp"
#include <stdexcept>

using namespace prs;

double prs::evaluate_expr(Token *t){
    return reduce(parse(t->str))->evaluate();
}

double prs::evaluate_literal(Token *t){
    switch (t->type){
        case token_type::integer:
            return static_cast<double>(std::atoi(t->str.c_str()));
        case token_type::real:
            return static_cast<double>(std::atof(t->str.c_str()));
    }
}

double prs::evaluate_binary_operator(Token *t){
    double sx_val = t->sx->evaluate();
    double dx_val = t->dx->evaluate();

    switch (t->type){
        case token_type::add:
            return sx_val + dx_val;
        case token_type::sub:
            return sx_val - dx_val;
        case token_type::mul:
            return sx_val * dx_val;
        case token_type::div:
            if (dx_val == 0.0){
                throw std::runtime_error{"division by 0 error"};
            }
            return sx_val / dx_val;
    }
}

double prs::evaluate_unary_operator(Token *t){

}

/**
 * Evaluate works on well formed tree: 
 * those obtained from using parse(v) and reduce(v)
 */
double Token::evaluate(){
    double result = 0.0;
    switch (this->category) {
        case token_category::expr:
            return evaluate_expr(this);
        case token_category::literal: 
            return evaluate_literal(this);
        case token_category::binary_op:
            return evaluate_binary_operator(this);
        case token_category::unary_op:
            return evaluate_unary_operator(this);
    }
}