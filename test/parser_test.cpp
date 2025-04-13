#include "parser.hpp"
#include <iostream>

using namespace prs;

int main(int argc, char **argv){
    // std::string expr {"1+(1)"};

    std::string expr {"1(+((1425+(48))-2312.67)*3)"};

    std::vector<Token *> v = parse(expr);

    for (int i=0; i<v.size(); i++){
        std::cout << v[i]->to_string() << std::endl;
    }
}