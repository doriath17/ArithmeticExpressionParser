#include "parser.hpp"
#include <iostream>

using namespace prs;

void prs::parse_verbose(std::string expr){
    std::vector<Token *> v = parse(expr);

    std::cout << "expr: " << expr << std::endl;

    for (int i=0; i<v.size(); i++){
        std::cout << v[i]->to_string() << std::endl;
    }

    std::cout << std::endl;
}

double prs::evaluate(std::string expr){
    return reduce(parse(expr))->evaluate();
}

double prs::evaluate_verbose(std::string expr){

    std::cout << "///////////////////////////////////////////////////////////////////" << std::endl;

    std::cout << "\nexpr: " << expr << std::endl;

    std::vector<Token *> v = parse(expr);

    std::cout << std::endl;

    for (int i=0; i<v.size(); i++){
        std::cout << v[i]->to_string() << std::endl;
    }

    std::cout << std::endl;

    Token *root = reduce(v);
    root->breadth_view();
    
    std::cout << std::endl;
    return root->evaluate();
}