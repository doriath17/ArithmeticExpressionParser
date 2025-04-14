#include "parser.hpp"
#include <iostream>

using namespace prs;

int main(int argc, char **argv){
    std::vector<std::string> v {
        std::string{"1+(1)"},
        std::string{"1.24((1425+(48))-2312.67)*3"},
        std::string{"(3 + 5)(5 * 3)"},
    };

    for (int i=0; i<v.size(); i++){
        parse_verbose(v[i]);
    }
}