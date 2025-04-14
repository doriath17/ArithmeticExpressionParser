#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "token.hpp"

namespace prs {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class AutomaResult {
public:
    std::size_t substr_end;
    Token *t;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Utility functions

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool is_operator_char(char &c);

token_type to_token_type(char &c);

std::string extract_substring(const std::string& str, int i, int j);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// main functions

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AutomaResult parse_parethesis(std::string expr, int j);

AutomaResult parse_operator(std::string expr, int j);

AutomaResult parse_value(std::string expr, int j);

std::vector<Token *> parse(std::string expr);

void parse_verbose(std::string expr);

double evaluate(std::string expr);

double evaluate_verbose(std::string expr);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}


#endif // PARSER_HPP
