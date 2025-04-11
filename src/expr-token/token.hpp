#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <vector>
#include <string>

// prs for parser
namespace prs {


// (categoria, priorita')

enum class token_category {
    expr,
    literal,
    unary_op,
    binary_op,
};

enum class token_type {
    expr,
    literal,
    add, 
    sub, 
    mul, 
    div,
    cos,
    sin,
    tan,
    sqrt,
    log,
};

std::string type_to_string(token_type type);
    
class Token {
public:

    Token(token_type type, token_category category, std::string expr);

    void set_sx(Token *sx);
    void set_dx(Token *dx);
    
    token_type get_type();
    token_category get_category();
    Token *get_sx();
    Token *get_dx();
    std::string get_str();

    std::string to_string();


    // void evaluate();


private:
    token_type type;
    token_category category;
    std::string str;
    Token *sx, *dx;
};



} 




#endif // TOKEN_HPP