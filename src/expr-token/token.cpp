#include "token.hpp"
#include <string>
#include <stdexcept>
#include <iostream>
#include <queue>

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

/**
 * Search for the first token with the lowest priority from sx (from i to j)
 */
int search_from_sx(std::vector<Token *> v, int i, int j){
    for (int k=i; k<=j; k++){
        if (v[k]->get_priority() == token_priority::p0){
            return k;
        }
    }
    for (int k=i; k<=j; k++){
        if (v[k]->get_priority() == token_priority::p1){
            return k;
        }
    }
    for (int k=i; k<=j; k++){
        if (v[k]->get_priority() == token_priority::p2){
            return k;
        }
    }
    for (int k=i; k<=j; k++){
        if (v[k]->get_priority() == token_priority::p3){
            return k;
        }
    }
    return -1;
}

/**
 * Search for the first token with the lowest priority from dx (from j to i)
 */
int search_from_dx(std::vector<Token *> v, int i, int j){
    for (int k=j; k>=i; k--){
        if (v[k]->get_priority() == token_priority::p0){
            return k;
        }
    }
    for (int k=j; k>=i; k--){
        if (v[k]->get_priority() == token_priority::p1){
            return k;
        }
    }
    for (int k=j; k>=i; k--){
        if (v[k]->get_priority() == token_priority::p2){
            return k;
        }
    }
    for (int k=j; k>=i; k--){
        if (v[k]->get_priority() == token_priority::p3){
            return k;
        }
    }
    return -1;
}

/**
 * reduce the slice (v, i, j) in a token using search form sx
 */
Token *prs::reduce_dx(std::vector<Token *> v, int i, int j){
    Token *t = nullptr;

    if (i == j){    // in this case must be a literal
        if (t = v[i]; t->category != token_category::literal)
            throw std::runtime_error{std::string{"string malformed -- literal not leaf: "} + t->str};
        else return t;
    } else if (j < i){  // there are no more tokens in v
        return nullptr; // the caller must interpret this the right way
    }
    
    int k = search_from_sx(v, i, j);
    if (k == -1){
        throw std::runtime_error{std::string{"error -- there is a token with no priority: "} + t->str};
    }
    t = v[k];

    switch (t->category){
        case token_category::unary_op:
            t->dx = reduce_dx(v, i, k-1);
            if (t->dx == nullptr){  // express the idea that an unary operator must have an argument
                throw std::runtime_error{std::string{"string malformed -- no argument for unary operator "} + t->str};
            }
            break;
        case token_category::binary_op:
            t->sx = reduce_sx(v, i, k-1);
            t->dx = reduce_dx(v, k+1, j);
            if (t->sx == nullptr || t->dx == nullptr){ // express the idea that an unary operator must have both arguments
                throw std::runtime_error{std::string{"string malformed -- no argument for binary operator "} + t->str};
            }
            break;
    }

    return t;
}

/**
 * reduce the slice (v, i, j) in a token using search form dx
 */
Token *prs::reduce_sx(std::vector<Token *> v, int i, int j){
    Token *t = nullptr;

    if (i == j){    // in this case must be a literal
        if (t = v[i]; t->category != token_category::literal)
            throw std::runtime_error{std::string{"string malformed -- literal not leaf: "} + t->str};
        else return t;
    } else if (j < i){  // there are no more tokens in v
        return nullptr; // the caller must interpret this the right way
    }

    int k = search_from_dx(v, i, j);
    if (k == -1){
        throw std::runtime_error{std::string{"error -- there is a token with no priority: "} + t->str};
    }
    t = v[k];

    switch (t->category){
        case token_category::unary_op:
            t->dx = reduce_dx(v, i, k-1);
            if (t->dx == nullptr){  // express the idea that an unary operator must have an argument
                throw std::runtime_error{std::string{"string malformed -- no argument for unary operator "} + t->str};
            }
            break;
        case token_category::binary_op:
            t->sx = reduce_sx(v, i, k-1);
            t->dx = reduce_dx(v, k+1, j);
            if (t->sx == nullptr || t->dx == nullptr){ // express the idea that an unary operator must have both arguments
                throw std::runtime_error{std::string{"string malformed -- no argument for binary operator "} + t->str};
            }
            break;
    }

    return t;
}

// reduce v into a token 
Token *prs::reduce(std::vector<Token *> v){
    return reduce_dx(v, 0, v.size()-1);
}

void Token::breadth_view(){
    std::deque<Token *> current_level{};
    std::deque<Token *> next_level{};

    std::string level_str {};

    current_level.push_back(this);

    while (not current_level.empty()){
        // consume the current level to populate the next level
        Token *t = current_level.front();
        level_str.append("[" + t->str + "]");

        if (t->sx != nullptr)
            next_level.push_back(t->sx);
        if (t->dx != nullptr)
            next_level.push_back(t->dx);

        current_level.pop_front();

        if (current_level.empty()){
            std::cout << level_str << std::endl;
            current_level = next_level; // copy
            next_level.clear();
            level_str.clear();
        }
    }
}

