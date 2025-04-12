#include "parser.hpp"
#include <exception>
#include <iostream>

using namespace prs;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// utility functions

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool prs::is_operator_char(char &c){
    switch (c) {
        case '+': case '-': case '*': case '/':
            return true;
        default:
            return false; 
    }
}

token_type prs::to_token_type(char &c){
    switch (c){
        case '+':
            return token_type::add;
        case '-':
            return token_type::sub;
        case '*':
            return token_type::mul;
        case '/':
            return token_type::div; 
    }

    return token_type::expr;
}

std::string prs::extract_substring(const std::string& str, int i, int j){
    std::string ret {};

    if (j >= str.size()){
        std::cout << "Error: cannot extract substring.\nExiting the program...\n";
        exit(-1);
    }

    for (; i<=j; i++){
        ret.push_back(str[i]);
    }

    return ret;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// operator parser

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


AutomaResult prs::parse_operator(std::string expr, int i){
    AutomaResult    result {static_cast<std::size_t>(i), nullptr};
    token_type type;
    char& c = expr[i];
    std::string substr;
    
    if (token_type type = to_token_type(expr[i]); type != token_type::expr){
        result.t = new Token(type, token_category::binary_op, std::string{expr[i]});
        return result;
    } else {
        std::cout<<"Error: using an invalid operator.\nTerminating the program...\n";
        exit(-1);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// value parser

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


using namespace prs;

enum class state{
    // q0 is entered by the caller by finding the pattern value
    q1, // upon reading a digit (and continuing reading a digit)
    q2, // upon reading a dot: '.' (real value)
    q3, // upon reading a digit after a dot
    q4, // terminal state: upon encountering somthing other than a digit
    q5, // upon not reading a digit after a dot: non-ending state, error in the format
};


state transition_q1(char &c){
    if (std::isdigit(c)){
        return state::q1;
    } else if (c == '.') {
        return state::q2;
    } else {
        return state::q4;
    }
}

state transition_q2(char& c){
    if (std::isdigit(c)){
        return state::q3;
    } else {
        std::cout << "Error: literal malformed.\nTerminatin the program...\n";
        exit(-1);
    }
}

state transition_q3(char& c){
    if (std::isdigit(c)){
        return state::q3;
    } else {
        return state::q4;
    }
}


/**
 * expr: the expression from which the automata will read
 * i:    the index from which the automata will read (i <= expr.size()-1)
 *       i is the first character: allowing the transition from q0 to q1
 * 
 * throw: std::exception
 */
AutomaResult prs::parse_value(std::string expr, int i){
    AutomaResult    result {static_cast<std::size_t>(i), nullptr};
    state           current_state{state::q1};
    token_type      type {token_type::integer};

    for (int j = i; j<expr.size(); j++){
        char c = expr[j];

        switch (current_state){
            case state::q1:
                current_state = transition_q1(c);
                break;
            case state::q2:
                current_state = transition_q2(c);
                type = token_type::real;
                break;
            case state::q3:
                current_state = transition_q3(c);
                break;
        }

        if (current_state == state::q4){
            result.substr_end = j-1;
            result.t = new Token(type, token_category::literal, prs::extract_substring(expr, i, result.substr_end));
            return result;
        }
    }

    // handle token if it is at the end of the expr

    if (current_state == state::q2){
        std::cout << "Error: literal malformed.\nTerminatin the program...\n";
        exit(-1);
    }

    result.substr_end = expr.size()-1;
    result.t = new Token(type, token_category::literal, prs::extract_substring(expr, i, result.substr_end));

    return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// parser

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool is_valid(token_category last, token_category curr){
    switch (last) {
    case token_category::expr:
        return true;
    case token_category::literal:
        if (curr == token_category::literal || curr == token_category::unary_op) return false;
        break;
    case token_category::unary_op:
        if (curr == token_category::binary_op) return false;
        break;
    case token_category::binary_op:
        if (curr == token_category::binary_op) return false;
        break;    
    }
    return true;
}


std::vector<Token *> prs::parse(std::string expr){
    AutomaResult a_result{};
    token_category last_category = token_category::expr;

    std::vector<Token *> v{};

    for (int i=0; i<expr.size(); i++){
        char& c = expr[i];

        if (std::isdigit(c)){
            a_result = parse_value(expr, i);
            i = a_result.substr_end;
        } else if (prs::is_operator_char(c)) {
            a_result = parse_operator(expr, i);
        } else if (std::isblank(c)){
            continue;
        } else {
            std::cout << "Error: string malformed.\nExiting the program...\n";
            exit(-1);
        }

        if (!is_valid(last_category, a_result.t->get_category())){
            std::cout << "Error: string malformed.\nExiting the program...\n";
            exit(-1);
        }
        last_category = a_result.t->get_category();

        v.push_back(a_result.t);
    }

    return v;
}