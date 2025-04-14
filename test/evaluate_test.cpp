#include <iostream>

#include "parser.hpp"

using namespace prs;
using namespace std;

static int tested = 0;
static int passed = 0;

int evaluate_test(string expr, string result_str){
    try {
        tested++;
        double result = evaluate_verbose(expr);
        double expected = atof(result_str.c_str());
        cout << "result: " << result << ", expected: " << expected << endl << endl;
        if (to_string(result) == to_string(expected)){
            passed++;
            return 0; 
        } else {
            return 1;
        }
    } catch (runtime_error e){
        cout << e.what() << endl;
        passed++;
        return 0;
    }
}

int main(int argc, char** argv){

    evaluate_test("1+(1)", "2");
    evaluate_test("1.24((1425+(48))-2312.67)*3", "-3123.5724");
    evaluate_test("(3 + 5)(5 * 3)", "120");
    evaluate_test("(3 + 5)", "8");
    evaluate_test("1/0", "null");

    cout << "passed: " << passed << " / " << tested << endl;

}