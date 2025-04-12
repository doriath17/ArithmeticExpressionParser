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

std::string Token::to_string(){
    std::string ret;
    ret.append("[type: ")
        .append(type_to_string(type))
        .append(", expr: ")
        .append(str)
        .append("]");
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

token_priority Token::get_priority(){
    switch (type){
        case token_type::add: case token_type::sub:
            return token_priority::p0;
        case token_type::mul: case token_type::div:
            return token_priority::p1;
        case token_type::literal:
            return token_priority::p2;
    }
    return token_priority::p3; // expr  
}

int search_from_sx(std::vector<Token *> v, int i, int j){

}

int search_from_dx(std::vector<Token *> v, int i, int j){

}

// TODO: errors

// reduce the slice (v, i, j) in a token
Token *prs::reduce_dx(std::vector<Token *> v, int i, int j){
    int k = search_from_sx(v, i, j);
    Token *t = v[k];

    switch (t->category){
        case token_category::unary_op:
            t->sx = reduce_sx(v, i, k-1);
            break;
        case token_category::binary_op:
            t->sx = reduce_sx(v, i, k-1);
            t->dx = reduce_dx(v, k+1, j);
            break;
    }

    return t;
}

Token *prs::reduce_sx(std::vector<Token *> v, int i, int j){
    int k = search_from_dx(v, i, j);
    Token *t = v[k];

    switch (t->category){
        case token_category::unary_op:
            t->sx = reduce_sx(v, i, k-1);
            break;
        case token_category::binary_op:
            t->sx = reduce_sx(v, i, k-1);
            t->dx = reduce_dx(v, k+1, j);
            break;
    }

    return t;
}

// reduce v into a token 
Token *reduce(Token *t, std::vector<Token *> v){
    return reduce_dx(v, 0, v.size()-1);
}


