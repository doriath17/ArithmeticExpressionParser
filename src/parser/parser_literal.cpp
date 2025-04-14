#include "parser.hpp"
#include <iostream>
#include <stdexcept>

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
        throw std::runtime_error{"literal malformed"};
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
AutomaResult prs::parse_literal(std::string expr, int i){
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
        throw std::runtime_error{"literal malformed: " + prs::extract_substring(expr, i, result.substr_end)};
    }

    result.substr_end = expr.size()-1;
    result.t = new Token(type, token_category::literal, prs::extract_substring(expr, i, result.substr_end));

    return result;
}