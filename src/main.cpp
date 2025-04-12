#include <iostream>

#include "parser.hpp"
#include "token.hpp"

using namespace prs;

int main(int argc, char** argv){
    if (argc < 1){
        std::cout << "Not enought arguments" << std::endl;
    }

    std::cout << "result: " << evaluate(argv[1]) << std::endl;

    return 0;
}