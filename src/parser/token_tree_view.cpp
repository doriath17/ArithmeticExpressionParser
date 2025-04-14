#include "token.hpp"
#include <stdexcept>
#include <deque>
#include <iostream>

using namespace prs;

void Token::breadth_view(){
    std::deque<Token *> current_level{};
    std::deque<Token *> next_level{};

    std::string level_str {};

    current_level.push_back(this);

    while (not current_level.empty()){
        // consume the current level to populate the next level
        Token *t = current_level.front();
        if (t->category == token_category::expr){
            level_str.append("[\"" + t->str + "\"]");
        } else {
            level_str.append("[" + t->str + "]");
        }

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