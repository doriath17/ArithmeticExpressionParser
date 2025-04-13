#include "parser.hpp"
#include <iostream>

using namespace prs;

void parse_verbose(std::string expr){
    std::vector<Token *> v = parse(expr);

    std::cout << "expr: " << expr << std::endl;

    for (int i=0; i<v.size(); i++){
        std::cout << v[i]->to_string() << std::endl;
    }

    std::cout << std::endl;
}

int main(int argc, char **argv){
    std::vector<std::string> v {
        std::string{"1+(1)"},
        std::string{"1((1425+(48))-2312.67)*3"},
        std::string{"(3 + 5)(5 * 3)"},
    };

    for (int i=0; i<v.size(); i++){
        parse_verbose(v[i]);
    }
}