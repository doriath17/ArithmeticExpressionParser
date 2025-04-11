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

Token* Token::get_sx(){
    return sx;
}

Token* Token::get_dx(){
    return dx;
}

std::string Token::get_str(){
    return str;
}



std::string Token::to_string(){
    std::string ret;
    ret.append("[type: ")
        .append(type_to_string(type))
        .append(", expr: ")
        .append(str)
        .append("]");
    return ret;
}

std::string prs::type_to_string(token_type type){
    switch (type) {
        case token_type::literal:
            return std::string{"LIT"};
        case token_type::add:
            return std::string{"ADD"};
        case token_type::sub:
            return std::string{"SUB"};
        case token_type::mul:
            return std::string{"MUL"};
        case token_type::div:
            return std::string{"DIV"};
    }
}


