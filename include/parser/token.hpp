#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <vector>
#include <string>

// prs for parser
namespace prs {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// token categories definition


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum class token_category {
    temporary,
    expr,
    literal,
    unary_op,
    binary_op,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// token types definition


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum class token_type {
    temporary,
    expr,
    integer,
    real,
    add, 
    sub, 
    mul, 
    div,
    // cos,
    // sin,
    // tan,
    // sqrt,
    // log,
};

std::string to_string(token_type type);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// priority definition


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum class token_priority {
    p0, 
    p1, 
    p2, 
    p3,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// token definition


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Token {
public:

    Token(token_type type, token_category category, std::string expr);

    void set_sx(Token *sx);
    void set_dx(Token *dx);

    token_type      get_type();
    token_category  get_category();
    token_priority  get_priority();
    Token *         get_sx();
    Token *         get_dx();
    std::string     get_str();
    
    std::string to_string();

    void breadth_view();

    // TODO: temporary solution
    friend Token *reduce_sx(std::vector<Token *> v, int i, int j);
    friend Token *reduce_dx(std::vector<Token *> v, int i, int j);

    friend double evaluate_expr(Token *t);
    friend double evaluate_literal(Token *t);
    friend double evaluate_unary_operator(Token *t);
    friend double evaluate_binary_operator(Token *t);


    double evaluate();


private:
    token_type type;
    token_category category;
    token_priority priority;
    std::string str;
    Token *sx, *dx;
};


Token *reduce_sx(std::vector<Token *> v, int i, int j);
Token *reduce_dx(std::vector<Token *> v, int i, int j);

Token *reduce(std::vector<Token *> v);

double evaluate_expr(Token *t);

double evaluate_literal(Token *t);

double evaluate_unary_operator(Token *t);

double evaluate_binary_operator(Token *t);


} 




#endif // TOKEN_HPP