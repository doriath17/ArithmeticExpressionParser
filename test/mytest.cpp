#include <iostream>

#include "parser.hpp"

using namespace prs;

int main(int argc, char** argv){
    
    std::string input{argv[1]};
    double expected = std::atof(argv[2]);

    double result = evaluate(input);

    std::cout << "result: " << result << std::endl;

    if (result == expected)
        return 0;
    else {
        return 1;
    }
}