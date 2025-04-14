#include <iostream>

#include "parser.hpp"

using namespace prs;
using namespace std;

int main(int argc, char** argv){
    std::vector<std::string> v {
        string{"1+(1)"}, string{"2"},
        string{"1.24((1425+(48))-2312.67)*3"}, string{"-3123.5724"},
        string{"(3 + 5)(5 * 3)"}, string{"120"},
        string{"(3 + 5)"}, string{"8"},
    };

    for (int i=0; i<v.size(); i += 2){
        double result = evaluate_verbose(v[i]);
        cout << "result: " << result << ", expected: " << atof(v[i+1].c_str()) << endl;
    }
}