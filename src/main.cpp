#include <iostream>
#include <vector>
#include <algorithm>

#include "parser.hpp"
#include "token.hpp"

using namespace prs;

int main(int argc, char** argv){
    std::string expr {"+    1425+48-2312.67 *3"};
    Token * t = parse(expr);

    while (t != nullptr){
        std::cout << t->to_string() << std::endl;
        t = t->get_dx();
    }
}