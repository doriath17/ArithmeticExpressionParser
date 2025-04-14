#include "token.hpp"
#include <string>

using namespace prs;

Token::Token(token_type type, token_category category, std::string str) : type{type}, category{category}, str{str}, sx{nullptr}, dx{nullptr} {}

void Token::set_sx(Token *sx){
    this->sx = sx;
}

void Token::set_dx(Token *dx){
    this->dx = dx;
}

token_type Token::get_type(){
    return type;
}

token_category Token::get_category(){
    return category;
}

token_priority Token::get_priority(){
    switch (type){
        case token_type::add: case token_type::sub:
            return token_priority::p0;
        case token_type::mul: case token_type::div:
            return token_priority::p1;
        case token_type::integer: case token_type::real:
            return token_priority::p2;
    }
    return token_priority::p3; // expr  
}

Token* Token::get_sx(){
    return sx;
}

Token* Token::get_dx(){
    return dx;
}

std::string Token::get_str(){
    return str;
}

std::string prs::to_string(token_type type){
    std::string ret{};
    switch (type) {
        case token_type::expr:
            return std::string{"expr"};
        case token_type::integer:
            return std::string{"integer"};
        case token_type::real:
            return std::string{"real"};
        case token_type::add:
            return std::string{"add"};
        case token_type::sub:
            return std::string{"sub"};
        case token_type::mul:
            return std::string{"mul"};
        case token_type::div:
            return std::string{"div"};
    }

    return ret;
}

std::string Token::to_string(){
    std::string ret;
    ret.append("[" + prs::to_string(type))
        .append(",\"")
        .append(str)
        .append("\"]");
    return ret;
}