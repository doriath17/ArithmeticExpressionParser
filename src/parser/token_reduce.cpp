#include "token.hpp"
#include <stdexcept>

using namespace prs;

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
        if (t = v[i]; t->category == token_category::expr){ // if it is an expr let it pass: the expr will be expanded during evaluation
            return t;
        } else if (t->category != token_category::literal)
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
        if (t = v[i]; t->category == token_category::expr){ // if it is an expr let it pass: the expr will be expanded during evaluation
            return t;
        } else if (t->category != token_category::literal)
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