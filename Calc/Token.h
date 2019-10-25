//
// Created by Jeronimo on 2019-10-21.
//

#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H
#include <string>

enum class Kind:char{
    name, number, end, plus='+', minus='-', mul='*', div='/', print=';', assign='=', lp='(', rp=')'
};

struct Token {
    Kind kind;
    std::string string_value;
    double number_value;
};

#endif //CALCULATOR_TOKEN_H
